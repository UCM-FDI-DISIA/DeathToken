
#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Fighter.h"  // Incluye la clase Fighter
#include <iostream>
using namespace std;

class BattleManager {
public:
    // Constructor
    BattleManager(Fighter& f1, Fighter& f2);

    // Método para iniciar la batalla
    void startBattle();

private:
    // Métodos auxiliares
    void generateMatchUps();
    void handleTurn();
    void switchTurn();
    bool checkWinCondition() const;

    // Atributos
    Fighter& fighter1;
    Fighter& fighter2;
    int currentTurn;


};
#endif