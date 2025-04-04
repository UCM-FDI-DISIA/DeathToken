#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "json.hpp" 
#include <algorithm>
using json = nlohmann::json;

// Tiempo entre turnos (milisegundos)
constexpr int MSEG = 1500;

// Para random
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dist(0.0f, 100.0f);
uniform_int_distribution<int> range(0, 27);  // 28 es el numero de enfrentamientos (n�peleadores * (n�peleadores - 1) /2) y hay 8 peleadores. Incluyendo el 0 lo hace que llegue hasta el 27
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

    // Mostrar la descripci�n de la batalla
    cout << "Descripci�n de la batalla: " << currentMatch.battleDescription << endl;
    cout << "Peleadores: " << currentMatch.fighter1.getName() << " vs " << currentMatch.fighter2.getName() << endl;

    // Asignar un "mindset" aleatorio a los luchadores
    int rndMindset1 = (rand() % MAXMINDSET) + MINMINDSET;
    int rndMindset2 = (rand() % MAXMINDSET) + MINMINDSET;

   
    currentMatch.fighter2.setMindset(rndMindset2);

    if (currentMatch.advantageFighterIndex == 1)
    {
        currentMatch.fighter1.setMindset(rndMindset1 + MOD);
        currentMatch.fighter2.setMindset(rndMindset2 - MOD);
    }
    else
    {
        currentMatch.fighter1.setMindset(rndMindset1 + MOD);
        currentMatch.fighter2.setMindset(rndMindset2 - MOD);
    }
}
