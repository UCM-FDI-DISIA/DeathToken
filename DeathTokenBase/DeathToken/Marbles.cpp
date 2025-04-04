#include "Marbles.h"
#include "Game.h"	
#include <iostream>
#include <random>
std::vector<int> Marbles::blockedMarble = { 0, 0,0,0};

Marbles::Marbles(Game* game) : GameState(game), texture(game->getTexture(MARBLESBACK)),
	marbles({ 0,0,0,0 }),
	RMarbles({ game->getTexture(REDMARBLE),game->getTexture(GREENMARBLE),
	game->getTexture(BLUEMARBLE),
	game->getTexture(YELLOWMARBLE) }),
	bInsanity (false)
{
	ui = new UIMarbles(this, game, this);
	Marbles::marblesButtonCreation();
	hud = new HUDBet(this);
}
Marbles::~Marbles() {
	
	HUDManager::popGame();
	delete ui;
}

void  Marbles::generateMarbles() {
	//En un vector voy metiendo aleatoriamente +1, representando ROJO/VERDE/AZUL/AMARILLO
	marbles = { 0,0,0,0 };
	drawnMarbles.clear();

	std::vector<int> validColors;

	for (int i = 0; i < blockedMarble.size(); i++) {
		if (blockedMarble[i] == 0) {
			validColors.push_back(i);
		}
	}

	int pos = 1;
	SDL_Rect auxBox;
	std::uniform_int_distribution<> distrib(0, validColors.size() - 1);

	for (int i = 0; i < 3; i++) {
		//int color;
		int color = validColors[distrib(game->getGen())];

		marbles[color]++;
		auxBox.x = Game::WIN_WIDTH /4 * pos;
		auxBox.y = Game::WIN_HEIGHT/  6;
		auxBox.w = (int)(124.0 / 1920.0 * Game::WIN_WIDTH);
		auxBox.h = (int)(124.0 / 1080.0 * Game::WIN_HEIGHT);
		
		drawnMarbles.push_back({ RMarbles[color], auxBox });
		pos++;
	}
	pos = 0;
}
int  Marbles::checkBets() {
	int moneyWin = 0;
	turnMoneyBet = 0;

	//Cuando se hagan los botones cada apuesta hecha se metera en un map indicando que apuesta 
	//hecha en un vector y el multi que da si gana

	for (const auto& [key, typeBet] : bets) { //Recorremos el mapa
		bool won = true;
		bool wonTriple = false;

		if (typeBet.typeOfBet == std::vector<int>{3, 3, 3, 3}) {// Si apuesta a cualquier triple
			for (int i = 0; i < typeBet.typeOfBet.size(); i++) { //recorremos el vector de la apuesta hecha
				if (marbles[i] == 3) {// si has salido 3 canicas del mismo color entra en true
					wonTriple = true;
					break;
				}
			}
		}


		for (int i = 0; i < typeBet.typeOfBet.size(); i++) {
			if (marbles[i] < typeBet.typeOfBet[i]) {//Si hay  mas canicas apostadas que canicas sacadas, le jugador pierde
				won = false;
				break;
			}
		}
		
		if (won|| wonTriple) {
			moneyWin += typeBet.moneyBet * typeBet.multiplier;
		}
		turnMoneyBet += typeBet.moneyBet;
	}

	return moneyWin;
}

void Marbles::startRound() {
	generateMarbles();//Se generar las canicas aleatorias
	long long moneyWin = checkBets();//Comparar canicas con apuesta
	//Segun la apuesta porX al dinero metido

	if (moneyWin > 0) {
		game->push(new Award(game, (GameState*)this, turnMoneyBet, moneyWin));
	}
	else {
		PlayerEconomy::setBet(0);
		hud->refresh();
	}
	
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


	switch (type) {
	case 1:
		multiplier = 2;
		break;
	case 2:
	case 4:
		multiplier = 5;
		break;
	case 3:
		multiplier = 20;
		break;
	}
	ButtonMarbles* btnMarbles = new ButtonMarbles(this, game, ui, x, y, width, height, texture, textureC, type, NCMarbles);
	marbleButtons.push_back(btnMarbles);
	//if (!(NCMarbles[i] >= blockedMarble[i] && blockedMarble[i] != 0)) {
	addObjects(marbleButtons.back());
	addEventListener(marbleButtons.back());
	btnMarbles->connect([this, NCMarbles, multiplier, btnMarbles]() { newBet(NCMarbles, multiplier, moneyBet, btnMarbles); });
}

void Marbles::newBet(std::vector<int> typeOfBet, int multiplier, int moneyBet, ButtonMarbles* btnMarbles) {
	
	moneyBet = ui->currentChipValue();

	bets[clave] = { typeOfBet, multiplier, moneyBet };
	clave++;

}

void Marbles::clearBets() {
	setbInsanity(false);
	blockedMarble = { 0,0,0,0 };
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

void Marbles::setBlockedMarble(std::vector<int> blocked)
{
	blockedMarble = blocked;
}
 std::vector<int> Marbles::getBlockedMarble() {
	return blockedMarble;
}

bool Marbles::getbInsanity()
{
	return bInsanity;
}

void Marbles::setbInsanity(bool insanity)
{
	bInsanity = insanity;
}
