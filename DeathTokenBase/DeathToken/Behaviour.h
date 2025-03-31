#pragma once
#include "Slots.h"
#include "SlotsLocura.h"
#include "Baccarat.h"
#include "Peleas.h"
#include "gameState.h"

class Behaviour {	
private:
	GameState* juego;
public:
	GameState* loadMadness(int index, Game* g) {
		switch (index)
		{
		case 0:
			juego = new Slots(g);
			break;
		default:
			juego = new GameState(g);
			break;
		}
		return juego;
		delete juego;
	};
	GameState* loadSanity(int index, Game* g) {
		switch (index)
		{
		case 0:
			juego = new SlotsLocura(g);
			break;
		default:
			juego = new GameState(g);
			break;
		}
		return juego;
		delete juego;
	};
};