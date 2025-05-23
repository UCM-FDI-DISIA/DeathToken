#pragma once
#include "baccarat.h"
#include <vector>
class BaccaratBlackjack : public Baccarat
{
	Texture* counterEx;
	Texture* counterBEx;
	Texture* tex;
	int playerXpos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 30);
	int playerYpos = (int)(Game::WIN_HEIGHT / 5.33);
	int bankerXpos = (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 + Game::WIN_WIDTH / 30);
	int bankerYpos = (int)(Game::WIN_HEIGHT / 5.32);
	Button* more;
	Button* stand;
	bool canAsk = true; //se pone en false cuando player planta
	vector<Card*> playerCardVec;
	vector<Card*> bankerCardVec;
	bool win = false;
	Texture* intro;
	SDL_Rect title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	int width = 0;
	int height = 0;
	int ctFrameEx = 14;
	int ctFrameBEx = 14;
	float time = 0;
	float actual = 0;
	bool animOn = true;
	bool playing = false;
	SDL_Rect ctEx = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3) + Game::WIN_WIDTH / 60, (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 5.4), Game::WIN_WIDTH / 40, Game::WIN_HEIGHT / 16 };
	SDL_Rect ctBEx = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42) + Game::WIN_WIDTH / 100, (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 5.4) , Game::WIN_WIDTH / 40, Game::WIN_HEIGHT / 16 };
public:
	BaccaratBlackjack(Game* game);
	virtual ~BaccaratBlackjack() { delete more; delete stand; };
	void update() override;
	void render() const override;
	void victory();
	void handCards() override;
	void handOneCard();
	void bancaAI();
	void startRound() override;
	int totalCards(vector<int>);
	void clearDeck() override;
	void showTutorial() override {};
};

