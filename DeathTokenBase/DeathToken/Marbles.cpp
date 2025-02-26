#include "Marbles.h"
#include "Game.h"	

Marbles::Marbles(Game* game) : GameState(game), texture(game->getTexture(MARBLESBACK)) {
	marbles = { 0,0,0,0 };
	ui = new UIChips(this, game);

	Marbles::marblesButtonCreation();

	RMarbles.push_back(game->getTexture(REDMARBLE));
	RMarbles.push_back(game->getTexture(GREENMARBLE));
	RMarbles.push_back(game->getTexture(BLUEMARBLE));
	RMarbles.push_back(game->getTexture(YELLOWMARBLE));
	
}


void Marbles::generateMarbles() {
	//En un vector voy metiendo aleatoriamente +1, representando ROJO/VERDE/AZUL/AMARILLO
	int pos = 1;
	SDL_Rect auxBox;

	marbles = { 0,0,0,0 };
	for (int i = 0; i < 3; i++) {
		int color = rand() % 3;
		marbles[color]++;
		auxBox.x = 0/*Game::WIN_WIDTH / 5*/ * pos;
		auxBox.y =0 /*Game::WIN_HEIGHT / 5*/;
		auxBox.w = (124.0 / 1920.0 * Game::WIN_WIDTH);
		auxBox.h = (124.0 / 1080.0 * Game::WIN_HEIGHT);
		
		RMarbles[color]->render(auxBox);
		pos++;
	}
	pos = 0;
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
	generateMarbles();

}

void Marbles::render() const {
	texture->render();
	GameState::render();
}
void  Marbles::marblesButtonCreation() {
	//Botones cuadrados para las apuestas de 1 color / BUTTONMARBLES1

	//ROJO
	buttonType1_1 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW1- marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2*PosPH1- 2*marginH, PosPW1, PosPH1, game->getTexture(BUTTONMARBLES1),1, {1,0,0,0});
	addObjects(buttonType1_1);
	addEventListener(buttonType1_1);
	//VERDE
	buttonType1_2 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW1 - marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH, PosPW1, PosPH1, game->getTexture(BUTTONMARBLES1),1,{0,1,0,0});
	addObjects(buttonType1_2);
	addEventListener(buttonType1_2);
	//AZUL
	buttonType1_3 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - 2*marginH, PosPW1, PosPH1, game->getTexture(BUTTONMARBLES1),1,{0,0,1,0});
	addObjects(buttonType1_3);
	addEventListener(buttonType1_3);
	//AMARILLO
	buttonType1_4 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH, PosPW1 , PosPH1, game->getTexture(BUTTONMARBLES1),1,{0,0,0,1});
	addObjects(buttonType1_4);
	addEventListener(buttonType1_4);

	//Botones rectangulares para las apuestas de 2 colores /BUTTONMARBLES2

	//ROJO/VERDE
	buttonType2_1 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - 3 * PosPW2 - PosPW1- 4*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2-marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2 ,{1,1,0,0});
	addObjects(buttonType2_1);
	addEventListener(buttonType2_1);
	//ROJO/ROJO
	buttonType2_2 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2-2 * marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{2,0,0,0});
	addObjects(buttonType2_2);
	addEventListener(buttonType2_2);
	//VERDE/VERDE
	buttonType2_3 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1-marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,2,0,0});
	addObjects(buttonType2_3);
	addEventListener(buttonType2_3);
	//ROJO/AMARILLO
	buttonType2_4 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2*marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{1,0,0,1});
	addObjects(buttonType2_4);
	addEventListener(buttonType2_4);
	//VERDE/AZUL
	buttonType2_5 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,1,1,0});
	addObjects(buttonType2_5);
	addEventListener(buttonType2_5);
	//ROJO/AZUL
	buttonType2_6 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW1 + 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2*marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{1,0,1,0});
	addObjects(buttonType2_6);
	addEventListener(buttonType2_6);
	//VERDE/AMARILLO
	buttonType2_7 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW1 + 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 -  marginH, PosPW2 , PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,1,0,1});
	addObjects(buttonType2_7);
	addEventListener(buttonType2_7);
	//AZUL/AZUL
	buttonType2_8 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,0,2,0});
	addObjects(buttonType2_8);
	addEventListener(buttonType2_8);
	//AMARILLO/AMARILLO
	buttonType2_9 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,0,0,2});
	addObjects(buttonType2_9);
	addEventListener(buttonType2_9);
	//AMARILLO/AZUL
	buttonType2_10 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + 2 * PosPW2 + PosPW1 + 4*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2- marginH, PosPW2, PosPH2, game->getTexture(BUTTONMARBLES2),2,{0,0,1,1});
	addObjects(buttonType2_10);
	addEventListener(buttonType2_10);

	//Botones rectangulares para las apuestas individuales de 3 mismos colores /	BUTTONMARBLES

	//ROJO/ROJO/ROJO
	buttonType3_1 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - 2 * PosPW3 - PosPW1- 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4)-3*marginH, PosPW3, PosPH3, game->getTexture(BUTTONMARBLES3),3,{3,0,0,0});
	addObjects(buttonType3_1);
	addEventListener(buttonType3_1);
	//VERDE/VERDE/VERDE
	buttonType3_2 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW3 - PosPW1 - 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) -3* marginH, PosPW3, PosPH3, game->getTexture(BUTTONMARBLES3),3,{0,3,0,0});
	addObjects(buttonType3_2);
	addEventListener(buttonType3_2);
	//AZUL/AZUL/AZUL
	buttonType3_3 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW1 + 2*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3*marginH, PosPW3, PosPH3, game->getTexture(BUTTONMARBLES3),3,{0,0,3,0});
	addObjects(buttonType3_3);
	addEventListener(buttonType3_3);
	//AMARILLO/AMARILLO/AMARILLO
	buttonType3_4 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 + PosPW3 + PosPW4 / 2 + 3*marginW, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3*marginH, PosPW3, PosPH3, game->getTexture(BUTTONMARBLES3),3,{0,0,0,3});
	addObjects(buttonType3_4);
	addEventListener(buttonType3_4);

	//Boton cuadrado para la apuesta de todos los posibles combianciones de tres mismos colores / BUTTONMAARBLES4
	buttonType4_1 = new ButtonMarbles(this, Game::WIN_WIDTH / 2 - PosPW1, Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - PosPH4 - 3*marginH, PosPW4, PosPH4, game->getTexture(BUTTONMARBLES4),4,{3,3,3,3});
	addObjects(buttonType4_1);
	addEventListener(buttonType4_1);
}

void
Marbles::createMarbleButton(double x, double y, double width, double height, Texture texture, std::vector<int> bet) {
	/*Button* btn = new MarblesButton(this, x, y, width, height, texture, bet);
	addObjects(btn);
	addEventListener(btn);*/
}