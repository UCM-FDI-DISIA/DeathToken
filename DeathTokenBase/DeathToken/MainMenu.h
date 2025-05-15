#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"

#include <iostream>

class MainMenu : public GameState{
private:
	Texture* back;
	//Input para Ivan
	Button* salir;
	Button* begin;
public:
	MainMenu(Game*);
	void render() const override;
};