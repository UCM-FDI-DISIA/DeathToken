#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"



#include <iostream>

class PauseState : public GameState {
private:

	Button* cont;
	Button* menu;
	Button* salir;
public:
	PauseState(Game*);
	void render() const override;
	void continuar() const;
	void backToMenu() const;
	void exit() const;
};