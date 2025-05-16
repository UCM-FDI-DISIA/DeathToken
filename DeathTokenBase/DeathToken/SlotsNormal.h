#pragma once
#include "slots.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Carrete;

class SlotsNormal : public Slots {
protected:
	constexpr static int N_COLUM = 3;
	constexpr static float TAM_CELDA = 210;
	constexpr static float TAM_BOTON = 150;

<<<<<<< Updated upstream
	std::vector<Carrete*> carretes; // vector con los tres carretes que conforman la maquina
	int comprobanteIndice; // Indice para saber cuando se han parado los tres carretes
	
=======
	std::vector<Carrete*> carretes;
	int comprobanteIndice;
	int canalSonidoGiro = -1;

	int getResult() override { return 0; }

>>>>>>> Stashed changes
public:

	SlotsNormal(Game*);
	~SlotsNormal();
	void update() override;
	void render() const override;
	void iniciarGiro() override;
};