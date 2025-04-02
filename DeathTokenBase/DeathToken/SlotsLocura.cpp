#include "SlotsLocura.h"
#include <chrono>
#include <random>
#include "Celda.h"
using namespace std;

SlotsLocura::SlotsLocura(Game* g) : Slots(g), indice(0), mat(N_COLUM), turnoPlayer(true), jugando(false), IAstartTime(0)
{
	float x = Game::WIN_WIDTH * (0.5 - (TAM_CELDA / 1920.0f) * (N_COLUM / 2.0f));
	float y = Game::WIN_HEIGHT * (50 / 1080.0f);
	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			Celda* c = new Celda(this, { (int)(x + j * celdaX), (int)(y + i * celdaY) }, (int)celdaX, (int)celdaY, game->getTexture(CELDA), game->getTexture(ICONOS));
			mat[i].push_back(c);
			addObjects(c);
		}
	}
	resultante = vectorAleatorio();
}
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

void SlotsLocura::update() {
	if (jugando) {
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
			ClearBoard();
			if (line) jugando = false;
		}

		if (!turnoPlayer) IA();
	}
		GameState::update();
	
}
void SlotsLocura::render() const {
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(MARBLESBACK)->render(r);

	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	SDL_Rect box((int)(Game::WIN_WIDTH / 2 + celdaX * (N_COLUM / 2.0f) + (20 / 1920.0f) * Game::WIN_WIDTH), (int)(Game::WIN_HEIGHT / 2 - celdaY), (int)celdaX, (int)celdaY);
	game->getTexture(CELDA)->render(box);
	if (jugando) { game->getTexture(ICONOS)->renderFrame(box, 0, resultante[indice]); }
	GameState::render();
}

int SlotsLocura::getNext() {
	if (turnoPlayer) {
		int n = resultante[indice];
		if (indice == resultante.size() - 1) resultante = vectorAleatorio();
		indice = (indice + 1) % resultante.size();
		turnoPlayer = false;
		IAstartTime = SDL_GetTicks();
		return n;
	}
	else return -1;
}

bool SlotsLocura::checkBoard() const {
	// Revisión filas y columnas
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
	// Revisión diagonales principales
	for (int i = 0; i < N_COLUM - 2; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i + 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i + 2][j + 2]->getElem()) {
				return true;
			}
		}
	}
	// Revisión diagonales secundarias
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
	if (SDL_GetTicks() - IAstartTime >= 1000) {
		bool placed = false;
		while (!placed) {
			int x = rand() % N_COLUM;
			int y = rand() % N_COLUM;
			if (mat[x][y]->getElem() == -1) {
				mat[x][y]->setElem(resultante[indice]);
				if (indice == resultante.size() - 1) resultante = vectorAleatorio();
				indice = (indice + 1) % resultante.size();
				placed = true;
			}
		}
		turnoPlayer = true;
	}
}
void SlotsLocura::ClearBoard() {
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			mat[i][j]->resetElem();
		}
	}
}
void SlotsLocura::iniciarGiro() {
	jugando = true;
	turnoPlayer = true;
}