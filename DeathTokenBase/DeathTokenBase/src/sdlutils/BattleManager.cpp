#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

BattleManager::BattleManager() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar aleatorio
}

// Cargar luchadores desde archivos JSON
bool BattleManager::loadFightersFromJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo de peleadores." << endl;
        return false;
    }

    json j;
    file >> j;

    // Procesar el JSON y cargar los peleadores
    for (auto& item : j) {
        Fighter fighter;
        fighter.loadFromJSON(item);
        fighters.push_back(fighter);
    }

    file.close();
    return true;
}

bool BattleManager::loadMatchupsFromJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo de enfrentamientos." << endl;
        return false;
    }

    json j;
    file >> j;

    // Procesar el JSON y cargar los enfrentamientos
    for (auto& item : j["matchups"]) {
        int id1 = item["F1"];
        int id2 = item["F2"];
        int advantageFighterIndex = item["advantageFighterIndex"];
        string battleDescription = item["battleDescription"];

      
        if (id1 < 0 || id1 >= fighters.size() || id2 < 0 || id2 >= fighters.size()) {
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

    file.close();
    return true;
}

void BattleManager::generateMatchQueue() {
    // Ya no es necesario hacer nada aquí, la cola se genera directamente al cargar los matchups
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
