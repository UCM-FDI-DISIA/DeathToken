#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"

#include <iostream>

class SlotsLocura : public GameState {
private:
	const int nColum = 4;
	const int tamCelda = 100;

	int comprobanteIndice;

public:
	SlotsLocura(Game*);
};