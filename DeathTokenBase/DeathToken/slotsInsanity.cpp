#include "slotsInsanity.h"
#include "SoundManager.h"
#include "celda.h"
#include "award.h"
#include <chrono>
#include <random>
using namespace std;

SlotsInsanity::SlotsInsanity(Game* g) : Slots(g), indice(0), mat(N_COLUM), turnoPlayer(true), jugando(false), IAstartTime(0)
{
	// Pone a true el modo locura en la Ui para que se muestre el tutorial correspondiente
	ui->setLocura(true);

	float x = Game::WIN_WIDTH * (0.5f - ((TAM_CELDA - 50) / 1920.0f) * (N_COLUM / 2.0f));
	float y = Game::WIN_HEIGHT * (70 / 1080.0f);
	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	// Crea la matriz de Celdas, que se añaden al vector de GO de la escena
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			Celda* c = new Celda(this, { (int)(x + j * celdaX), (int)(y + i * celdaY) }, (int)celdaX, (int)celdaY, game->getTexture(CELDA), game->getTexture(ICONOS));
			mat[i].push_back(c);
			addObjects(c);
		}
	}
	// vector de los indices en el orden en el que se mostraran para colocar
	resultante = vectorAleatorio();
        auto& soundManager = SoundManager::obtenerInstancia();
        soundManager.reproducirMusica("SlotsM");
	//Boton para poner la apuesta
	x = Game::WIN_WIDTH * (0.5f - ((TAM_CELDA - 20) / 1920.0f) * ((N_COLUM / 2.0f) + 1.0f));
	y = Game::WIN_HEIGHT * 0.5f;
	btnBet = new ButtonSlots(this, game, ui, int(x), (int)y, (int)celdaX, (int)celdaY, game->getTexture(BETSLOTS));
	addObjects(btnBet);
	addEventListener(btnBet);
}
vector<int> SlotsInsanity::vectorAleatorio() {
	vector<int> vector;
	// Creacion del vector segun las frecuencias y desordenacion
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
	//Comprobaciones correspondientes (solo si se está jugando)
	if (jugando) {
		int line = checkBoard(); //Comprueba si hay linea
		//Comprueba si toda la mtriza está llena para borrarla
		bool full = true;
		for (int i = 0; i < N_COLUM; ++i) {
			for (int j = 0; j < N_COLUM; ++j) {
				if (mat[i][j]->getElem() == -1) { // elem == -1 es casilla vacia
					full = false;
					break;
				}
			}
			if (!full) break;
		}
		//Si está llena o si ha habido linea se vacia la matriz
		if (full || line != -1) {
			// En caso de linea, si acaba de jugar el jugador (!turnoPlayer, porque ya habrá cedido el turno a la IA), se muestra la recompensa
			if (line != -1) {
				if (!turnoPlayer) {
					game->push(new Award(game, (GameState*)this, bet, bet * multiplicadores[line]));
				}
				bet = 0; //reset de la apuesta
				jugando = false; //se para el juego
				turnoPlayer = true;
			}
			ClearBoard();
		}

		if (!turnoPlayer) IA(); //Turno de la IA, si le toca
		//El turno del jugador se gestiona mediante botones y callbacks, por lo que no tiene un metodo propio
	}
	GameState::update();

}
void SlotsInsanity::render() const {
	//render del fondo
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(SLOTSFONDO)->render(r);

	//render de la casilla que representa el icono siguiente a colocar
	SDL_Rect box;
	box.w = (int)(Game::WIN_WIDTH * (TAM_CELDA / 1920.0f));
	box.h = (int)(Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f));
	box.x = (int)(Game::WIN_WIDTH * (0.5f - ((TAM_CELDA - 20) / 1920.0f) * ((N_COLUM / 2.0f) + 1.0f)));
	box.y = (int)(Game::WIN_HEIGHT * 0.5f - box.h * 1.5f);
	if (turnoPlayer) { game->getTexture(CELDA)->render(box); }
	else { game->getTexture(CELDA)->render(box, { 170,230,255 }); } //Si es el turno de la IA se pinta con un tono azul para diferenciar

	if (jugando) { game->getTexture(ICONOS)->renderFrame(box, 0, resultante[indice]); } //Si se está jugando se muestra el icono a colocar
	GameState::render();
}
//Metodo llamado por la celda al ser pulsada
int SlotsInsanity::getNext() {
	//Si es el turno del jugador se delvuelve a la casilla el icono señalado por indice (y se avanza)
	if (turnoPlayer) {
		int n = resultante[indice];
		if (indice == resultante.size() - 1) { resultante = vectorAleatorio(); } //Cuando el vector se acaba se vuelve a mezclar
		indice = (indice + 1) % resultante.size();
		turnoPlayer = false; //Cambio de turno a la IA
		IAstartTime = SDL_GetTicks(); //Tiempo de inicio del turno de IA, para el delay
		return n;
	}
	else return -1; //Si no eta jugando el player, se devuelve casilla vacía
}
//Metodo que compruba si hay tres en raya. Devuelve el id del icono que forma la línea
int SlotsInsanity::checkBoard() const {
	// Revisiï¿½n filas y columnas
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
	// Revisiï¿½n diagonales principales
	for (int i = 0; i < N_COLUM - 2; ++i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i + 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i + 2][j + 2]->getElem()) {
				return mat[i][j]->getElem();
			}
		}
	}
	// Revisiï¿½n diagonales secundarias
	for (int i = N_COLUM - 1; i > 1; --i) {
		for (int j = 0; j < N_COLUM - 2; ++j) {
			if (mat[i][j]->getElem() != -1 &&
				mat[i][j]->getElem() == mat[i - 1][j + 1]->getElem() && mat[i][j]->getElem() == mat[i - 2][j + 2]->getElem()) {
				return mat[i][j]->getElem();
			}
		}
	}
	//devuelve -1 si no hay linea
	return -1;
}
//Movimiento de la IA
void SlotsInsanity::IA() {
	// Delay para empezar (para que el jugador entienda que la IA está pensando)
	if (SDL_GetTicks() - IAstartTime >= 1000) {
		//La IA comprueba si poniendo el nuevo icono consigue el tres en raya en alguna casilla
		bool placed = false;
		for (int i = 0; i < N_COLUM; ++i) {
			for (int j = 0; j < N_COLUM; ++j) {
				if (mat[i][j]->getElem() == -1) { //Comprobación de vacía
					mat[i][j]->setElem(resultante[indice]);
					int linea = checkBoard(); 
					if (linea == -1) { //No se ha conseguido línea
						mat[i][j]->setElem(-1); //Se vacia la casilla que se ha probado y se prueba la siguiente
					}
					else {
						placed = true; //Se ha conseguido
						break;
					}
				}
			}
			if (placed) { break; }
		}
		// Si no ha conseguido 3 en raya coloca el icono libre en una casilla vacia aleatoria
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
		//Acaba el turno de la IA, le toca al jugador
		turnoPlayer = true;
	}
}
// Pone todas las celdas vacías
void SlotsInsanity::ClearBoard() {
	for (int i = 0; i < N_COLUM; ++i) {
		for (int j = 0; j < N_COLUM; ++j) {
			mat[i][j]->resetElem();
		}
	}
}
// Si no se está jugando ya, se cede el primer turno al jugador
void SlotsInsanity::iniciarGiro() {
	if (!jugando) {
		turnoPlayer = true;
	}
	jugando = true;
}