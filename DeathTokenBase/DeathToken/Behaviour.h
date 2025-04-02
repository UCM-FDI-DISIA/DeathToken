#pragma once
#include "SlotsNormal.h"
#include "SlotsLocura.h"
#include "Baccarat.h"
#include "BaccaratFlip.h"
#include "Peleas.h"
#include "Marbles.h"
#include "marblesInsanity.h"
#include "gameState.h"


class Behaviour {	
private:
	GameState* juego;
public:
	GameState* loadMadness(int index, Game* g) {
		switch (index)
		{
		case 0:
			juego = new SlotsNormal(g);
			break;
		case 1:
			juego = new Baccarat(g);
			break;
		case 2:
			juego = new Marbles(g);
			break;
		case 3:
			juego = new Peleas(g);
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
		case 1:
			juego = new BaccaratFlip(g);
			break;
		case 2:
			juego = new MarblesInsanity(g);
			break;
		default:
			juego = new GameState(g);
			break;
		}
		return juego;
		delete juego;
	};
};