#include "baccaratInsanityManager.h"
#include "game.h"

BaccaratInsanityManager::BaccaratInsanityManager(Game* game) : game(game), GameState(game) {
}

void BaccaratInsanityManager::update()
{
	randomCard();
}

void BaccaratInsanityManager::randomCard() {
	uniform_int_distribution<> distrib(0, 2);

	int num = distrib(game->getGen());
	switch (num) {
	case 0:
	{
		bBet = new BaccaratBet(game);
		game->pop();
		game->push(bBet);
		break;
	}
	case 1:
	{
		bFlip = new BaccaratFlip(game);
		game->pop();
		game->push(bFlip);
		break;
	}
	case 2:
	{
		bBJ = new BaccaratBlackjack(game);
		game->pop();
		game->push(bBJ);
		break;
	}
	}
}