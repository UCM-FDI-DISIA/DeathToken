#pragma once

#include "gameState.h"
#include "texture.h"
#include "text.h"
#include <string>

class Award : public GameState
{
private:
	long long betG;
	long long mWinG;
	GameState* state;
	Uint32 startTime;
	Texture* background;
	Text* text;
	Text* winText;
	long long currentWin;
	int wSize = 200;
	int nSize = 300;
	int cSize = 20;
public:
	Award(Game* game, GameState* lastState, long long bet, long long mWin);
	~Award() {};
	void render()const  override;
	void update() override;
	std::string getWinMessage(int multiplier);
	 int relativeX(const float& n);
	 int relativeY(const float& n);
};

