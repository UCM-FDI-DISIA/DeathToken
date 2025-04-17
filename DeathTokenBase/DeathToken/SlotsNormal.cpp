#include "slotsNormal.h"
#include "Carrete.h"
#include "button.h"
#include "texture.h"
#include "game.h"
#include "award.h"
using namespace std;

SlotsNormal::SlotsNormal(Game* g) : Slots(g), comprobanteIndice(0)
{
	float x = Game::WIN_WIDTH * (0.5f - (TAM_CELDA / 1920.0f) * (N_COLUM / 2.0f));
	float y = Game::WIN_HEIGHT * (40 / 1080.0f);
	float celdaX = Game::WIN_WIDTH * (TAM_CELDA / 1920.0f);
	float celdaY = Game::WIN_HEIGHT * (TAM_CELDA / 1080.0f);
	float botonX = Game::WIN_WIDTH * (TAM_BOTON / 1920.0f);
	float botonY = Game::WIN_HEIGHT * (TAM_BOTON / 1080.0f);


	for (int i = 0; i < N_COLUM; ++i) {
		carretes.push_back(new Carrete(this, { (int)(x + i * celdaX), (int)y }, (int)celdaX, (int)celdaY, game->getTexture(CELDA), game->getTexture(ICONOS)));
		addObjects(carretes[i]);
		Button* button = new Button(this, (int)(x + i * celdaX + (celdaX - botonX) / 2), (int)(y * 2 + celdaY * N_COLUM), (int)botonX, (int)botonY, game->getTexture(CELDA));
		addObjects(button);
		addEventListener(button);

		Carrete* c = carretes[i];
		button->connect([this, c] {
			if (c->getParada())++comprobanteIndice;
			c->pararGiro();
			});
	}
}
SlotsNormal:: ~SlotsNormal() {
	for (Carrete* i : carretes) i = nullptr;
	delete ui;
}
void SlotsNormal::update() {
	GameState::update();
	if (comprobanteIndice == 3) {
		comprobanteIndice = 0;

		vector<int> vectorCarrete1 = carretes[0]->getCarrete();
		vector<int> vectorCarrete2 = carretes[1]->getCarrete();
		vector<int> vectorCarrete3 = carretes[2]->getCarrete();

		int multiplicador = 0;
		for (int i = 0; i < N_COLUM; ++i) {

			bool telarañas1_2 = vectorCarrete1[i] == vectorCarrete2[i] && vectorCarrete1[i] == 0;
			bool telarañas1_3 = vectorCarrete1[i] == vectorCarrete3[i] && vectorCarrete1[i] == 0;
			bool telarañas2_3 = vectorCarrete2[i] == vectorCarrete3[i] && vectorCarrete2[i] == 0;

			if (vectorCarrete1[i] == vectorCarrete2[i] && vectorCarrete2[i] == vectorCarrete3[i]) {
				
				multiplicador += multiplicadores[vectorCarrete1[i]];
			}
			else if (telarañas1_2 || telarañas1_3 || telarañas2_3) {
				multiplicador += multiplicadores[0];
			}
		}
		for (Carrete* c : carretes) c->deleteCarrete();
#if _DEBUG

		std::cout << multiplicador << "\n";
#endif
		if (multiplicador != 0) game->push(new Award(game, (GameState*)this, bet, bet * multiplicador));
	}
}
void SlotsNormal::render() const {
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(MARBLESBACK)->render(r);

	GameState::render();
}
void SlotsNormal::iniciarGiro() {
	bool girar = false;
	for (Carrete* c : carretes)
		girar = girar || c->getParada();
	if (!girar) {
		for (Carrete* c : carretes) c->iniciarGiro();
	}
}