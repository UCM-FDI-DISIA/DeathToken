#pragma once

#include "gameState.h"
#include "Texture.h"
#include "Text.h"

class Marbles;
class Award : public GameState
{
private:
	int betG;
	int mWinG;
	GameState* state;
	Uint32 startTime;
	Texture* background;
	Text* text;
public:
	Award(Game* game, GameState* lastState, int bet, int mWin);
	void render()const  override;
	void update() override;
	void showMessage() ;
};

