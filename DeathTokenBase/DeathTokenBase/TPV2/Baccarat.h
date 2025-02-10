#pragma once
#include <cstdlib>
#include <vector>
using namespace std;
struct Tapete {
	vector<int> banca;
	vector<int> jugador;
};

class Baccarat
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
	Baccarat();
	~Baccarat();

	void repartir();
	void terceraBanca();
	int generaAleatorio();
};

