#include "Carrete.h"
Carrete::Carrete(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* iconos)
	: sceneObject(g, pos, w, h, celdas), simbolos(iconos) {
}
vector<int> Carrete::vectorAleatorio() {
	vector<int> vector;
	for (int i = 0; i < NUM_ELEMS; ++i) {
		for (int j : frecuencias) {
			vector.push_back(i);
		}
	}

	return vector;
}
void Carrete::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = pos.getX();

	for (int i = 0; i < nCeldas; ++i) {
		r.y = pos.getY() + i * h;
		texture->render(r);
	}
}