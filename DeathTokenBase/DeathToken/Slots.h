#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"

#include <iostream>

class Slots : public GameState {
private:
	const int nColum = 3;
	const int tamCelda = 100;
	
	Button* boton1;
	Button* boton2;
	Button* boton3;

	Carrete* carrete1;
	Carrete* carrete2;
	Carrete* carrete3;
	
public:
	Slots(Game*);
	void render() const override;
};