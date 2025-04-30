﻿#include "battleManager.h"
#include "json.hpp"
#include "peleas.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <SDL_ttf.h>
#include <thread>

using json = nlohmann::json;
// Valores para el animo
const int MOD = 10;
const int MINMINDSET = MOD;
const int MAXMINDSET = 100 - MOD;


// Tiempo entre turnos (milisegundos)
constexpr int MSEG = 1500;

// Para random
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dist(0.0f, 100.0f);
uniform_int_distribution<int> range(0, 27);  // 28 es el numero de enfrentamientos (nºpeleadores * (nºpeleadores - 1) /2) y hay 8 peleadores. Incluyendo el 0 lo hace que llegue hasta el 27
uniform_real_distribution<float> mindsetRange(5, 20);
uniform_real_distribution<float> inicialMindSet(MINMINDSET, MAXMINDSET);

BattleManager::BattleManager(DialogueBox* dialog, Game* g)
	: currentMatch()
	, currentState(BattleState::START)
	, lastTurn(BattleState::START)
	, actionTimer(0)
	, endMatch(false)
	, dialog(dialog)
	, game(g)
{
}

void BattleManager::StartBattle()
{

	int i = range(gen);
	currentMatch = game->GetMatchUp(i);

	float rndMindset1 = inicialMindSet(gen);
	float rndMindset2 = inicialMindSet(gen);

	if (currentMatch.advantageFighterIndex == 1) {
		currentMatch.fighter1.setMindset(rndMindset1 + MOD);
		currentMatch.fighter2.setMindset(rndMindset2 - MOD);
	}
	else {
		currentMatch.fighter1.setMindset(rndMindset1 + MOD);
		currentMatch.fighter2.setMindset(rndMindset2 - MOD);
	}

	// Empieza el que tiene menos habilidad
	if (currentMatch.fighter1.getAbility() > currentMatch.fighter2.getAbility()) {
		std::swap(currentMatch.fighter1, currentMatch.fighter2);
	}

	currentState = BattleState::START;
}

void BattleManager::Update(float deltaTime)
{
	if (dialog->shouldAdvanceState() || currentState == BattleState::START) {
		dialog->resetDialogStateFlag(); // Reiniciamos el temporizador

		switch (currentState) {
		case BattleState::START:
			dialog->showMessage("La pelea será un clasicazo en esta arena " + currentMatch.fighter1.getName() + " vs " + currentMatch.fighter2.getName());
			dialog->showMessage(currentMatch.battleDescription);
			dialog->showMessage("Acorde a las normas empieza " + currentMatch.fighter1.getName());
			currentState = BattleState::PLAYER1_TURN;  // Cambiamos al turno del jugador 1
			lastTurn = BattleState::PLAYER1_TURN;  // Inicializamos el último turno
			break;

		case BattleState::PLAYER1_TURN:
			ActionTurn(currentMatch.fighter1, currentMatch.fighter2);
			currentState = BattleState::EVALUATE;  // Cambiamos a evaluación
			break;

		case BattleState::PLAYER2_TURN:
			ActionTurn(currentMatch.fighter2, currentMatch.fighter1);
			currentState = BattleState::EVALUATE;  // Cambiamos a evaluación
			break;

		case BattleState::EVALUATE:
			if (!currentMatch.fighter1.isAlive() ||
				!currentMatch.fighter2.isAlive()) {
				currentState = BattleState::END;  // Si alguien murió, terminamos
			}
			else {
				// Cambiar al siguiente turno
				if (lastTurn == BattleState::PLAYER1_TURN) {
					currentState = BattleState::PLAYER2_TURN;
					dialog->showMessage("Turno de " + currentMatch.fighter2.getName());
					dialog->showMessage("¡" + currentMatch.fighter2.getName() + " se dispone a atacar ferozmente a su enemigo!");
					lastTurn =
						BattleState::PLAYER2_TURN;  // Actualizamos el último turno
				}
				else {
					currentState = BattleState::PLAYER1_TURN;
					dialog->showMessage("Turno de " + currentMatch.fighter1.getName());
					dialog->showMessage("¡" + currentMatch.fighter1.getName() + " se dispone a atacar ferozmente a su enemigo!");
					lastTurn =
						BattleState::PLAYER1_TURN;  // Actualizamos el último turno
				}
			}
			break;

		case BattleState::END:
			Fighter* winner = currentMatch.fighter1.isAlive() ?
				&currentMatch.fighter1 :
				&currentMatch.fighter2;
			dialog->showMessage("¡La batalla ha terminado! El ganador es: " + winner->getName());
			break;
		}
	}
}


void BattleManager::ActionTurn(Fighter& active, Fighter& objetive)
{
	float hitBackProb = 2.5f + 15.0f * (50.0f - active.getMindset()) / 200.0f;
	float failProb = 7.5f + 12.5f * (50.0f - active.getMindset()) / 100.0f;
	float criticalProb = 10.0f + 30.0f * (active.getMindset() - 50.0f) / 100.0f;
	float prob = dist(gen);

	// Golpearse a sí mismo
	if (prob < hitBackProb) {
		active.takeDamage(active.getAttack());
		dialog->showMessage("¡Pero se ha golpeado a sí mismo, " + active.getName() + " se ha vuelto loco!");

		if (active.isAlive()) {
			active.reduceMindset(mindsetRange(gen));
			dialog->showMessage("Esto seguro que mina su concentración en el combate");
			dialog->showMessage("¡Ahora es más probable que pierda!");
		}
		else {
			dialog->showMessage("¡LA CATASTROFE SE HIZO REALIDAD!");
			dialog->showMessage("¡" + active.getName() + " ha caído por su propia mano!");
		}
	}

	// Fallo
	else if (prob < hitBackProb + failProb) {
		dialog->showMessage(active.getName() + " lamentablemente su golpe ha fallado a su objetivo.");
		active.reduceMindset(mindsetRange(gen));
		dialog->showMessage("Esto seguro que mina su concentración en el combate.");
		dialog->showMessage("¡Ahora es más probable que pierda!");
	}

	// Crítico
	else if (prob < hitBackProb + failProb + criticalProb) {
		objetive.takeDamage(active.getAttack() * 3);
		dialog->showMessage("¡MADRE MÍA, CRÍTICO! " + active.getName() + " acaba de destrozar a su oponente.");
		dialog->showMessage(" Tras semejante golpe tal vez deban replantearse el resultado del combate.");
		if (objetive.isAlive()) {
			active.boostMindset(mindsetRange(gen));
			objetive.reduceMindset(mindsetRange(gen));
			dialog->showMessage("Esto seguro que mejora su concentración en el combate.");
			dialog->showMessage("¡Ahora es más probable que gane!");
			dialog->showMessage("¡Y " + objetive.getName() + " es más probable que pierda!");
		}
		else {
			dialog->showMessage(active.getName() + " gana este brutal encuentro.");
			dialog->showMessage("Enhorabuena a todos los que confiaron en nuestro increíble ganador.");
		}
	}

	// Ataque normal
	else {
		objetive.takeDamage(active.getAttack());
		dialog->showMessage(active.getName() + " golpea duramente a su oponente.");
		if (!objetive.isAlive()) {
			dialog->showMessage(active.getName() + " gana este brutal encuentro.");
			dialog->showMessage("Enhorabuena a todos los que confiaron en nuestro increíble ganador.");
		}
	}
}
