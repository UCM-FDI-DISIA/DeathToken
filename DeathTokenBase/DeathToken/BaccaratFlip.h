#pragma once
#include "baccarat.h"
class BaccaratFlip : public Baccarat
{
private:
	Texture* text;
	Texture* intro;
	SDL_Rect title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	int width = 0;
	int height = 0;
	float time = 0;
	float actual = 0;
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
	bool animOn = true;
	vector<int> extraVals;
	//contadores cartas extra en cada mazo
	int extraP = 0;
	int extraB = 0;
	//valor del frame de la tercera
	int tercera;
	int segunda;
	int primera;
	//borra botones
	bool card1 = false;
	bool card2 = false;
	bool card3 = false;
public:
	BaccaratFlip(Game* game);
	virtual ~BaccaratFlip() {};
	void addCards() override;
	void handleExtraCards();
	void startRound() override;
	void cardButton();
	void deckButton();
	void clearDeck() override;
	void render() const override;
	void update() override;
	void showTutorial() override {};
};
