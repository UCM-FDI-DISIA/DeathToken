#pragma once
#include "sceneObject.h"

class Celda : public sceneObject {
public:
	Celda(GameState*, Point2D<int>, int, int, Texture*, Texture*);
	~Celda() {};
	inline int getElem() { return elem; }
	inline void setElem(int n) { elem = n; }
private:
	int elem;
};