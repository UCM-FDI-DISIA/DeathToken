#pragma once

#include "gameState.h"
#include "UI.h"

class Marbles : public GameState
{
private:
	UISlots* ui;
public:
	Marbles(Game* game);
};

