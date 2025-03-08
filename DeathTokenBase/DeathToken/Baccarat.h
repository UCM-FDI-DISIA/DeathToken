#pragma once
#include <cstdlib>
#include <vector>
#include "gameState.h"
using namespace std;
struct Tapete {
	vector<int> banca;
	vector<int> jugador;
};

class Baccarat : public GameState
{
protected:
	Tapete tap;
	vector<int> cartas;
	int numAleatorio;
	int sumaJug;
	int sumaBanca;
	const int xDos = 2;
	const int xOcho = 8;
	//bool locura; global?
public:
	Baccarat(Game* game);
	

	void repartir();
	void terceraBanca();
	int generaAleatorio();
};