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


class BattleManager {
public:
	BattleManager(DialogueBox* dialog, Game* g);

	void StartBattle();

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
	Game* game;
	DialogueBox* dialog;
	Matchup currentMatch;
	BattleState currentState;
	BattleState lastTurn;
	void ActionTurn(Fighter& active, Fighter& objetive);

	inline void EndMatch() {
		endMatch = true;
	}
};
#endif
