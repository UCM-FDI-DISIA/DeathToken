#pragma once

#include "gameState.h"
#include "UI.h"

class Marbles : public GameState
{
private:
	UIChips* ui;
public:
	Marbles(Game* game);
};

