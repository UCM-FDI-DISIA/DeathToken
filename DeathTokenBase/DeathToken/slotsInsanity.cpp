#include "slotsInsanity.h"
#include "celda.h"
#include "award.h"
#include <chrono>
#include <random>
using namespace std;

SlotsInsanity::SlotsInsanity(Game* g) : Slots(g), indice(0), mat(N_COLUM), turnoPlayer(true), jugando(false), IAstartTime(0)
{
	float x = Game::WIN_WIDTH * (0.5f - (TAM_CELDA / 1920.0f) * (N_COLUM / 2.0f));
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

	float w = Game::WIN_WIDTH * (150.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (150.0f / 1080.0f);
	x = Game::WIN_WIDTH * (0.5f - (TAM_CELDA / 1920.0f) * ((N_COLUM / 2.0f) + 1));
	y = Game::WIN_HEIGHT * 0.5f - h / 2;
	btnBet = new ButtonSlots(this, game, ui, int(x), (int)y, (int)w, (int)h, game->getTexture(CELDA));
	addObjects(btnBet);
	addEventListener(btnBet);
}
vector<int> SlotsInsanity::vectorAleatorio() {
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

void SlotsInsanity::update() {
	if (jugando) {
		int line = checkBoard();
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
		if (full || line != -1) {
			if (line != -1) {
				if (!turnoPlayer) { game->push(new Award(game, (GameState*)this, bet, bet * multiplicadores[line])); }
				jugando = false;
				turnoPlayer = true;
			}
			ClearBoard();
		}

		if (!turnoPlayer) IA();
	}
	GameState::update();

}
void SlotsInsanity::render() const {
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(MARBLESBACK)->render(r);

	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	SDL_Rect box((int)(Game::WIN_WIDTH / 2 + celdaX * (N_COLUM / 2.0f) + (20 / 1920.0f) * Game::WIN_WIDTH), (int)(Game::WIN_HEIGHT / 2 - celdaY), (int)celdaX, (int)celdaY);
	if (turnoPlayer) { game->getTexture(CELDA)->render(box); }
	else { game->getTexture(CELDA)->render(box, { 170,230,255 }); }

	if (jugando) { game->getTexture(ICONOS)->renderFrame(box, 0, resultante[indice]); }
	GameState::render();
}

int SlotsInsanity::getNext() {
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

int SlotsInsanity::checkBoard() const {
	// Revisión filas y columnas
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i][j + 1]->getElem() && mat[i][j]->getElem() == mat[i][j + 2]->getElem()) {
				return mat[i][j]->getElem();
			}
			else if (mat[j][i]->getElem() != -1 &&
				mat[j][i]->getElem() == mat[j + 1][i]->getElem() && mat[j][i]->getElem() == mat[j + 2][i]->getElem()) {
				return mat[j][i]->getElem();
			}
		}
	}
	// Revisión diagonales principales
	for (int i = 0; i < N_COLUM - 2; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i + 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i + 2][j + 2]->getElem()) {
				return mat[i][j]->getElem();
			}
		}
	}
	// Revisión diagonales secundarias
	for (int i = N_COLUM - 1; i > 1; --i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i - 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i - 2][j + 2]->getElem()) {
				return mat[i][j]->getElem();
			}
		}
	}

	return -1;
}
void SlotsInsanity::IA() {
	if (SDL_GetTicks() - IAstartTime >= 1000) {
		bool placed = false;
		for (int i = 0; i < N_COLUM; ++i) {
			for (int j = 0; j < N_COLUM; ++j) {
				if (mat[i][j]->getElem() != -1) {
					mat[i][j]->setElem(resultante[indice]);
					int linea = checkBoard();
					if (linea == -1) {
						mat[i][j]->setElem(-1);
					}
					else {
						placed = true;
						break;
					}
				}
			}
			if (placed) { break; }
		}
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
void SlotsInsanity::ClearBoard() {
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			mat[i][j]->resetElem();
		}
	}
}
void SlotsInsanity::iniciarGiro() {
	if (!jugando) {
		turnoPlayer = true;
	}
	jugando = true;
}