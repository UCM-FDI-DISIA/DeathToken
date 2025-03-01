#pragma once

#include "gameState.h"
#include "vector"
#include "Texture.h"
#include "Button.h"
#include "Game.h"
#include "UI.h"
#include <map>
class Marbles : public GameState
{
protected:
	struct Bet {
		std::vector<int> typeOfBet;
		int multiplier= 0;
		int moneyBet= 0;
	};
	UIMarbles* ui;

	Texture* texture;
	std::vector<int> marbles;
	std::map<int, Bet> bets;
	std::map<int, Bet> betsHistory;
	std::vector<Texture*> RMarbles;
	std::vector<std::pair<Texture*, SDL_Rect>> drawnMarbles;
	std::vector<ButtonMarbles*> marbleButtons;
	bool play = false;
	int moneyBet;
	int clave = 0;

	//Botones cuadrados para las apuestas de 1 color / BUTTONMARBLES1
	/*Button* buttonType1_1;
	Button* buttonType1_2;
	Button* buttonType1_3;
	Button* buttonType1_4;
	//Botones rectangulares para las apuestas de 2 colores /BUTTONMARBLES2
	Button* buttonType2_1;
	Button* buttonType2_2;
	Button* buttonType2_3;
	Button* buttonType2_4;
	Button* buttonType2_5;
	Button* buttonType2_6;
	Button* buttonType2_7;
	Button* buttonType2_8;
	Button* buttonType2_9;
	Button* buttonType2_10;
	//Botones rectangulares para las apuestas individuales de 3 mismos colores /	BUTTONMARBLES
	Button* buttonType3_1;
	Button* buttonType3_2;
	Button* buttonType3_3;
	Button* buttonType3_4;

	//Boton cuadrado para la apuesta de todos los posibles combianciones de tres mismos colores / BUTTONMAARBLES4
	Button* buttonType4_1;*/
	double PosPW1 = (118.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH1 = (118.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW3 = (302.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH3 = (102.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW2 = (166.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH2 = (83.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW4 = (239.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH4 = (180.0 / 1080.0) * Game::WIN_HEIGHT;
	double marginW = (5.0 / 1920.0) * Game::WIN_WIDTH;
	double marginH = (5.0 / 1080.0) * Game::WIN_WIDTH;
public:
	Marbles(Game* game);
	~Marbles();
	void render() const override;
	void update() override;

	void  generateMarbles();
	int checkBets(int moneyBet);
	void startRound();
	void createMarbleButton(int x, int y, int width, int height, Texture*, Texture*, int type, std::vector<int> NCMarbles);
	void marblesButtonCreation();
	void newBet(std::vector<int> typeOfBet, int multiplier, int moneyBet, ButtonMarbles* btnMarbles);
	void clearBets();
	void repeat();
	
	//Detectar botones y que apuesta hace y con que cantidad de monedas
	//Metodo play que hace que el juego lanze las 3 bolas de colores con un random
	//Con las bolas que salen detectar si estan igual que la apuesta
	//dependiendo de que apuesta ganadora, dar un mult de las fichas que apuestas
};

