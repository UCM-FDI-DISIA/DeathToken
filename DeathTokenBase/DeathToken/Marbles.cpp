#include "Marbles.h"
#include "Game.h"	

Marbles::Marbles(Game* game) : GameState(game), texture(game->getTexture(MARBLESBACK)) {
	marbles = { 0,0,0,0 };

	buttonType1_1 = new Button(this,  Game::WIN_WIDTH/2 -118 ,Game::WIN_HEIGHT- Game::WIN_HEIGHT/4 -118 - 118 , 118, 118, game->getTexture(BUTTONMARBLES1));
	addObjects(buttonType1_1);
	addEventListener(buttonType1_1);

	buttonType1_2 = new Button(this, Game::WIN_WIDTH/2 , Game::WIN_HEIGHT-Game::WIN_HEIGHT/4 - 118- 118, 118,118, game->getTexture(BUTTONMARBLES1));
	addObjects(buttonType1_2);
	addEventListener(buttonType1_2);

	buttonType1_3 = new Button(this, Game::WIN_WIDTH / 2 - 118, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 118, 118,118, game->getTexture(BUTTONMARBLES1));
	addObjects(buttonType1_3);
	addEventListener(buttonType1_3);

	buttonType1_4 = new Button(this, Game::WIN_WIDTH / 2, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 118,118,118, game->getTexture(BUTTONMARBLES1));
	addObjects(buttonType1_4);
	addEventListener(buttonType1_4);

}


void Marbles::generateMarbles() {
	//En un vector voy metiendo aleatoriamente +1, representando ROJO/VERDE/AZUL/AMARILLO
	marbles = { 0,0,0,0 };
	for (int i = 0; i > 3; i++) {
		int color = rand() % 3;
		marbles[color]++;
	}
}
int  Marbles::checkBets(int moneyBet) {
	int moneyWin = 0;
	//Cuando se hagan los botones cada apuesta hecha se metera en un map indicando que apuesta 
	//hecha en un vector y el multi que da si gana

	for (const auto& betkey : bets) {//Recorre el map
		const Bet& typeBet = betkey.second;//Pillo la apuesta

		bool won = true;
		for (int i = 0; i < 4; i++) {
			if (marbles[i] < typeBet.typeOfBet[i]) { //Si algun numero del vector es mayor a las canicas, se da esa apuesta como perdida
				won = false;
			}
		}

		if (won) {//Si ha ganado esa apuesta se calcula lo ganado
			int BetMoneyWin = moneyBet * typeBet.multiplier;
			moneyWin += BetMoneyWin;
		}
	}
	bets.clear();
	return moneyWin;
}

void Marbles::startRound() {
	play = true;
}
void Marbles::update() {
	if (play) {//Cuando se activa el boton de jugar
		generateMarbles();//Se generar las canicas aleatorias
		int moneyWin = checkBets(moneyBet);//Comparar canicas con apuesta
		//Segun la apuesta porX al dinero metido
		if (moneyWin > 0) {
			//mostrar mensaje LOLOLOLO HASSSS GANADOOOOO
			//AMAZING
		}
		play = false;
	}
}

void Marbles::render() const {
	texture->render();
	GameState::render();
}
