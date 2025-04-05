#include "CrazyBaccaratManager.h"
#include "Game.h"

//CrazyBaccaratManager::CrazyBaccaratManager(Game* game) : game(game) {}
//
//void CrazyBaccaratManager::randomCard() {
//	uniform_int_distribution<> distrib(0, 2);
//
//	int num = distrib(game->getGen());
//
//	switch (num) {
//	case 0:
//		bBet = new BaccaratBet();
//		game->push(bBet);
//	case 1:
//		bFlip = new BaccaratFlip();
//		game->push(bFlip);
//	case 2:
//		bBJ = new BaccaratBlackjack(game);
//		game->push(bBJ);
//	}
//}