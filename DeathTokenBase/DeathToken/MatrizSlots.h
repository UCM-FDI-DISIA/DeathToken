#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
class MatrizSlots : public sceneObject {
private:
	const int TAM = 4;
	const int NUM_ELEMS = 18;
	Texture* iconos;
	vector<vector<int>> mat;

public:
	MatrizSlots(GameState*, Point2D<int>, int, int, Texture*, Texture*);
	~MatrizSlots() {};

	void render() const override;
	void update() override;
};
