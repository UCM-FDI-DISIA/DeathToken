#pragma once

#include "gameState.h"
#include "vector"
#include "Texture.h"
#include "Button.h"
#include <map>

class Marbles : public GameState
{
protected:
	struct Bet {
		std::vector<int> typeOfBet;
		int multiplier;
	};
	
	Texture* texture;
	std::vector<int> marbles;
	std::map<int, Bet> bets;
	bool play = false;
	int moneyBet;
	//Botones cuadrados para las apuestas de 1 color / BUTTONMARBLES1
	Button* buttonType1_1;
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
	Button* buttonType4_1;

public:
	Marbles(Game* game);

	void render() const override;
	void update() override;

	void generateMarbles();
	int checkBets(int moneyBet);
	void startRound();

	//Detectar botones y que apuesta hace y con que cantidad de monedas
	//Metodo play que hace que el juego lanze las 3 bolas de colores con un random
	//Con las bolas que salen detectar si estan igual que la apuesta
	//dependiendo de que apuesta ganadora, dar un mult de las fichas que apuestas
};

