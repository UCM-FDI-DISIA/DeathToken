#include "Award.h"
#include "Marbles.h"
#include "Game.h"
#include "SDL.h"

Award::Award(Game* game, GameState* lastState, int bet, int mWin) 
	: GameState(game), state(lastState), betG(bet), mWinG(mWin), startTime(SDL_GetTicks()), background(nullptr) {
	background = game->getTexture(BLACKFOND);
	background->modAlfa(140);
	this->addObjects(background);

	//Crear calse intermedia PLAystate que herede todos los juegos y hacer un puntero que puedas pillar de cada juego
	//Mirar el virtualTimer
	text = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 2, 200);

	int multi = mWinG / betG;
	if (multi >= 2 && multi <= 3) {
		//AWESOME
		text->setMessage("PRUEBA");
	}
	else if (multi >= 3 && multi <= 5) {
		//AMAZING
		text->setMessage("PRUEBA");

	}
	else if (multi >= 5 && multi <= 10) {
		//BIG BIG WIN
		text->setMessage("PRUEBA");

	}
	else if (multi >= 10 && multi <= 20) {
		//MEGA WIN
		text->setMessage("PRUEBA");

	}
	else if (multi > 20) {
		//LO ROMPISTE
		text->setMessage("PRUEBA");

	}
	else
	{
		text->setMessage("PRUEBA");
	}
	this->addObjects(text);

}


void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
	Uint32 elapsedTime = SDL_GetTicks() - startTime;
	if (elapsedTime >= 5000) {
		
		game->pop(); // Regresar al estado anterior
	}
}

void Award::render() const  {
	state->render();
	background->render();
	GameState::render();
	//Una vez entrado tiene que ir a show Message y renderizar la cantidad del premio con un mensaje
	//
	
}

void Award::showMessage() {
	
}