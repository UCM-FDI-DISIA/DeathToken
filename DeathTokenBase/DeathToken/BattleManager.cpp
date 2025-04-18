#include "BattleManager.h"
#include "json.hpp"
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
const int MINMINDSET = 20;
const int MAXMINDSET = 80;
const int MOD = 20;

// Tiempo entre turnos (milisegundos)
constexpr int MSEG = 1500;

// Para random
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dist(0.0f, 100.0f);
uniform_int_distribution<int> range(
  0,
  27);  // 28 es el numero de enfrentamientos (n�peleadores * (n�peleadores - 1) /2) y hay 8 peleadores. Incluyendo el 0 lo hace que llegue hasta el 27
uniform_real_distribution<float> mindsetRange(5, 20);
uniform_real_distribution<float> inicialMindSet(MINMINDSET, MAXMINDSET);

BattleManager::BattleManager()
    : fighters()
    , battleQueue()
    , currentMatch()
    , currentState(BattleState::START)
    , lastTurn(BattleState::START)
    , actionTimer(0)
    , endMatch(false)
{
}

bool BattleManager::loadFightersFromJSON(const string& filename)
{
  ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "No se pudo abrir el archivo de peleadores." << endl;
    return false;
  }

  json j;
  file >> j;

  for (auto& item : j["peleadores"]) {
    Fighter fighter;
    // Convertir el JSON a string antes de pasarlo
    fighter.loadFromJSON(item.dump());
    fighters.push_back(fighter);
  }

  file.close();
  return true;
}

bool BattleManager::loadMatchupsFromJSON(const string& filename)
{
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "No se pudo abrir el archivo de enfrentamientos." << endl;
    return false;
  }

  try {
    json j;
    file >> j;

    // Verificar si "matchups" existe en el JSON
    if (j.find("matchups") == j.end()) {
      cout << "No se encuentra el campo 'matchups' en el JSON." << endl;
      return false;
    }

    // Procesar el JSON y cargar los enfrentamientos
    for (auto& item : j["matchups"]) {
      int id1 = item["F1"];
      int id2 = item["F2"];
      int advantageFighterIndex = item["advantageFighterIndex"];
      string battleDescription = item["battleDescription"];

      if (id1 < 0 || id1 >= fighters.size() || id2 < 0 ||
          id2 >= fighters.size()) {
        cout << "�ndice de peleador inv�lido." << endl;
        continue;
      }

      Matchup matchup;
      matchup.fighter1 = fighters[id1];
      matchup.fighter2 = fighters[id2];
      matchup.advantageFighterIndex = advantageFighterIndex;
      matchup.battleDescription = battleDescription;

      battleQueue.push_back(matchup);
    }
  }
  catch (const json::parse_error& e) {
    cout << "Error al procesar el JSON: " << e.what() << endl;
    return false;
  }

  file.close();
  return true;
}

void BattleManager::StartBattle()
{
  assert(!battleQueue.empty());

  int i = range(gen);
  currentMatch = battleQueue[i];

  cout << "Descripci�n de la batalla: " << currentMatch.battleDescription
       << endl;
  cout << "Peleadores: " << currentMatch.fighter1.getName() << " vs "
       << currentMatch.fighter2.getName() << endl;

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

  currentState = BattleState::START;
}

void BattleManager::Update(float deltaTime)
{
  actionTimer += deltaTime;

  if (actionTimer >= ACTIONDELAY) {
    actionTimer = 0.0f;  // Reiniciamos el temporizador

    switch (currentState) {
      case BattleState::START:
        cout << "Iniciando batalla..." << endl;
        currentState =
          BattleState::PLAYER1_TURN;  // Cambiamos al turno del jugador 1
        lastTurn = BattleState::PLAYER1_TURN;  // Inicializamos el �ltimo turno
        break;

      case BattleState::PLAYER1_TURN:
        cout << "Turno de " << currentMatch.fighter1.getName() << endl;
        ActionTurn(currentMatch.fighter1, currentMatch.fighter2);
        currentState = BattleState::EVALUATE;  // Cambiamos a evaluaci�n
        break;

      case BattleState::PLAYER2_TURN:
        cout << "Turno de " << currentMatch.fighter2.getName() << endl;
        ActionTurn(currentMatch.fighter2, currentMatch.fighter1);
        currentState = BattleState::EVALUATE;  // Cambiamos a evaluaci�n
        break;

      case BattleState::EVALUATE:
        cout << "Evaluando resultado..." << endl;
        if (!currentMatch.fighter1.isAlive() ||
            !currentMatch.fighter2.isAlive()) {
          currentState = BattleState::END;  // Si alguien muri�, terminamos
        }
        else {
          // Cambiar al siguiente turno
          if (lastTurn == BattleState::PLAYER1_TURN) {
            currentState = BattleState::PLAYER2_TURN;
            lastTurn =
              BattleState::PLAYER2_TURN;  // Actualizamos el �ltimo turno
          }
          else {
            currentState = BattleState::PLAYER1_TURN;
            lastTurn =
              BattleState::PLAYER1_TURN;  // Actualizamos el �ltimo turno
          }
        }
        break;

      case BattleState::END:
        Fighter* winner = currentMatch.fighter1.isAlive() ?
                            &currentMatch.fighter1 :
                            &currentMatch.fighter2;
        cout << "�La batalla ha terminado! El ganador es: " << winner->getName()
             << endl;
        break;
    }
  }
}


void BattleManager::ActionTurn(Fighter& active, Fighter& objetive)
{
  float hitBackProb = 2.5f + 15.0f * (50.0f - active.getMindset()) / 200.0f;
  float failProb = 7.5f + 12.5f * (50.0f - active.getMindset()) / 100.0f;
  float criticalProb = 10.0f + 30.0f * (active.getMindset() - 50.0f) / 100.0f;

  cout << "�" << active.getName()
       << " se dispone a atacar ferozmente a su enemigo!\n";
  float prob = dist(gen);

  // Golpearse a s� mismo
  if (prob < hitBackProb) {
    active.takeDamage(active.getAttack());
    cout << "�Pero se ha golpeado a s� mismo, " << active.getName()
         << " se ha vuelto loco!\n";
    if (active.isAlive()) {
      active.reduceMindset(mindsetRange(gen));
      cout << "Esto seguro que mina su concentraci�n en el combate\n";
      cout << "�Ahora es m�s probable que pierda!\n";
    }
    else {
      cout << "�LA CATASTROFE SE HIZO REALIDAD!\n";
      cout << "�" << active.getName() << " ha ca�do por su propia mano!\n";
    }
  }

  // Fallo
  else if (prob < hitBackProb + failProb) {
    cout << active.getName()
         << " lamentablemente su golpe ha fallado a su objetivo.\n";
    active.reduceMindset(mindsetRange(gen));
    cout << "Esto seguro que mina su concentraci�n en el combate.\n";
    cout << "�Ahora es m�s probable que pierda!\n";
  }

  // Cr�tico
  else if (prob < hitBackProb + failProb + criticalProb) {
    objetive.takeDamage(active.getAttack() * 3);
    cout << "�MADRE M�A, CR�TICO! " << active.getName()
         << " acaba de destrozar a su oponente.\n";
    cout
      << " Tras semejante golpe tal vez deban replantearse el resultado del combate.\n";
    if (objetive.isAlive()) {
      active.boostMindset(mindsetRange(gen));
      objetive.reduceMindset(mindsetRange(gen));
      cout << "Esto seguro que mejora su concentraci�n en el combate.\n";
      cout << "�Ahora es m�s probable que gane!\n";
      cout << "�Y " << objetive.getName() << " es m�s probable que pierda!\n";
    }
    else {
      cout << active.getName() << " gana este brutal encuentro.\n";
      cout
        << "Enhorabuena a todos los que confiaron en nuestro incre�ble ganador.\n";
    }
  }

  // Ataque normal
  else {
    objetive.takeDamage(active.getAttack());
    cout << active.getName() << " golpea duramente a su oponente.\n";
    if (!objetive.isAlive()) {
      cout << active.getName() << " gana este brutal encuentro.\n";
      cout
        << "Enhorabuena a todos los que confiaron en nuestro incre�ble ganador.\n";
    }
  }
}

void BattleManager::ExecuteTurns(Matchup currentMatch)
{
  // Empieza el que tiene menos habilidad
  if (currentMatch.fighter1.getAbility() > currentMatch.fighter2.getAbility()) {
    Fighter temp = currentMatch.fighter1;
    currentMatch.fighter1 = currentMatch.fighter2;
    currentMatch.fighter2 = temp;
  }

  cout << "Comenzar� la pelea " << currentMatch.fighter1.getName() << ".\n";
  cout << "Mucha suerte a todos los jugadores.\n";
  cout << "\n";

  auto lastTime = chrono::high_resolution_clock::now();

  while (currentState != BattleState::END && !endMatch) {  // Continuar hasta que la batalla termine
    auto currentTime = chrono::high_resolution_clock::now();
    float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;
    Update(deltaTime);  // Pasamos el delta time a Update
  }

  // Mostrar el resultado final
  if (!currentMatch.fighter1.isAlive()) {
    cout << currentMatch.fighter2.getName() << " gana la pelea.\n";
  }
  else {
    cout << currentMatch.fighter1.getName() << " gana la pelea.\n";
  }
}