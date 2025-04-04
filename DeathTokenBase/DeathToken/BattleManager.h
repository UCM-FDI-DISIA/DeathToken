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
enum class BattleState { START, PLAYER1_TURN, PLAYER2_TURN, EVALUATE, END };
struct Matchup {
    Fighter fighter1;
    Fighter fighter2;
    int advantageFighterIndex = 0;
    string battleDescription;
};

class BattleManager {
public:
    BattleManager();

    ~BattleManager() {
        EndMatch();
        fighters.clear();
        battleQueue.clear();
    }
    
    // Carga de objetos del json
    bool loadFightersFromJSON(const string& filename);
    bool loadMatchupsFromJSON(const string& filename);

    void StartBattle();
    void ExecuteTurns(Matchup currentMatch);

    inline const Matchup& getCurrentMatchUp() const { return currentMatch; }
    inline const Fighter& getFigther1() const { return currentMatch.fighter1; }
    inline const Fighter& getFigther2() const { return currentMatch.fighter2; }
    inline const BattleState& getBattleState() const { return currentState; }

  private:
    float actionTimer;  // Temporizador para controlar retrasos
    const float ACTIONDELAY = 2;
    bool endMatch;
    vector<Fighter> fighters;
    vector<Matchup> battleQueue;  // Cola de enfrentamientos
    Matchup currentMatch;
    BattleState currentState;
    BattleState lastTurn;
    void Update(float deltaTime);
    void ActionTurn(Fighter& active, Fighter& objetive);

    inline void EndMatch() {
        endMatch = true;
    }
};
#endif
