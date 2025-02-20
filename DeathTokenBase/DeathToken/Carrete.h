#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
class Carrete : public sceneObject {
private:
	const int nCeldas = 3;
	const int NUM_ELEMS = 18;
	const vector<int> frecuencias = { 4,3,3,3,2,2,1 };
	vector<int> resultante;
	int indice;
	Texture* iconos;
	bool giro = false;

public:
	Carrete(GameState*,Point2D<int>, int, int, Texture*,Texture*);
	~Carrete() {};
	vector<int> vectorAleatorio();
	void moverIndice();
	int getIndice() const { return indice; };
	void iniciarGiro();
	void pararGiro();
	void render() const override;
	void update() override;
};
