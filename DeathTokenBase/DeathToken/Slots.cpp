#include "Slots.h"


Slots::Slots(Game* g) : GameState(g), comprobanteIndice(0)
{
	int x = (game->WIN_WIDTH / 4) - (tamCelda/2);
	carrete1 = new Carrete(this, { x , alturaCelda }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete1);
	Button* boton1 = new Button(this, x + 25, ditanciaBoton, tamBoton, tamBoton, game->getTexture(CELDA));
	addObjects(boton1);
	addEventListener(boton1);
	boton1->connect([this] { carrete1->pararGiro(); ++comprobanteIndice; });

	x = (game->WIN_WIDTH / 4 * 2) - (tamCelda / 2);
	carrete2 = new Carrete(this, { x , alturaCelda }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete2);
	Button* boton2 = new Button(this, x + 25, ditanciaBoton, tamBoton, tamBoton, game->getTexture(CELDA));
	addObjects(boton2);
	addEventListener(boton2);
	boton2->connect([this] { carrete2->pararGiro(); ++comprobanteIndice; });

	x = (game->WIN_WIDTH / 4 * 3) - (tamCelda / 2);
	carrete3 = new Carrete(this, { x , alturaCelda }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete3);
	Button* boton3 = new Button(this, x + 25, ditanciaBoton, tamBoton, tamBoton, game->getTexture(CELDA));
	addObjects(boton3);
	addEventListener(boton3);
	boton3->connect([this] { carrete3->pararGiro(); ++comprobanteIndice; });

	Button* botonIncio = new Button(this, 75, 225, tamBoton, tamBoton, game->getTexture(CELDA));
	addObjects(botonIncio);
	addEventListener(botonIncio);
	botonIncio->connect([this]
		{
			carrete1->iniciarGiro();
			carrete2->iniciarGiro();
			carrete3->iniciarGiro();

		});
	
}
void Slots::update() {
	GameState::update();
	if (comprobanteIndice == 3) {
		comprobanteIndice = 0;

		vector<int> vectorCarrete1 = carrete1->getCarrete();
		vector<int> vectorCarrete2 = carrete2->getCarrete();
		vector<int> vectorCarrete3 = carrete3->getCarrete();

		for (int i = 0; i < vectorCarrete1.size() - 1; ++i) {

		}
	}	
}