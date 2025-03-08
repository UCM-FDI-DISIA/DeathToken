#pragma once
#include "gameState.h"
#include "BattleManager.h"
class Peleas : public GameState
{
public:
	Peleas(Game* game);
	/*void render() const override;*/
private:
	BattleManager* _battleM;
};

