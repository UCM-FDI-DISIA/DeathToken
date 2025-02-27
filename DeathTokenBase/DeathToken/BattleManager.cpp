#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <random>
#include "json.hpp" 
#include <algorithm>
using json = nlohmann::json;

BattleManager::BattleManager() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar aleatorio
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
        cout << "Índice de peleador inválido." << endl;
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

void BattleManager::StartBattle() {
    if (battleQueue.empty()) {
        cout << "No hay enfrentamientos en la cola." << endl;
        return;
    }

    // Obtener el primer enfrentamiento en la cola
    Matchup currentMatch = battleQueue.front();
    battleQueue.erase(battleQueue.begin());

    // Mostrar la descripción de la batalla
    cout << "Descripción de la batalla: " << currentMatch.battleDescription << endl;
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
        currentMatch.fighter1.setMindset(rndMindset2 + MOD);
        currentMatch.fighter2.setMindset(rndMindset1 - MOD);
    }
}
