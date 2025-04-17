#include "carrete.h"

vector<int> Carrete::vectorAleatorio() {
	vector<int> vector;

	for (int i = 0; i < frecuencias.size(); ++i) {
		for (int j = 0; j < frecuencias[i]; ++j) {
			vector.push_back(i);
		}
	}

	unsigned int seed =(unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	return vector;
}

Carrete::Carrete(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* ic)
	: sceneObject(g, pos, w, h, celdas), iconos(ic), indice(0), act(0) {

	resultante = vectorAleatorio();
}
Carrete:: ~Carrete() {
	iconos = nullptr;
}

void Carrete::update() {
		if (act == delta) {
			if (giro) indice = (indice + 1) % resultante.size();
			act = 0;
		}
		else act++;
}

void Carrete::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = pos.getX();

	for (int i = 0; i < NUM_ELEMS; ++i) {
		r.y = pos.getY() + i * h;
		texture->render(r);

		int ind = indice - i;
		if (ind < 0) ind += (int)resultante.size();
		iconos->renderFrame(r, 0, resultante[ind]);
	}
}
void Carrete::iniciarGiro() {
	giro = true;
}
void Carrete::pararGiro() {
	if (giro) {
		for (int i = 0; i < NUM_ELEMS; ++i) {
			int ind = indice - i;
			if (ind < 0) ind += (int)resultante.size();
			carretesRes.push_back(resultante[ind]);
		}
		giro = false;
	}
}