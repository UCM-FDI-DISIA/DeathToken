#include "Carrete.h"


vector<int> Carrete::vectorAleatorio() {
	vector<int> vector;

	for (int i = 0; i < frecuencias.size(); ++i) {
		for (int j = 0; j < frecuencias[i]; ++j) {
			vector.push_back(i);
		}
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	return vector;
}

Carrete::Carrete(GameState* g, Point2D<int> pos, int w, int h, Texture* celdas, Texture* ic)
	: sceneObject(g, pos, w, h, celdas), iconos(ic), indice(0),carretesRes({0,0,0}) {

	resultante = vectorAleatorio();
}

void Carrete::update() {
	moverIndice();
}

void Carrete::render() const {
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = pos.getX();

	for (int i = 0; i < nCeldas; ++i) {
		r.y = pos.getY() + i * h;
		texture->render(r);

		int ind = indice + i;
		if (ind == resultante.size()) ind = 0;
		else if (ind == resultante.size() + 1) ind = 1;
		iconos->renderFrame(r, 0, resultante[ind]);
	}
}
void Carrete::moverIndice() {
	if (giro) {
		++indice;
		if (indice == resultante.size()) indice = 0;
	}
}
void Carrete::iniciarGiro() {
	giro = true;
}
void Carrete::pararGiro() {
	giro = false;

	for (int i = 0; i < carretesRes.size() - 1; ++i) {

		int ind = indice + i;
		if (ind == resultante.size()) ind = 0;
		else if (ind == resultante.size() + 1) ind = 1;

		carretesRes[i] = resultante[ind];		
	}
}