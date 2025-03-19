#include "BaccaratFlip.h"

BaccaratFlip::BaccaratFlip(Game* game) : Baccarat(game) {
	createBaccaratBetButton(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70, (int)(Game::WIN_HEIGHT / 5.33), Game::WIN_WIDTH / 3, Game::WIN_HEIGHT / 8 );//rect player
}

void BaccaratFlip::render() const {
	Baccarat::render();

}

void
BaccaratFlip::createBaccaratBetButton(int x, int y, int width, int height) {
	ButtonBaccarat* btnBaccarat = new ButtonBaccarat(this, game, ui, x, y, width, height);
	bacButtons.push_back(btnBaccarat);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarat->connect([this, x, btnBaccarat]() { newBet(0, moneyBet, btnBaccarat); });
}
