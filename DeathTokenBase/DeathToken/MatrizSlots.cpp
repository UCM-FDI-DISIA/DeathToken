#include "MatrizSlots.h"

MatrizSlots::MatrizSlots(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* ic)
	: sceneObject(g, pos, w, h, celdas), iconos(ic), mat(TAM, vector<int>(TAM)) {

}

void MatrizSlots::update() {
}

void MatrizSlots::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;

	for (int i = 0; i < TAM; ++i) {
		for (int j = 0; j < TAM; ++j) {
			r.x = pos.getX() + i * w;
			r.y = pos.getY() + j * h;
			texture->render(r);
		}
	}
}