#pragma once
#include "Baccarat.h"
class BaccaratBlackjack : public Baccarat
{
	Button* more;
	Button* stand;
public:
	BaccaratBlackjack(Game* game);
	//void render() const override;
	void handCards() override;
	void handOneCard(bool banker);
	void askCards();
	void bancaAI();
	void startRound() override;
};

