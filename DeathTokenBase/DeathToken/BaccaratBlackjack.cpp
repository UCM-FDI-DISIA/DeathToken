#include "baccaratBlackjack.h"


BaccaratBlackjack::BaccaratBlackjack(Game* game) : Baccarat(game, true), tex(game->getTexture(BLACKMAT)), intro(game->getTexture(JACK)) {
	ui->isBlackJack = true;

	createBaccaratButton(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8, 2, 2);
}

void BaccaratBlackjack::handCards() {
	Baccarat::handCards();
	if (totalCards(mat.player) == 21) {
		game->push(new Award(game, (GameState*)this, 100, 400));
		win = true;
	}
}

void BaccaratBlackjack::render() const {
	tex->render();
	GameState::render();
	if (animOn)
	{
		SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
		SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
		SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
		SDL_RenderFillRect(game->getRenderer(), &black);
		intro->render(title);
	}
}

void BaccaratBlackjack::update() {
	if (mat.player.size() == 0 && mat.player.size() == 0)
		GameState::update();
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
	if (!canAsk && !timeForWin) {
		banker2->frame = mat.banker[1];
		victory();
	}

	if (totalCards(mat.player) > 21) {
		banker2->frame = mat.banker[1];
		timeForWin = true;
	}

	if (timeForWin) {
		float dt = SDLUtils::getDeltaTime();
		tiempo += dt;
		if (tiempo > 3)
		{
			timeForWin = false;
			tiempo = 0;
			canAsk = true;
			win = true;
			clearDeck();
		}
	}
}

void BaccaratBlackjack::victory() {
	int totalBet = 0;
	for (int i = 0; i < bets.size(); i++) { totalBet += bets[i].moneyBet; }
	if (totalCards(mat.player) > totalCards(mat.banker) && totalCards(mat.player) <= 21 || totalCards(mat.banker) > 21) {
		game->push(new Award(game, (GameState*)this, totalBet, 4 * totalBet));
	}
	else if (totalCards(mat.banker) == totalCards(mat.player) && totalCards(mat.banker) <= 21 && totalCards(mat.player) <= 21 && !win) {
		game->push(new Award(game, (GameState*)this, totalBet, totalBet));
	}

	timeForWin = true;
}

void BaccaratBlackjack::startRound() {
	if (!animOn)
	{
		win = false;
		handCards();
		//eleccion frame cartas
		player1->frame = mat.player[0];
		banker1->frame = mat.banker[0];
		player2->frame = mat.player[1];
		
		askCards();
	}
}

void BaccaratBlackjack::askCards() {
	int xBut = (int)(Game::WIN_WIDTH * 7.16 / 8), yBut = (int)(Game::WIN_HEIGHT * 4.5 / 7), wBut = Game::WIN_WIDTH / 15, hBut = Game::WIN_WIDTH / 15;
	more = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(TICK));
	addObjects(more);
	addEventListener(more);
	more->connect([this]() { handOneCard(); });
	yBut = (int)(Game::WIN_HEIGHT * 4.5 / 9);
	stand = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(CROSS));
	addObjects(stand);
	addEventListener(stand);
	stand->connect([this]() { bancaAI(); });
}

void BaccaratBlackjack::handOneCard() {
	if (totalCards(mat.player) < 21 && canAsk) {
		rndNum = generateRnd();
		mat.player.push_back(rndNum);
		playerCardVec.push_back(createCard(playerXpos, playerYpos, 0, mat.player[mat.player.size() - 1]));
		playerXpos -= Game::WIN_WIDTH / 30;
		cardsVec.push_back(rndNum);
	}
}

void BaccaratBlackjack::bancaAI() {
	if (!win) {
		canAsk = false;
		banker2->frame = mat.banker[1];
		while (totalCards(mat.banker) < 17) {
			rndNum = generateRnd();
			mat.banker.push_back(rndNum);
			bankerCardVec.push_back(createCard(bankerXpos, bankerYpos, 0, mat.banker[mat.banker.size() - 1]));
			bankerXpos += Game::WIN_WIDTH / 30;
			cardsVec.push_back(rndNum);
		}
	}
}

int BaccaratBlackjack::totalCards(vector<int> askedCards) {
	int t = 0;
	int marker = 0;
	for (int i : askedCards)
	{
		if (i > 10) i = 10;
		if (i == 1) {
			marker++;
			i = 11;
		}
		if (t + i > 21 && marker > 0) { t -= 10; marker--; }
		t += i;
	}
	return t;
}

void BaccaratBlackjack::clearDeck() {
	PlayerEconomy::setBet(0);
	hud->refresh();
	clearBets();
	banker1->frame = 0;
	banker2->frame = 0;
	player1->frame = 0;
	player2->frame = 0;
	Baccarat::clearDeck();
	playerXpos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 30);
	bankerXpos = (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 + Game::WIN_WIDTH / 30);

	for (size_t i = bankerCardVec.size(); i > 0; i--) {
		bankerCardVec.pop_back();
		gameObjects.pop_back();
	}
	for (size_t i = playerCardVec.size(); i > 0; i--) {
		playerCardVec.pop_back();
		gameObjects.pop_back();
	}
	eventHandlers.pop_back();
	eventHandlers.pop_back();
	gameObjects.pop_back();
	gameObjects.pop_back();
}

