#pragma once
#include "sceneObject.h"
#include <vector>
class Carrete : public sceneObject {
private:
	const int nCeldas = 3;
	const int NUM_ELEMS = 21;
	const vector<int> frecuencias = { 4,3,3,3,2,2,1 };
	vector<int> resultante;
	int index;
	Texture* simbolos; 

public:
	Carrete(GameState*,Point2D<int>, int, int, Texture*,Texture*);
	~Carrete() {};
	vector<int> vectorAleatorio();
	void render() const override;
	void update() override {}
};
