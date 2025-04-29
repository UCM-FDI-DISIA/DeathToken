#pragma once
#include "baccarat.h"
class BaccaratBet : public Baccarat
{
	Button* bet = nullptr;
	Button* stop = nullptr;
	bool buttonsOn = false;
	Texture* intro;
	SDL_Rect title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	int width = 0;
	int height = 0;
	float time = 0;
	float actual = 0;
public:
	BaccaratBet(Game* game) : Baccarat(game), intro(game->getTexture(BET)) {};
	void acumulate();
	void repeatBet();
	void update() override;
	void render() const override;
	void didntWin();
};

