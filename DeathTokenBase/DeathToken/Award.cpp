#include "Award.h"
#include "Marbles.h"
#include "Game.h"
#include "SDL.h"

Award::Award(Game* game, Marbles* lastState, int bet, int mWin) 
	: GameState(game), state(lastState), betG(bet), mWinG(mWin), startTime(SDL_GetTicks()), background(nullptr) {
	background = game->getTexture(BLACKFOND);
	background->modAlfa(140);

}


void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
	Uint32 elapsedTime = SDL_GetTicks() - startTime;
	if (elapsedTime >= 5000) { // 5 segundos
		game->pop(); // Regresar al estado anterior
	}
}

void Award::render() const  {
	state->render();
	background->render();
	//Una vez entrado tiene que ir a show Message y renderizar la cantidad del premio con un mensaje
	//
	/*int multi = mWinG / betG;
	if (multi >= 2 && multi <= 3) {
		//AWESOME
	}
	else if (multi >= 3 && multi <= 5) {
		//AMAZING
	}
	else if (multi >= 5 && multi <= 10) {
		//BIG BIG WIN
	}
	else if (multi >= 10 && multi <= 20) {
		//MEGA WIN
	}
	else if (multi > 20) {
		//LO ROMPISTE
	}*/
}

void Award::showMessage() {
	
}