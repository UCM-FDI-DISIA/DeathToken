#include "BaccaratFlip.h"

BaccaratFlip::BaccaratFlip(Game* game) : Baccarat(game) {
	createBaccaratBetButton(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70, (int)(Game::WIN_HEIGHT / 5.33), Game::WIN_WIDTH / 3, Game::WIN_HEIGHT / 8);//rect player
	extra1 = createCard(Game::WIN_WIDTH / 2 - 150, Game::WIN_HEIGHT / 1.5, 0, 14); // frame 14 = boca abajo
	extra2 = createCard(Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 1.5, 0, 14);
	extra3 = createCard(Game::WIN_WIDTH / 2 + 150, Game::WIN_HEIGHT / 1.5, 0, 14);
	handleExtraCards();
}

//void BaccaratFlip::addCards()
//{
//	Baccarat::addCards();
//	//// tres cartas extra boca abajo
//	//extra1 = createCard(Game::WIN_WIDTH / 2 - 150, Game::WIN_HEIGHT / 1.5, 0, 14); // frame 14 = boca abajo
//	//extra2 = createCard(Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 1.5, 0, 14);
//	//extra3 = createCard(Game::WIN_WIDTH / 2 + 150, Game::WIN_HEIGHT / 1.5, 0, 14);
//}

void BaccaratFlip::handleExtraCards()
{
	// Generar 3 cartas aleatorias
	extraVals.clear();
	for (int i = 0; i < 3; ++i) {
		int val = generateRnd();
		extraVals.push_back(val);
	}
}

void BaccaratFlip::render() const {
	Baccarat::render();
	GameState::render();
}

void
BaccaratFlip::createBaccaratBetButton(int x, int y, int width, int height) {
	ButtonBaccarat* btnBaccarat = new ButtonBaccarat(this, game, ui, x, y, width, height);
	bacButtons.push_back(btnBaccarat);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarat->connect([this, x, btnBaccarat]() { newBet(0, moneyBet, btnBaccarat); });
}
