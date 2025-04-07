#include "baccaratBet.h"

void BaccaratBet::repeatBet() {

	for (int i = 0; i < betsHistory.size(); i++)
		bets[i] = { betsHistory[i].multiplier * 2, betsHistory[i].moneyBet * betsHistory[i].multiplier, betsHistory[i].betType };
	int currentBet = 0;
	for (int i = 0; i < bets.size(); i++) {
		currentBet += bets[i].moneyBet;
	}
	for (auto i : bacButtons)
	{
		i->repeatDoubleBet();
	}
	HUDManager::applyBet(currentBet);

	startRound();

	if (!hasWon) {
		didntWin();
	}
}

void BaccaratBet::didntWin() {
	buttonsOn = false;
	for (int i = 0; i < betsHistory.size(); i++) {
		if (betsHistory[i].betType == 0) {
			betsHistory[i].multiplier == 8;
		}
		else {
			betsHistory[i].multiplier = 2;
		}
	}
}

void BaccaratBet::acumulate() {
	if (!buttonsOn) {
		int xBut = Game::WIN_WIDTH * 7.07 / 8, yBut = Game::WIN_HEIGHT * 4.5 / 7, wBut = Game::WIN_WIDTH / 18, hBut = Game::WIN_WIDTH / 18;
		bet = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(TICK));
		addObjects(bet);
		addEventListener(bet);
		bet->connect([this]() { repeatBet(); });
		yBut = Game::WIN_HEIGHT * 4.5 / 9;
		stop = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(CROSS));
		addObjects(stop);
		addEventListener(stop);
		stop->connect([this]() { didntWin(); });
	}
}

void BaccaratBet::update() {
	Baccarat::update();
	if (bet != nullptr && stop != nullptr && !buttonsOn) {
		bet = nullptr;
		stop = nullptr;
		eventHandlers.pop_back();
		eventHandlers.pop_back();
		gameObjects.pop_back();
		gameObjects.pop_back();
	}
	if (hasWon) {
		acumulate();
		buttonsOn = true;
		hasWon = false;
	}
}
