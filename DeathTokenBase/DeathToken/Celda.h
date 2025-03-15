#pragma once
#include "Button.h"
#include "Vector2D.h"
class SlotsLocura;

class Celda : public Button {
public:
	Celda(SlotsLocura*, Point2D<int>, int, int, Texture*, Texture*);
	inline ~Celda() {};
	void render() const override;
	inline int getElem() { return elem; }
	inline void resetElem() { elem = -1; }
private:
	int elem;
	Texture* iconos;
	SlotsLocura* slots;
};