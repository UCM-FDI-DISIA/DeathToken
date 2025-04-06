#pragma once
#include "BaccaratBet.h"
#include "BaccaratBlackjack.h"
#include "BaccaratFlip.h"
class Game;

class CrazyBaccaratManager : public GameState
{
	Game* game;
	BaccaratBet* bBet;
	BaccaratFlip* bFlip;
	BaccaratBlackjack* bBJ;
public:
	CrazyBaccaratManager(Game* game);//textura de las cartas o que se eliga directamente en randomCard
	void update() override;
	void randomCard();//las cartas tienen que ser botones que te llevan a la escena de cada juego, 
	//clase que hace de manager de los 3 juegos distintos de baccarat en modo locura
	//cuando hay locura se hace que salga esto en el baccarat, sale una carta aleatoria y ya se cambia el juego
};

