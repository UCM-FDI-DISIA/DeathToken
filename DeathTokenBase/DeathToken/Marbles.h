#pragma once

#include "gameState.h"
#include "vector"
#include "Texture.h"
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

