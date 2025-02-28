#include "Slots.h"


Slots::Slots(Game* g) : GameState(g), comprobanteIndice(0)
{
	int offset = 20;
	int x = (game->WIN_WIDTH / 2) - (TAM_CELDA + TAM_CELDA / 2) - offset;

	Button* botonIncio = new Button(this, x - TAM_BOTON - offset, game->WIN_HEIGHT/2 - TAM_BOTON/2, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
	addObjects(botonIncio);
	addEventListener(botonIncio);
	botonIncio->connect([this] {for (Carrete* c : carretes) c->iniciarGiro();});

	for (int i = 0; i < N_COLUM; ++i) {
		carretes.push_back(new Carrete(this, { x , TAM_CELDA }, TAM_CELDA, TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS)));
		addObjects(carretes[i]);
		Button* button = new Button(this, x + (TAM_CELDA - TAM_BOTON)/2, DISTANCIA_BOTON, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
		addObjects(button);
		addEventListener(button);

		Carrete* c = carretes[i];
		button->connect([this, c] { c->pararGiro(); ++comprobanteIndice; });
		x += TAM_CELDA + offset;
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
	GameState:: ~GameState();
}
void Slots::update() {

	GameState::update();
	if (comprobanteIndice == 3) {
		comprobanteIndice = 0;

		vector<int> vectorCarrete1 = carretes[0]->getCarrete();
		vector<int> vectorCarrete2 = carretes[1]->getCarrete();
		vector<int> vectorCarrete3 = carretes[2]->getCarrete();

		int multiplicador = 0;
		for (int i = 0; i < 3; ++i) {

			bool telarañas1_2 = vectorCarrete1[i] == vectorCarrete2[i] && puntuaciones.find(vectorCarrete1[i])->first == 0;
			bool telarañas1_3 = vectorCarrete1[i] == vectorCarrete3[i] && puntuaciones.find(vectorCarrete1[i])->first == 0;
			bool telarañas2_3 = vectorCarrete2[i] == vectorCarrete3[i] && puntuaciones.find(vectorCarrete2[i])->first == 0;

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
		vectorCarrete1.erase(vectorCarrete1.begin(), vectorCarrete1.end() - 1);
		vectorCarrete2.erase(vectorCarrete2.begin(), vectorCarrete2.end() - 1);
		vectorCarrete3.erase(vectorCarrete3.begin(), vectorCarrete3.end() - 1);
		cout << multiplicador << "\n";
	}
}