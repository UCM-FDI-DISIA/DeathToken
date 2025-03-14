#include "Award.h"

Award::Award(Game* game, GameState lastState, int bet, int mWin) : GameState(game), betG(bet),mWinG(mWin) {}

void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
}

void Award::render() const{
	//Una vez entrado tiene que ir a show Message y renderizar la cantidad del premio con un mensaje
	//
}

void Award::showMessage() {
	int multi = mWinG / betG;
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
	}
}