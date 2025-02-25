#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#define NUM_ELEMS 3
class Carrete : public sceneObject {
private:
	const vector<int> frecuencias = { 4,3,3,3,2,2,1};
	vector<int> resultante;
	int indice;
	Texture* iconos;
	bool giro = false;
	vector<int>carretesRes;

public:
	Carrete(GameState*,Point2D<int>, int, int, Texture*,Texture*);
	~Carrete() {};
	vector<int> vectorAleatorio();
	void moverIndice();
	int getIndice() const { return indice; };
	vector<int> getCarrete() const { return carretesRes; };
	void deleteCarrete() { carretesRes.erase(carretesRes.erase(carretesRes.begin(), carretesRes.end() - 1)); }
	void iniciarGiro();
	void pararGiro();
	void render() const override;
	void update() override;

	virtual Collision hit(const SDL_Rect&, Collision::Target) { return NO_COLLISION; }
};
