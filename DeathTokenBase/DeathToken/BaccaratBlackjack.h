#pragma once
#include "Baccarat.h"
#include <vector>
class BaccaratBlackjack : public Baccarat
{
	float playerXpos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 30);
	float playerYpos = (int)(Game::WIN_HEIGHT / 5.33);
	float bankerXpos = (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 + Game::WIN_WIDTH / 30);
	float bankerYpos = (int)(Game::WIN_HEIGHT / 5.32);
	Button* more;
	Button* stand;
	bool canAsk = true; //se pone en false cuando player planta
	vector<Card*> playerCardVec;
	vector<Card*> bankerCardVec;
	bool win = false;

public:
	BaccaratBlackjack(Game* game);
	void update() override;
	void victory();
	void handCards() override;
	void handOneCard();
	void askCards();
	void bancaAI();
	void startRound() override;
	int totalCards(vector<int>);
	void clearDeck() override;
};

