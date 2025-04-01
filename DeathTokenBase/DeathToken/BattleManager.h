#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "DialogueBox.h"
#include "Fighter.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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
	BattleManager(DialogueBox* dialog);

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
	inline const string& getBattleDescription() const { return currentMatch.battleDescription; }

	void Update(float deltaTime);

private:
	float actionTimer;  // Temporizador para controlar retrasos
	const float ACTIONDELAY = 2000;
	bool endMatch;
	DialogueBox* dialog;
	vector<Fighter> fighters;
	vector<Matchup> battleQueue;  // Cola de enfrentamientos
	Matchup currentMatch;
	BattleState currentState;
	BattleState lastTurn;
	void ActionTurn(Fighter& active, Fighter& objetive);

	inline void EndMatch() {
		endMatch = true;
	}
};
#endif
