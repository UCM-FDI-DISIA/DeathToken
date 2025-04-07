#pragma once
#include "Baccarat.h"
class BaccaratFlip : public Baccarat
{
private:
	Texture* text;
	//botones de la carta
	Button* carta1;
	Button* carta2;
	Button* carta3;
	//botones mazos
	Button* banker;
	Button* player;
	//cartas extra
	Card* extra1;
	Card* extra2;
	Card* extra3;
	int chosen;
	int flips = 0;
	bool active = false;
	
	vector<int> extraVals;
public:
	BaccaratFlip(Game* game);
	void addCards() override;
	void handleExtraCards();
	void startRound() override;
	void cardButton();
	void deckButton();
	void clearDeck() override;
	void render() const override;
	void update() override;
};

