#include "slotsNormal.h"
#include "carrete.h"
#include "button.h"
#include "texture.h"
#include "game.h"
#include "award.h"
using namespace std;

SlotsNormal::SlotsNormal(Game* g) : Slots(g), comprobanteIndice(0)
{
	// Tamaños relativos al tamaño de pantalla
	float x = Game::WIN_WIDTH * (0.5f - ((TAM_CELDA - 50) / 1920.0f) * (N_COLUM / 2.0f));
	float y = Game::WIN_HEIGHT * (40 / 1080.0f);
	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	float botonX = Game::WIN_WIDTH * (TAM_BOTON / 1920.0f);
	float botonY = Game::WIN_HEIGHT * (TAM_BOTON / 1080.0f);

	// Crea por cada columna un carrete y un botón para detenerlos
	for (int i = 0; i < N_COLUM; ++i) {
		// Añade el carrete a la lista de objetos
		Carrete* c = new Carrete(this, { (int)(x + i * celdaX), (int)y }, (int)celdaX, (int)celdaY, game->getTexture(CELDA), game->getTexture(ICONOS));
		c->init(g);
		carretes.push_back(c);
		addObjects(carretes[i]);

		// Boton correspondiente para detener el giro
		Button* button = new Button(this, (int)(x + i * celdaX + (celdaX - botonX) / 2), (int)(y * 2 + celdaY * N_COLUM), (int)botonX, (int)botonY,
			game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
		addObjects(button);
		addEventListener(button);
		// callback del boton
		button->connect([this, c] {
			if (c->getParada()) {
				++comprobanteIndice;
				c->pararGiro(); // Para el giro si no esta parado 
			}
			});
	}

	// Botón para añadir la apuesta
	float w = Game::WIN_WIDTH * (200.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (200.0f / 1080.0f);
	x = Game::WIN_WIDTH * (0.5f - ((TAM_CELDA - 20) / 1920.0f) * ((N_COLUM / 2.0f) + 1.0f));
	y = Game::WIN_HEIGHT * 0.5f - h / 2;
	btnBet = new ButtonSlots(this, game, ui, int(x), (int)y, (int)w, (int)h, game->getTexture(BETSLOTS));
	addObjects(btnBet);
	addEventListener(btnBet);
}
SlotsNormal:: ~SlotsNormal() {
	for (Carrete* i : carretes) {
		i = nullptr;
	}
}
void SlotsNormal::update() {
	// Update de los gameObjects de la escena
	GameState::update();
	// Si se han parado los tres, carrete se hace la comprobación
	if (comprobanteIndice == N_COLUM) {
		comprobanteIndice = 0;

		vector<int> vectorCarrete1 = carretes[0]->getCarrete();
		vector<int> vectorCarrete2 = carretes[1]->getCarrete();
		vector<int> vectorCarrete3 = carretes[2]->getCarrete();

		int multiplicador = 0;
		for (int i = 0; i < N_COLUM; ++i) {
			// Comprobante de dos arañas en la misma fila
			bool telarañas1_2 = vectorCarrete1[i] == vectorCarrete2[i] && vectorCarrete1[i] == 0;
			bool telarañas1_3 = vectorCarrete1[i] == vectorCarrete3[i] && vectorCarrete1[i] == 0;
			bool telarañas2_3 = vectorCarrete2[i] == vectorCarrete3[i] && vectorCarrete2[i] == 0;
			// Comprobante de los tres iconos en la fila iguales
			if (vectorCarrete1[i] == vectorCarrete2[i] && vectorCarrete2[i] == vectorCarrete3[i]) {
				// Suma el multiplicador correspondiente al total
				multiplicador += multiplicadores[vectorCarrete1[i]];
			}
			else if (telarañas1_2 || telarañas1_3 || telarañas2_3) {
				multiplicador += multiplicadores[0];
			}
		}
		// Se borran los tres carretes
		for (Carrete* c : carretes) c->deleteCarrete();
#if DEBUG
		std::cout << multiplicador << "\n";
#endif
		// Si el multiplicador no es 0 (ha habido combinación), se muestra el mensaje
		if (multiplicador != 0) {
			game->push(new Award(game, (GameState*)this, bet, bet * multiplicador));
		}
		// Se resetea la apuesta
		bet = 0;
	}
}
void SlotsNormal::render() const {
	// render del fondo
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(SLOTSFONDO)->render(r);

	// render de los gameObjects
	GameState::render();
}
bool SlotsNormal::iniciarGiro() {
	// Comprueba que todos los carretes estén parados para iniciar
	bool girar = false;
	for (Carrete* c : carretes) {
		girar = girar || c->getParada();
	}
	// Inicia el giro de los carretes
	if (!girar) {
		for (Carrete* c : carretes) {
			c->iniciarGiro();
		}
		return true;
	}
	else {
		return false;
	}
}