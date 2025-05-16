#include "carrete.h"

vector<int> Carrete::vectorAleatorio() {
	vector<int> vector;
	// genera un vector en base a las frecuencias
	for (int i = 0; i < frecuencias.size(); ++i) {
		for (int j = 0; j < frecuencias[i]; ++j) {
			vector.push_back(i);
		}
	}
	// desorden aleatorio del vector
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	return vector;
}

Carrete::Carrete(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* ic)
	: sceneObject(g, pos, w, h, celdas), iconos(ic), indice(0), act(0) {
	// genera el vector aleatorio
	resultante = vectorAleatorio();
}
Carrete:: ~Carrete() {
	deleteCarrete();
	iconos = nullptr;
}

void Carrete::update() {
	// cada 'delta' updates actualiza el carrete
	if (act == delta) {
		// Avanza el indice en uno
		if (giro) { indice = (indice + 1) % resultante.size(); }
		act = 0;
	}
	else act++;
}

void Carrete::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = pos.getX();
	// render de las tres celdas y sus iconos
	for (int i = 0; i < NUM_ELEMS; ++i) {
		r.y = pos.getY() + i * h;
		texture->render(r);

		// El indice indica la posición de la casilla de abajo, por lo que las otras dos calculan indice - 1 o -2 correspondientemente
		int ind = indice - i;
		if (ind < 0) { ind += (int)resultante.size(); }
		iconos->renderFrame(r, 0, resultante[ind]);
	}
}
void Carrete::iniciarGiro() {
	giro = true;
}
void Carrete::pararGiro() {
	// Crea el carrete resulatante con los tres iconos  que se muestran
	for (int i = 0; i < NUM_ELEMS; ++i) {
		int ind = indice - i;
		if (ind < 0) ind += (int)resultante.size();
		carretesRes.push_back(resultante[ind]);
	}
	giro = false;
}