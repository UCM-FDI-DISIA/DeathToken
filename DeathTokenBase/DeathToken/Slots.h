#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"
#include "checkML.h"
#include "UI.h"

#include <iostream>
#include <unordered_map>



class Slots : public GameState {
protected:
	constexpr static int N_COLUM = 3;
	constexpr static float X_CELDA = (200 / 1920.0);
	constexpr static float Y_CELDA = (200 / 1080.0);
	constexpr static float DISTANCIA_BOTON = (200 * 3 + 50)/1080.0;
	constexpr static float X_BOTON = (150/1920.0);
	constexpr static float Y_BOTON = (150 / 1080.0);

	vector<Carrete*> carretes;
	int comprobanteIndice;
	vector<int> multiplicadores = { 2,3,10,30,90,150,3000 };
	unordered_map<int, int> puntuaciones;
	UISlots* ui;

	HUDBet* hud;

public:

	Slots(Game*);
	~Slots();
	void update() override;
	void render() const override;
	void iniciarGiro();
};