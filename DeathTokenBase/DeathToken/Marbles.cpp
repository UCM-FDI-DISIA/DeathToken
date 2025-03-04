#include "Marbles.h"
#include "Game.h"	
#include <iostream>
#include <random>

Marbles::Marbles(Game* game) : GameState(game), texture(game->getTexture(MARBLESBACK)),
	marbles( { 0,0,0,0 }),
	ui( new UIMarbles(this, game, this)),


	RMarbles({ game->getTexture(REDMARBLE),game->getTexture(GREENMARBLE),
	game->getTexture(BLUEMARBLE),
	game->getTexture(YELLOWMARBLE) })
	{
	Marbles::marblesButtonCreation();

}
Marbles::~Marbles() {
	for (auto b : marbleButtons) {
		delete b;
	}
	delete ui;


}

void  Marbles::generateMarbles() {
	//En un vector voy metiendo aleatoriamente +1, representando ROJO/VERDE/AZUL/AMARILLO
	marbles = { 0,0,0,0 };
	drawnMarbles.clear();
	int pos = 1;
	SDL_Rect auxBox;
	for (int i = 0; i < 3; i++) {
		std::uniform_int_distribution<> distrib(0, 3);
		int color = distrib(game->getGen());

		//int color = rand() % 4; // usáis "rand" (que es C) y luego la lib de C++. Usad solo la de C++.
		marbles[color]++;
		auxBox.x = Game::WIN_WIDTH / 4 * pos;
		auxBox.y = Game::WIN_HEIGHT/  6;
		auxBox.w = (int)(124.0 / 1920.0 * Game::WIN_WIDTH);
		auxBox.h = (int)(124.0 / 1080.0 * Game::WIN_HEIGHT);
		
		drawnMarbles.push_back({ RMarbles[color], auxBox });
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
		
		// cleon no sabe qué es esto, pero sospecha
		for (int i = 0; i < 4; i++) {
			if (marbles[i] <= typeBet.typeOfBet[i]) { //Si algun numero del vector es mayor a las canicas, se da esa apuesta como perdida
				won = false;
			}
		}

		if (won) {//Si ha ganado esa apuesta se calcula lo ganado
			moneyWin += typeBet.moneyBet * typeBet.multiplier;
			
		}
	}
	return moneyWin;
}

void Marbles::startRound() {
	generateMarbles();//Se generar las canicas aleatorias
	int moneyWin = checkBets(moneyBet);//Comparar canicas con apuesta
	//Segun la apuesta porX al dinero metido

	  #if _DEBUG
	if (moneyWin > 0) {

		std::cout << "HAS GANDADO" << moneyWin;
		
	}
	else {
		std::cout << "HAS PERDIDO";

	}
	  #endif

	clearBets();
}
void Marbles::update() {
	
	GameState::update();
}

void Marbles::render() const {
	texture->render();
	GameState::render();
	for (const auto& marble : drawnMarbles) {
		marble.first->render(marble.second); 
	}
}
void  Marbles::marblesButtonCreation() {
	//Botones cuadrados para las apuestas de 1 color / BUTTONMARBLES1
	
	//ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1 - marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - 2 * marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 1,0,0,0 });
	//VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1 - marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,1,0,0 });
	//AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - 2 * marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,0,1,0 });
	//AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,0,0,1 });
	
	//Botones rectangulares para las apuestas de 2 colores /BUTTONMARBLES2

	//ROJO/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 3 * PosPW2 - PosPW1 - 4 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,1,0,0 });
	//ROJO/ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 2,0,0,0 });
	//VERDE/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,2,0,0 });
	//ROJO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,0,0,1 });
	//VERDE/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,1,1,0 });
	//ROJO/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,0,1,0 });
	//VERDE/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,1,0,1 });
	//AZUL/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,2,0 });
	//AMARILLO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,0,2 });
	//AMARILLO/AZUL	
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + 2 * PosPW2 + PosPW1 + 4 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,1,1 });
	
	//Botones rectangulares para las apuestas individuales de 3 mismos colores /	BUTTONMARBLES
	
	//ROJO/ROJO/ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW3 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH), (int)(PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 3,0,0,0 });
	//VERDE/VERDE/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW3 - PosPW1 - 2 * marginW),(int)( Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH),(int)( PosPW3),(int)( PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,3,0,0 });
	//AZUL/AZUL/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW),(int)( Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH),(int)( PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,0,3,0 });
	//AMARILLO/AMARILLO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW3 + PosPW4 / 2 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH), (int)(PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,0,0,3 });
	
	//Boton cuadrado para la apuesta de todos los posibles combianciones de tres mismos colores / BUTTONMAARBLES4
	
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1),(int) (Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - PosPH4 - 3 * marginH),(int) PosPW4, (int)PosPH4, game->getTexture(BUTTONMARBLES4), game->getTexture(BUTTONMARBLES4CLCK), 4, { 3,3,3,3 });
}

void
Marbles::createMarbleButton(int x, int y, int width, int height, Texture* texture, Texture* textureC, int type, std::vector<int> NCMarbles) {
	
	int multiplier = 0;

	if(type == 1) {
		multiplier = 2;
	}
	else if (type == 2) {
		multiplier = 5;

	}
	else if (type == 3) {
		multiplier = 20;

	}
	else if (type == 4) {
		multiplier = 5;
	}
	ButtonMarbles* btnMarbles = new ButtonMarbles(this, game, ui, x, y, width, height, texture, textureC, type, NCMarbles);
	marbleButtons.push_back(btnMarbles);
	addObjects(marbleButtons.back());
	addEventListener(marbleButtons.back());
	btnMarbles->connect([this, NCMarbles, multiplier, btnMarbles]() { newBet(NCMarbles, multiplier, moneyBet, btnMarbles); });
}

void Marbles::newBet(std::vector<int> typeOfBet, int multiplier, int moneyBet, ButtonMarbles* btnMarbles) {
	
	moneyBet = btnMarbles->getBet();

	bets[clave] = { typeOfBet, multiplier, moneyBet };
	clave++;
}

void Marbles::clearBets() {
	betsHistory = bets;
	bets.clear();
	for (auto i : marbleButtons)
	{
		i->clear();
	}
}

void Marbles::repeat()
{
	bets = betsHistory;
	for (auto i : marbleButtons)
	{
		i->repeat();
	}
}