#include "baccaratBet.h"
#include "sdlUtils.h"

BaccaratBet::BaccaratBet(Game* game) : Baccarat(game, true), intro(game->getTexture(BET)) {
	ui->isBet = true;
	btnBaccarattie = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 , Game::WIN_WIDTH / 4 , Game::WIN_HEIGHT / 8);
	bacButtons.push_back(btnBaccarattie);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarattie->connect([this]() {
		if (!betOnPlayer && !betOnBanker)
		{
			newBet(8, 0, btnBaccarattie); betOnTie = true;
			btnBaccaratbanker->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccaratplayer->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });

		btnBaccaratbanker = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 6);
		bacButtons.push_back(btnBaccaratbanker);
		addObjects(bacButtons.back());
		addEventListener(bacButtons.back());
		btnBaccaratbanker->connect([this]() { if (!betOnPlayer && !betOnTie) {
			newBet(2, 1, btnBaccaratbanker); betOnBanker = true;
			btnBaccarattie->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccaratplayer->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });

		btnBaccaratplayer = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8);
		bacButtons.push_back(btnBaccaratplayer);
		addObjects(bacButtons.back());
		addEventListener(bacButtons.back());
		btnBaccaratplayer->connect([this]() { if (!betOnTie && !betOnBanker) {
			newBet(2, 2, btnBaccaratplayer); betOnPlayer = true;
			btnBaccaratbanker->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccarattie->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });
}

void BaccaratBet::win() {
	playerComb = 0, bankerComb = 0;

	for (int i = 0; i < mat.player.size(); i++) {
		if (mat.player[i] > 9) mat.player[i] = 0;
		playerComb += mat.player[i];
	}
	for (int i = 0; i < mat.banker.size(); i++) {
		if (mat.banker[i] > 9) mat.banker[i] = 0;
		bankerComb += mat.banker[i];
	}
	playerComb = playerComb % 10;
	bankerComb = bankerComb % 10;

	int multi = 0;
	if (playerComb > bankerComb) {
		playerBet = true;
	}
	else if (playerComb < bankerComb) {
		bankerBet = true;
	}
	else if (playerComb == bankerComb) {
		tieBet = true;
	}
	int totalBet = 0;
	for (int i = 0; i < bets.size(); i++) {
		if (bets[i].betType == 0 && tieBet) {
			totalBet += bets[i].moneyBet;
			if (multi == 0)
			{
				multi = bets[i].multiplier;
			}
		}
		else if (bets[i].betType == 1 && bankerBet) {
			totalBet += bets[i].moneyBet;
			if (multi == 0)
			{
				multi = bets[i].multiplier;
			}
		}
		else if (bets[i].betType == 2 && playerBet) {
			totalBet += bets[i].moneyBet;
			if (multi == 0)
			{
				multi = bets[i].multiplier;
			}
		}
	}

	if (totalBet > 0) {
		game->push(new Award(game, (GameState*)this, totalBet, totalBet * multi, true));
		hasWon = true;
	}
	PlayerEconomy::setBet(0);
	hud->refresh();
	clearBets();
	timeForWin = true;
}

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
	ui->setOnBet(true);
	startRound();
	PlayerEconomy::addInsanity(1);
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
	if (!animOn && PlayerEconomy::getInsanity() > 0 && (mat.player.size() == 0 && mat.player.size() == 0) && ui->getOnBet())
	{
		PlayerEconomy::subtractInsanity(1);
		Baccarat::startRound();
	}
}

void BaccaratBet::acumulate() {
	if (!buttonsOn) {
		int xBut = (int)(Game::WIN_WIDTH * 7.16 / 8), yBut = (int)(Game::WIN_HEIGHT * 4.5 / 7), wBut = Game::WIN_WIDTH / 15, hBut = Game::WIN_WIDTH / 15;
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
	if (mat.player.size() == 0 && mat.player.size() == 0)
		GameState::update();
	if (cardAnim && SDL_GetTicks() - animTime > 75.0f && frame < 9)
	{
		frame++;
		animTime = SDL_GetTicks();
		if (frame == 7) {
			if (animInCard == 0)
			{
				player1->frame = mat.player[0];
				if (mat.player[0] > 9)
					ctFrame = 0;
				else
					ctFrame = mat.player[0];
			}
			else if (animInCard == 1)
			{
				banker1->frame = mat.banker[0];
				if (mat.banker[0] > 9)
					ctFrameB = 0;
				else
					ctFrameB = mat.banker[0];
			}
			else if (animInCard == 2)
			{
				player2->frame = mat.player[1];
				if (mat.player[1] <= 9)
				{
					ctFrame += mat.player[1];
					ctFrame = ctFrame % 10;
				}
			}
			else if (animInCard == 3)
			{
				banker2->frame = mat.banker[1];
				if (mat.banker[1] <= 9)
				{
					ctFrameB += mat.banker[1];
					ctFrameB = ctFrameB % 10;
				}
			}
		}
		if (frame == 9 && animInCard < 3) {
			frame = 0;
			if (animInCard == 0)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
			else if (animInCard == 1)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
			else if (animInCard == 2)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
		}
	}
	if (frame == 9) {
		handThird();//reparte tercera
		cardAnim = false;
		frame = 0;
		animInCard = 0;
		sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
	}
	if (thirdPlayerMove) {
		player3->setPos(player3->position() - Vector2D(5, 0));
		if (player3->position().getX() <= (int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81))
		{
			thirdPlayerMove = false;
			if (mat.player[2] <= 9)
			{
				ctFrame += mat.player[2];
				ctFrame = ctFrame % 10;
			}
			goForWin = true;
		}
	}
	if (thirdBankerMove) {
		banker3->setPos(banker3->position() + Vector2D(5, 0));
		if (banker3->position().getX() >= (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5))
		{
			thirdBankerMove = false;
			if (mat.banker[2] <= 9)
			{
				ctFrameB += mat.banker[2];
				ctFrameB = ctFrameB % 10;
			}
			goForWin = true;
		}
	}
	if (goForWin)
	{
		btnBaccaratbanker->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15);
		btnBaccarattie->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 + 10);
		btnBaccaratplayer->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200);
		betOnPlayer = false;
		betOnBanker = false;
		betOnTie = false;
		win();
		goForWin = false;
	}
	if (bet != nullptr && stop != nullptr && !buttonsOn) {
		bet = nullptr;
		stop = nullptr;
		eventHandlers.pop_back();
		eventHandlers.pop_back();
		gameObjects.pop_back();
		gameObjects.pop_back();
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
	if (timeForWin) {
		float dt = SDLUtils::getDeltaTime();
		tiempo += dt;
		if (tiempo > 3)
		{
			if (hasWon) {
				acumulate();
				buttonsOn = true;
				hasWon = false;
			}
			timeForWin = false;
			tiempo = 0;
			playerBet = false;
			bankerBet = false;
			tieBet = false;
			player1->frame = 0;
			player2->frame = 0;
			banker1->frame = 0;
			banker2->frame = 0;
			banker3->frame = 14;
			player3->frame = 14;
			ctFrame = 14;
			ctFrameB = 14;
			clearDeck();
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


void BaccaratBet::clearBets() {
	Baccarat::clearBets();
	btnBaccaratbanker->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15);
	btnBaccarattie->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 + 10);
	btnBaccaratplayer->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200);
	betOnBanker = false;
	betOnPlayer = false;
	betOnTie = false;
}
