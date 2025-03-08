#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Fighter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "DialogueBox.h"

using namespace std;

struct Matchup {
    Fighter fighter1;
    Fighter fighter2;
    int advantageFighterIndex = 0;
    string battleDescription;
};

class BattleManager {
public:
    BattleManager();
    
    // Carga de objetos del json
    bool loadFightersFromJSON(const string& filename);
    bool loadMatchupsFromJSON(const string& filename);

    void StartBattle();
    void ExecuteTurns(Matchup currentMatch);

    inline Fighter getFigther1() const { /*assert(currentMatch.advantageFighterIndex != 0);*/ return currentMatch.fighter1; }
    inline Fighter getFigther2() const { /*assert(currentMatch.advantageFighterIndex != 0);*/ return currentMatch.fighter2; }

private:
    vector<Fighter> fighters;
    vector<Matchup> battleQueue;  // Cola de enfrentamientos
    Matchup currentMatch;
    
    
    void ActionTurn(Fighter& active, Fighter& objetive);
};
#endif
