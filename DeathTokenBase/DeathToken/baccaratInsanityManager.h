#pragma once
#include "baccaratBet.h"
#include "baccaratBlackjack.h"
#include "baccaratFlip.h"
class Game;

class BaccaratInsanityManager : public GameState
{
	Game* game;
	BaccaratBet* bBet;
	BaccaratFlip* bFlip;
	BaccaratBlackjack* bBJ;
public:
	BaccaratInsanityManager(Game* game);//textura de las cartas o que se eliga directamente en randomCard
	virtual ~BaccaratInsanityManager() {};
	void update() override;
	void render() const override;
	void randomCard();//las cartas tienen que ser botones que te llevan a la escena de cada juego, 
	//clase que hace de manager de los 3 juegos distintos de baccarat en modo locura
	//cuando hay locura se hace que salga esto en el baccarat, sale una carta aleatoria y ya se cambia el juego
};

