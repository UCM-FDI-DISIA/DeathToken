#include "BattleManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

BattleManager::BattleManager() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar aleatorio
}

// Cargar luchadores desde archivos JSON
bool BattleManager::loadFighters(const std::vector<std::string>& filenames) {
    for (const auto& filename : filenames) {
        Fighter fighter;
        if (fighter.loadFromJSON(filename)) {
            fighters.push_back(fighter);
        }
        else {
            std::cout << "Error al cargar el luchador desde el archivo: " << filename << std::endl;
        }
    }
    return true;
}