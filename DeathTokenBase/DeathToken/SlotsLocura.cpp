#include "SlotsLocura.h"
#include <chrono>
#include "Celda.h"
using namespace std;

vector<int> SlotsLocura::vectorAleatorio() {
	vector<int> vector;

	for (int i = 0; i < frecuencias.size(); ++i) {
		for (int j = 0; j < frecuencias[i]; ++j) {
			vector.push_back(i);
		}
	}

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	return vector;
}
SlotsLocura::SlotsLocura(Game* g) : GameState(g), indice(0), mat(N_COLUM)
{
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			Celda* c = new Celda(this, { j * TAM_CELDA, i * TAM_CELDA }, TAM_CELDA, TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS));
			mat[i].push_back(c);
			addObjects(c);
		}
	}
	resultante = vectorAleatorio();
}

void SlotsLocura::update() {
	bool full = true;
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			if (mat[i][j]->getElem() == -1) {
				full = false;
				break;
			}
		}
		if (!full) break;
	}
	if (full) {
		for (int i = 0; i < N_COLUM; ++i)
			for (int j = 0; j < N_COLUM; ++j)
				mat[i][j]->resetElem();
	}
	GameState::update();
}

int SlotsLocura::getNext() {
	int n = resultante[indice];
	indice = (indice + 1) % resultante.size();
	return n;
}
