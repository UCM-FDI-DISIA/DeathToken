#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"

#include <iostream>

class MainMenu : public GameState{
private:
	Texture* portada;
	Button* level1;
	Button* level2;
	Button* salir;
public:
	MainMenu(Game*);
	void render() const override;
	void lvl1() const;
	void lvl2() const;
	void exit() const;
};