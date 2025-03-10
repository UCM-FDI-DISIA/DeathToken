#include "BaccaratBlackjack.h"

BaccaratBlackjack::BaccaratBlackjack(Game* game) : Baccarat(game) {
	player3->frame = 14;
	banker3->frame = 14;
}

void BaccaratBlackjack::handCards() {
	Baccarat::handCards();
}

void BaccaratBlackjack::startRound() {
	handCards();
	//eleccion frame cartas
	player1->frame = mat.player[0];
	//banker1->frame = mat.banker[0];
	player2->frame = mat.player[1];
	banker2->frame = mat.banker[1];
	askCards();//borramos mazo repartido
}

void BaccaratBlackjack::askCards() {
	int xBut = Game::WIN_WIDTH * 4 / 5, yBut = Game::WIN_HEIGHT * 3 / 4, wBut = Game::WIN_WIDTH / 10, hBut = Game::WIN_HEIGHT / 7;
	more = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
	addObjects(more);
	addEventListener(more);
	more->connect([this]() { handOneCard(false); });
	yBut = Game::WIN_HEIGHT * 3 / 5;
	stand = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
	addObjects(stand);
	addEventListener(stand);
	stand->connect([this]() { clearDeck(); });
}

void BaccaratBlackjack::handOneCard(bool banker) {
	rndNum = generateRnd();
	if (!banker) {
		mat.player.push_back(rndNum);
	}
	else
	{
		mat.banker.push_back(rndNum);
	}
	cardsVec.push_back(rndNum);
}
