#pragma once
#include "gameState.h"
#include "hud.h"
#include "ui.h"
#include <SDL_ttf.h>

class InputBox;

class PeleasInsanity : public GameState
{
public:
	PeleasInsanity(Game* game);
	void render() const override;
	void update() override;
	void StartBattle();

private:	
	InputBox* input1;
};

