#include "BaccaratBet.h"

void BaccaratBet::repeatBet() {
	for (int i = 0; i < betsHistory.size(); i++)
		bets[i] = { betsHistory[i].multiplier * 2, betsHistory[i].moneyBet * 2 };
	int currentBet = 0;
	for (int i = 0; i < bets.size(); i++) {
		currentBet += bets[i].moneyBet;
	}
	for (auto i : bacButtons)
	{
		i->repeatDoubleBet();
	}
	HUDManager::applyBet(currentBet);
}

void BaccaratBet::acumulate() {
	if (!buttonsOn) {
		int xBut = Game::WIN_WIDTH * 4 / 5, yBut = Game::WIN_HEIGHT * 3 / 4, wBut = Game::WIN_WIDTH / 10, hBut = Game::WIN_HEIGHT / 7;
		bet = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
		addObjects(bet);
		addEventListener(bet);
		bet->connect([this]() { repeatBet(); });
		yBut = Game::WIN_HEIGHT * 3 / 5;
		stop = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(SLOTSBUT));
		addObjects(stop);
		addEventListener(stop);
		stop->connect([this]() {});
	}
}

void BaccaratBet::update() {
	Baccarat::update();
	if (hasWon) {
		acumulate();
		buttonsOn = true;
		hasWon = false;
	}
}
