#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"

#include <iostream>
#include <unordered_map>

class Slots : public GameState {
private:
	const int nColum = 3;
	const int tamCelda = 100;
	const int mitadSlot = 25;
	const int alturaCelda = 100;
	const int ditanciaBoton = 450;
	const int tamBoton = 50;
	Carrete* carrete1;
	Carrete* carrete2;
	Carrete* carrete3;
	int comprobanteIndice;

	unordered_map<int, int> puntuaciones;
	
public:
	Slots(Game*);
	void update() override;
};