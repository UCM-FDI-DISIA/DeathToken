#include "BaccaratBlackjack.h"

BaccaratBlackjack::BaccaratBlackjack(Game* game) : Baccarat(game) {
	player3->frame = 14;
	banker3->frame = 14;
}

void BaccaratBlackjack::handCards() {
	Baccarat::handCards();
	if (totalCards(mat.player) == 21) {
		cout << "BlackJack!" << endl;
		game->push(new Award(game, (GameState*)this, 100, 400));
		win = true;
	}
}

void BaccaratBlackjack::update() {
	if (totalCards(mat.player) > 21) {
		cout << "pierdes" << endl;
		banker1->frame = mat.banker[0];
		win = true;
	}
}

void BaccaratBlackjack::victory() {
	if (totalCards(mat.player) > totalCards(mat.banker) && totalCards(mat.player) <= 21 || totalCards(mat.banker) > 21) {
		game->push(new Award(game, (GameState*)this, 100, 400));
	}
	else if (totalCards(mat.banker) > totalCards(mat.player) && totalCards(mat.banker) <= 21) {
		cout << "gana banker" << endl;
	}
	else if (totalCards(mat.banker) == totalCards(mat.player) && totalCards(mat.banker) <= 21 && totalCards(mat.player) <= 21 && !win) {
		game->push(new Award(game, (GameState*)this, 100, 100));
	}

}

void BaccaratBlackjack::startRound() {
	clearDeck();
	canAsk = true;
	win = false;
	handCards();
	//eleccion frame cartas
	player1->frame = mat.player[0];
	//banker1->frame = mat.banker[0];
	player2->frame = mat.player[1];
	banker2->frame = mat.banker[1];
	askCards();
}

void BaccaratBlackjack::askCards() {
	int xBut = Game::WIN_WIDTH * 4 / 5, yBut = Game::WIN_HEIGHT * 3 / 4, wBut = Game::WIN_WIDTH / 10, hBut = Game::WIN_HEIGHT / 7;
	more = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
	addObjects(more);
	addEventListener(more);
	more->connect([this]() { handOneCard(); });
	yBut = Game::WIN_HEIGHT * 3 / 5;
	stand = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
	addObjects(stand);
	addEventListener(stand);
	stand->connect([this]() { bancaAI(); });
}

void BaccaratBlackjack::handOneCard() {
	if (totalCards(mat.player) < 21 && canAsk) {
		rndNum = generateRnd();
		mat.player.push_back(rndNum);
		playerCardVec.push_back(createCard(playerXpos, playerYpos, 0, mat.player[mat.player.size() - 1]));
		playerXpos -= Game::WIN_WIDTH / 30;
		cardsVec.push_back(rndNum);
	}
}

void BaccaratBlackjack::bancaAI() {
	if (!win) {
		canAsk = false;
		banker1->frame = mat.banker[0];
		while (totalCards(mat.banker) < 17) {
			rndNum = generateRnd();
			mat.banker.push_back(rndNum);
			bankerCardVec.push_back(createCard(bankerXpos, bankerYpos, 0, mat.banker[mat.banker.size() - 1]));
			bankerXpos += Game::WIN_WIDTH / 30;
			cardsVec.push_back(rndNum);
		}
	}
	victory();
}

int BaccaratBlackjack::totalCards(vector<int> askedCards) {
	int t = 0;
	int marker = 0;
	for (int i : askedCards)
	{
		if (i > 10) i = 10;
		if (i == 1) {
			marker++;
			i = 11;
		}
		if (t + i > 21 && marker > 0) { t -= 10; marker--; }
		t += i;
	}
	return t;
}

void BaccaratBlackjack::clearDeck() {
	banker1->frame = 0;
	Baccarat::clearDeck();
	playerXpos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 30);
	bankerXpos = (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 + Game::WIN_WIDTH / 30);

	for (int i = bankerCardVec.size(); i > 0; i--) {
		bankerCardVec.pop_back();
		gameObjects.pop_back();
	}
	for (int i = playerCardVec.size(); i > 0; i--) {
		playerCardVec.pop_back();
		gameObjects.pop_back();
	}

	eventHandlers.pop_back();
	eventHandlers.pop_back();
	gameObjects.pop_back();
	gameObjects.pop_back();
}

