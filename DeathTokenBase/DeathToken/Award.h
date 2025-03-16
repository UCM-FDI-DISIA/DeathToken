#pragma once

#include "gameState.h"
#include "Texture.h"


class Marbles;
class Award : public GameState
{
private:
	int betG;
	int mWinG;
	Marbles* state;
	Uint32 startTime;
	Texture* background;

public:
	Award(Game* game, Marbles* lastState, int bet, int mWin);
	void render()const  override;
	void update() override;
	void showMessage() ;
};

