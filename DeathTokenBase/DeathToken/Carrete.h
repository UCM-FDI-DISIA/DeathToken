#pragma once
#include "sceneObject.h"
#include <vector>
class Carrete : public sceneObject {
private:
	const int NUM_ELEMS = 18;
	const vector<int> frecuencias = { 4,3,3,3,2,2,1 };
	vector<int> resultante;
	int index;
	Point2D<> posicion;
	Texture* simbolos; 

public:
	Carrete(PlayState*,Texture*,Texture*);
	~Carrete() {};
	vector<int> vectorAleatorio();
	void render() const override;
	void update() override;
};
