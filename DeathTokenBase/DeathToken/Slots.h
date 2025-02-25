#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"

#include <iostream>
#include <unordered_map>

#define N_COLUM 3
#define TAM_CELDA 100
#define DISTANCIA_BOTON 450
#define TAM_BOTON 50

class Slots : public GameState {
private:

	Carrete* carrete1;
	Carrete* carrete2;
	Carrete* carrete3;
	int comprobanteIndice;
	vector<int> multiplicadores = {2,3,10,30,90,150,3000 };
	unordered_map<int, int> puntuaciones;
	
public:
	Slots(Game*);
	void update() override;
};