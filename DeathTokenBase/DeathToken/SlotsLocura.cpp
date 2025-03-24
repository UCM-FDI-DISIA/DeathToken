#include "SlotsLocura.h"
#include <chrono>
#include <random>
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
SlotsLocura::SlotsLocura(Game* g) : GameState(g), indice(0), mat(N_COLUM), turnoPlayer(true)
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
	bool line = checkBoard();
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
	if (full || line) {
		for (int i = 0; i < N_COLUM; ++i)
			for (int j = 0; j < N_COLUM; ++j)
				mat[i][j]->resetElem();
	}

	if (!turnoPlayer) IA();

	GameState::update();
}
void SlotsLocura::render() const {
	SDL_Rect box(Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 2, TAM_CELDA, TAM_CELDA);
	game->getTexture(CELDA)->render(box);
	game->getTexture(ICONOS)->renderFrame(box, 0, resultante[indice]);
	GameState::render();
}

int SlotsLocura::getNext() {
	if (turnoPlayer) {
		int n = resultante[indice];
		indice = (indice + 1) % resultante.size();
		turnoPlayer = false;
		return n;
	}
	else return -1;
}

bool SlotsLocura::checkBoard() const {
	// Revisi�n filas y columnas
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i][j + 1]->getElem() && mat[i][j]->getElem() == mat[i][j + 2]->getElem()) {
				return true;
			}
			else if (mat[j][i]->getElem() != -1 &&
				mat[j][i]->getElem() == mat[j + 1][i]->getElem() && mat[j][i]->getElem() == mat[j + 2][i]->getElem()) {
				return true;
			}
		}
	}
	// Revisi�n diagonales principales
	for (int i = 0; i < N_COLUM - 2; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i + 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i + 2][j + 2]->getElem()) {
				return true;
			}
		}
	}
	// Revisi�n diagonales secundarias
	for (int i = N_COLUM - 1; i > 1; --i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i - 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i - 2][j + 2]->getElem()) {
				return true;
			}
		}
	}

	return false;
}

void SlotsLocura::IA() {
	bool placed = false;
	while (!placed) {
		int x = rand() % N_COLUM;
		int y = rand() % N_COLUM;
		if (mat[x][y]->getElem() == -1) {
			mat[x][y]->setElem(resultante[indice]);
			indice = (indice + 1) % resultante.size();
			placed = true;
		}
	}
	turnoPlayer = true;
}