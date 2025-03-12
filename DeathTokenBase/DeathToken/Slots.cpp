#include "Slots.h"
#include "Game.h"


Slots::Slots(Game* g) : GameState(g), comprobanteIndice(0), ui(new UISlots(this, g, this))
{

	int offset = (int)(20 / 1920.0) * Game::WIN_WIDTH;
	int y = (int)((50/1080.0) * Game::WIN_HEIGHT);
	int x = (int)(((1 / 2.0) - (X_CELDA + X_CELDA / 2))* Game::WIN_WIDTH) - offset;

	for (int i = 0; i < N_COLUM; ++i) {
		carretes.push_back(new Carrete(this, { x , y },(int) (X_CELDA * Game::WIN_WIDTH), (int)(Y_CELDA * Game::WIN_HEIGHT), game->getTexture(CELDA), game->getTexture(ICONOS)));
		addObjects(carretes[i]);
		Button* button = new Button(this, x + (int)(((X_CELDA - X_BOTON) / 2) * Game::WIN_WIDTH), y + (int)(DISTANCIA_BOTON * Game::WIN_HEIGHT), (int)(X_BOTON*Game::WIN_WIDTH), (int)(Y_BOTON * Game::WIN_HEIGHT), game->getTexture(CELDA));
		addObjects(button);
		addEventListener(button);

		Carrete* c = carretes[i];
		button->connect([this, c]{  
				if(c->getParada())++comprobanteIndice;
				c->pararGiro();
				
		});
		x += (int)((X_CELDA *Game::WIN_WIDTH)+ offset);
	}

	for (int i = 0; i < 7; ++i) {
		pair<int, int> aux;
		aux.first = i;
		aux.second = multiplicadores[i];
		puntuaciones.insert(aux);
	}

}
Slots:: ~Slots() {
	for (Carrete* i : carretes) i = nullptr;
	delete ui;
}
void Slots::update() {
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
				auto it = puntuaciones.find(vectorCarrete1[i]);
				multiplicador += it->second;
			}
			else if (telarañas1_2 || telarañas1_3 || telarañas2_3) {
				auto it = puntuaciones.find(0);
				multiplicador += it->second;
			}
		}
		for (Carrete* c : carretes) c->deleteCarrete();
		std :: cout << multiplicador << "\n";
	}
}
void Slots::render() const {
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(MARBLESBACK)->render(r);
	
	GameState::render();
}
void Slots::iniciarGiro() {
	bool girar = false;
	for (Carrete* c : carretes)
		girar = girar || c->getParada();
	if (!girar) {
		for (Carrete* c : carretes) c->iniciarGiro();
	}
}