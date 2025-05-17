#pragma once
#include "gameState.h"
#include "texture.h"
#include "button.h"
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
	~MainMenu() { delete inputNombre; }
	void render() const override;

};