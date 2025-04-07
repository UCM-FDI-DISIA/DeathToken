#pragma once
#include "gameState.h"
#include "texture.h"
#include "button.h"

#include <iostream>

class EndState : public GameState {
private:
	Texture* result;
	SDL_Rect box;
	Button* menu;
	Button* salir;
public:
	EndState(Game*, bool);
	void render() const override;
	void backToMenu() const;
	void exit() const;
};