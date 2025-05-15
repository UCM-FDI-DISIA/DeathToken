#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "inputBox.h"

#include <iostream>

class MainMenu : public GameState{
private:
	Texture* back;
	InputBox* inputNombre;
	Button* salir;
	Button* begin;
public:
	MainMenu(Game*);
	void render() const override;

};