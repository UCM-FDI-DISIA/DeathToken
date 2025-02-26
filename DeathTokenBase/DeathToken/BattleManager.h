#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Fighter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const int MINMINDSET = 20;
const int MAXMINDSET = 80 - MINMINDSET;
const int MOD = 20;
struct Matchup {
    Fighter fighter1;
    Fighter fighter2;
    int advantageFighterIndex;
    string battleDescription;
};

class BattleManager {
public:
    BattleManager();

    bool loadFightersFromJSON(const string& filename);
    void StartBattle();

private:
    vector<Fighter> fighters;
    vector<Matchup> battleQueue;  // Cola de enfrentamientos
};

#endif
