#include "baccaratBet.h"
#include "SDLUtils.h"

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
			betsHistory[i].multiplier = 8;
		}
		else {
			betsHistory[i].multiplier = 2;
		}
	}
}

void BaccaratBet::startRound()
{
	if (!animOn)
	{
		Baccarat::startRound();
	}
}

void BaccaratBet::acumulate() {
	if (!buttonsOn) {
		int xBut = (int)(Game::WIN_WIDTH * 7.07 / 8), yBut = (int)(Game::WIN_HEIGHT * 4.5 / 7), wBut = (int)Game::WIN_WIDTH / 18, hBut = (int)Game::WIN_WIDTH / 18;
		bet = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(TICK));
		addObjects(bet);
		addEventListener(bet);
		bet->connect([this]() { repeatBet(); });
		yBut = (int)(Game::WIN_HEIGHT * 4.5 / 9);
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
	title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	if (width < Game::WIN_WIDTH && height < Game::WIN_HEIGHT && animOn) {
		width += Game::WIN_WIDTH / 50;
		height += Game::WIN_HEIGHT / 50;

	}
	else {
		float dt = SDLUtils::getDeltaTime();
		time += dt;
		if (time - actual > 1)
		{
			animOn = false;
			width = 0;
			height = 0;
		}
	}
}

void BaccaratBet::render() const
{
	Baccarat::render();
	if (animOn)
	{
		SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
		SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
		SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
		SDL_RenderFillRect(game->getRenderer(), &black);
		intro->render(title);
	}
}
