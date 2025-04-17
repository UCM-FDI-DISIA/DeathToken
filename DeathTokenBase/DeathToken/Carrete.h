#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

class Carrete : public sceneObject {
private:
	constexpr static int NUM_ELEMS = 3;

	const vector<int> frecuencias = { 4,3,3,3,2,2,1};
	vector<int> resultante;
	int indice;
	Texture* iconos;
	bool giro = false;
	vector<int>carretesRes;
	
	vector<int> vectorAleatorio();

	const int delta = 1;
	int act;

public:
	Carrete(GameState*,Point2D<int>, int, int, Texture*,Texture*);
	~Carrete();
	
	int getIndice() const { return indice; }
	bool getParada() { return giro; }
	vector<int> getCarrete() const { return carretesRes; }
	void deleteCarrete() { carretesRes.erase(carretesRes.erase(carretesRes.begin(), carretesRes.end() - 1)); }
	void iniciarGiro();
	void pararGiro();
	void render() const override;
	void update() override;
};
