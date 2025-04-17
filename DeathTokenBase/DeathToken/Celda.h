#pragma once
#include "button.h"
#include "vector2D.h"
class SlotsInsanity;

class Celda : public Button {
public:
	Celda(SlotsInsanity*, Point2D<int>, int, int, Texture*, Texture*);
	inline ~Celda() {};
	void render() const override;
	inline int getElem() { return elem; }
	inline void setElem(int n) { elem = n; }
	inline void resetElem() { elem = -1; }
private:
	int elem;
	Texture* iconos;
	SlotsInsanity* slots;
};