#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Fighter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "json.hpp"  // Incluir la librería JSON

using namespace std;
using json = nlohmann::json;

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
    bool loadMatchupsFromJSON(const string& filename);
    void generateMatchQueue();
    void StartBattle();

private:
    vector<Fighter> fighters;
    vector<Matchup> battleQueue;  // Cola de enfrentamientos
};

#endif
