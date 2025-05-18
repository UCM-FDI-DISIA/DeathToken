#pragma once
#include "baccarat.h"
class BaccaratBet : public Baccarat
{
	ButtonBaccarat* btnBaccarattie;
	ButtonBaccarat* btnBaccaratplayer;
	ButtonBaccarat* btnBaccaratbanker;
	Button* bet;
	Button* stop;
	bool buttonsOn;
	Texture* intro;
	SDL_Rect title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	int width = 0;
	int height = 0;
	float time = 0;
	float actual = 0;
	bool animOn = true;
	bool betOnTie = false, betOnPlayer = false, betOnBanker = false;
public:
	BaccaratBet(Game* game);
	virtual ~BaccaratBet() {
		delete bet;
		delete stop;
	};
	void repeatBet();
	void update() override;
	void render() const override;
	void didntWin();
	void startRound() override;
	void showTutorial() override {};//para que no salte de una el tutorial
	void clearBets() override;
	void win() override;
};

