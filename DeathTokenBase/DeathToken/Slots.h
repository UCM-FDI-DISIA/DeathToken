#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"

#include <iostream>

class Slots : public GameState {
private:
	const int nColum = 3;
	const int tamCelda = 100;
public:
	Slots(Game*);
};