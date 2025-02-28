#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"
#include "checkML.h"

#include <iostream>
#include <unordered_map>



class Slots : public GameState {
private:
	constexpr static int N_COLUM = 3;
	constexpr static int TAM_CELDA = 150;
	constexpr static int DISTANCIA_BOTON = TAM_CELDA * 4 + 50;
	constexpr static int TAM_BOTON = 100;

	vector<Carrete*> carretes;
	int comprobanteIndice;
	vector<int> multiplicadores = { 2,3,10,30,90,150,3000 };
	unordered_map<int, int> puntuaciones;

public:
	Slots(Game*);
	~Slots();
	void update() override;
};