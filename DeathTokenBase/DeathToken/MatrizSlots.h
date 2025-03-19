#pragma once
#include "sceneObject.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
class MatrizSlots : public sceneObject {
private:
	Texture* iconos;
	vector<vector<int>> mat;
	int fil; int col;
public:
	MatrizSlots(GameState*, Point2D<int>, int, int, Texture*, Texture*, int, int);
	~MatrizSlots() {};

	void render() const override;
	void update() override;

	virtual Collision hit(const SDL_Rect&, Collision::Target) { return NO_COLLISION; }
};
