#pragma once

#include "gameState.h"
#include "Texture.h"
#include "Text.h"
#include <string>

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
	Text* winText;
	int currentWin;
	int wSize = 200;
	int nSize = 300;
	int cSize = 20;
public:
	Award(Game* game, GameState* lastState, int bet, int mWin);
	void render()const  override;
	void update() override;
	std::string getWinMessage(int multiplier);
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
};

