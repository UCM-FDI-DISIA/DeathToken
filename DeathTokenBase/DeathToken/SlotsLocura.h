#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"
#include "MatrizSlots.h"

#include <iostream>


class SlotsLocura : public GameState {
private:
	constexpr static int N_COLUM = 4;
	constexpr static int TAM_CELDA = 150;
	MatrizSlots* mat;

public:
	SlotsLocura(Game*);
};