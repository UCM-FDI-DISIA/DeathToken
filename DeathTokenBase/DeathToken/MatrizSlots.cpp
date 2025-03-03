#include "MatrizSlots.h"

MatrizSlots::MatrizSlots(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* ic, int filas, int colum)
	: sceneObject(g, pos, w, h, celdas), iconos(ic), mat(filas, vector<int>(colum)), fil (filas), col (colum)
{

}

void MatrizSlots::update() {
}

void MatrizSlots::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;

	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < fil; ++j) {
			r.x = pos.getX() + i * w;
			r.y = pos.getY() + j * h;
			texture->render(r);
		}
	}
}