#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"

class PlayState;

#include <iostream>

class PauseState : public GameState {
private:
	PlayState* background;
	Button* cont;
	Button* menu;
	Button* salir;
public:
	PauseState(Game*, PlayState*);
	void render() const override;
	void continuar() const;
	void backToMenu() const;
	void exit() const;
};