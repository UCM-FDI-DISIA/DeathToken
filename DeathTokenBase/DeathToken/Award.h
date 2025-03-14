#pragma once

#include "gameState.h"

class Award : public GameState
{
private:
	int betG;
	int mWinG;
public:
	Award(Game* game, GameState lastState, int bet, int mWin);
	void render() const override;
	void update() override;
	void showMessage() ;
};

