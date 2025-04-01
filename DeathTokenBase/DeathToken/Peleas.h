#pragma once
#include "gameState.h"
#include "BattleManager.h"
class Peleas : public GameState
{
public:
	Peleas(Game* game);
private:
	BattleManager* _battleM;
};

