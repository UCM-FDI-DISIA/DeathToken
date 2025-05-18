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

	std::vector<Carrete*> carretes; // vector con los tres carretes que conforman la maquina
	int comprobanteIndice; // Indice para saber cuando se han parado los tres carretes
	int canalSonidoGiro = -1;
public:

	SlotsNormal(Game*);
	~SlotsNormal();
	void update() override;
	void render() const override;
	bool iniciarGiro() override;
};