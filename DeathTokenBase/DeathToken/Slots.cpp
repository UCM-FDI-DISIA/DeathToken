#include "Slots.h"


Slots::Slots(Game* g) : GameState(g)
{
	int x = game->WIN_WIDTH / 4;
	carrete1 = new Carrete(this, { x , 100 }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete1);

	x = game->WIN_WIDTH / 4 * 2;
	carrete2 = new Carrete(this, { x , 100 }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete2);

	x = game->WIN_WIDTH / 4 * 3;
	carrete3 = new Carrete(this, { x , 100 }, tamCelda, tamCelda, game->getTexture(CELDA), game->getTexture(ICONOS));
	gameObjects.push_back(carrete3);
	
	/*
	boton1 = new Button(this, 200, 260, 175, 25, game->getTexture(), game->getTexture());
	addObjects(boton1);
	addEventListener(boton1);
	boton1->connect([this]{ carrete1->pararGiro();})
	boton2 = new Button(this, 200, 260, 175, 25, game->getTexture(), game->getTexture());
	addObjects(boton2);
	addEventListener(boton2);
	boton2->connect([this]{ carrete2->pararGiro();})
	boton3 = new Button(this, 200, 260, 175, 25, game->getTexture(), game->getTexture());
	addObjects(boton3);
	addEventListener(boton3);
	boton3->connect([this]{ carrete3->pararGiro();})
	*/

}