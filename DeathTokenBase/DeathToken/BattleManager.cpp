#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "json.hpp" 

using json = nlohmann::json;

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
