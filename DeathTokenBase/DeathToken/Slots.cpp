#include "Slots.h"


Slots::Slots(Game* g) : GameState(g), comprobanteIndice(0)
{
	int x = (game->WIN_WIDTH / 4) - (TAM_CELDA/2);
	carrete1 = new Carrete(this, { x , TAM_CELDA }, TAM_CELDA, TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete1);
	Button* boton1 = new Button(this, x + 25, DISTANCIA_BOTON, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
	addObjects(boton1);
	addEventListener(boton1);
	boton1->connect([this] { carrete1->pararGiro(); ++comprobanteIndice; });

	x = (game->WIN_WIDTH / 4 * 2) - (TAM_CELDA / 2);
	carrete2 = new Carrete(this, { x , TAM_CELDA }, TAM_CELDA, TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete2);
	Button* boton2 = new Button(this, x + 25, DISTANCIA_BOTON, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
	addObjects(boton2);
	addEventListener(boton2);
	boton2->connect([this] { carrete2->pararGiro(); ++comprobanteIndice; });

	x = (game->WIN_WIDTH / 4 * 3) - (TAM_CELDA / 2);
	carrete3 = new Carrete(this, { x , TAM_CELDA }, TAM_CELDA, TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete3);
	Button* boton3 = new Button(this, x + 25, DISTANCIA_BOTON, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
	addObjects(boton3);
	addEventListener(boton3);
	boton3->connect([this] { carrete3->pararGiro(); ++comprobanteIndice; });

	Button* botonIncio = new Button(this, 75, 225, TAM_BOTON, TAM_BOTON, game->getTexture(CELDA));
	addObjects(botonIncio);
	addEventListener(botonIncio);
	botonIncio->connect([this]
		{
			carrete1->iniciarGiro();
			carrete2->iniciarGiro();
			carrete3->iniciarGiro();

		});

	for (int i = 0; i < 7; ++i) {
		pair<int, int> aux;
		aux.first = i;
		aux.second = multiplicadores[i];
		puntuaciones.insert(aux);
	}
		
}
void Slots::update() {

	GameState::update();
	if (comprobanteIndice == 3) {
		comprobanteIndice = 0;

		vector<int> vectorCarrete1 = carrete1->getCarrete();
		vector<int> vectorCarrete2 = carrete2->getCarrete();
		vector<int> vectorCarrete3 = carrete3->getCarrete();

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
		carrete1->deleteCarrete();
		carrete2->deleteCarrete();
		carrete3->deleteCarrete();
		vectorCarrete1.erase(vectorCarrete1.begin(), vectorCarrete1.end() - 1);
		vectorCarrete2.erase(vectorCarrete2.begin(), vectorCarrete2.end() - 1);
		vectorCarrete3.erase(vectorCarrete3.begin(), vectorCarrete3.end() - 1);
		cout << multiplicador << "\n";
	}		
}