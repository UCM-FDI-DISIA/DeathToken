#include "baccarat.h"
#include "game.h"
#include <random>

Baccarat::Baccarat(Game* game, bool bJ) : GameState(game), texture(game->getTexture(BACMAT)), smoke(game->getTexture(SMOKE)), counter(game->getTexture(COUNTER)), counterB(game->getTexture(COUNTER)), ui(new UIBaccarat(this, game, this)) {
	addEventListener(this);
	addCards();
	//Buttons
	int w = (int)(Game::WIN_WIDTH * (450.0f / 1920.0f));
	int h = (int)(Game::WIN_WIDTH * (135.0f / 1920.0f));
	int posT = (int)(Game::WIN_WIDTH * (370.0f / 1920.0f));
	int posP = (int)(Game::WIN_WIDTH * (740.0f / 1920.0f));
	int posB = (int)(Game::WIN_WIDTH * (555.0f / 1920.0f));
	if (!bJ)
	{
		createBaccaratButton(Game::WIN_WIDTH / 2 - w / 2, posT, w, h, 8, 0);//x8 apuesta
		createBaccaratButton(Game::WIN_WIDTH / 2 - w / 2, posB, w, h, 2, 1);//x2 apuesta
		createBaccaratButton(Game::WIN_WIDTH / 2 - w / 2, posP, w, h, 2, 2);//x2 apuesta
	}
	hud = new HUDBet(this, false);
}

Card* Baccarat::createCard(int a, int b, int rot, int frame) {//crea cartas
	Card* carta = new Card(this, frame, { a, b }, rot);
	addObjects(carta);
	return carta;
}

void Baccarat::addCards() {//llama al metodo que crea las cartas
	//tercera player
	player3 = createCard((int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81 + Game::WIN_HEIGHT / 8), (int)(Game::WIN_HEIGHT / 5.33), 90, 14);
	//tercera banca
	banker3 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5 - Game::WIN_HEIGHT / 8), (int)(Game::WIN_HEIGHT / 5.32), 270, 14);
	//derch player
	player1 = createCard((int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3), (int)(Game::WIN_HEIGHT / 5.33), 0, 0);
	//banker izq
	banker1 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42), (int)(Game::WIN_HEIGHT / 5.32), 0, 0);
	//izq player
	player2 = createCard((int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70), (int)(Game::WIN_HEIGHT / 5.33), 0, 0);
	//banker dch
	banker2 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20), (int)(Game::WIN_HEIGHT / 5.32), 0, 0);
}


void Baccarat::handleEvent(const SDL_Event& event) {
}

void Baccarat::render() const {
	texture->render();
	GameState::render();
	if (cardAnim) {
		smoke->renderFrame(sm, 0, frame);
	}
	counter->renderFrame(ct, 0, ctFrame);
	counterB->renderFrame(ctB, 0, ctFrameB);
}

void Baccarat::clearDeck() {
	while (0 < cardsVec.size())
		cardsVec.pop_back();
	while (0 < mat.player.size())
		mat.player.pop_back();
	while (0 < mat.banker.size())
		mat.banker.pop_back();
}

void Baccarat::update() {//para que las cartas se muevan enun futuro
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
		win();
		goForWin = false;
	}
	if (timeForWin) {
		float dt = SDLUtils::getDeltaTime();
		tiempo += dt;
		if (tiempo > 3)
		{
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
			clearDeck();//borramos mazo repartido
		}
	}
}

void Baccarat::handCards() {
	for (int i = 0; i < 2; i++) {//reparte las 4 primeras cartas
		rndNum = generateRnd();
		mat.player.push_back(rndNum);
		cardsVec.push_back(rndNum);
		rndNum = generateRnd();
		mat.banker.push_back(rndNum);
		cardsVec.push_back(rndNum);
	}
}

void Baccarat::handThird() {//reparte la tercera segun las normas
	if (mat.player[0] > 9) mat.player[0] = 0;//para q las figuras no tengan valor
	if (mat.player[1] > 9) mat.player[1] = 0;
	if (mat.banker[0] > 9) mat.banker[0] = 0;
	if (mat.banker[1] > 9) mat.banker[1] = 0;
	playerComb = (mat.player[0] + mat.player[1]) % 10;
	bankerComb = (mat.banker[0] + mat.banker[1]) % 10;//cuando pasa de 10 no se cuentan decena
	if (playerComb < 6) {
		rndNum = generateRnd();
		mat.player.push_back(rndNum);
		cardsVec.push_back(rndNum);
		thirdPlayerMove = true;
		player3->frame = rndNum;
		bankThird();
	}
	else if (playerComb == 6 && bankerComb < 6 || playerComb == 7 && bankerComb < 6) {
		rndNum = generateRnd();
		mat.banker.push_back(rndNum);
		cardsVec.push_back(rndNum);
		thirdBankerMove = true;
		banker3->frame = rndNum;
	}
	else {
		goForWin = true;
	}
}

void Baccarat::bankThird() {//se llama desde handthird si es necesario
	if (bankerComb < 3 || bankerComb == 3 && mat.player.back() % 10 != 8 ||
		mat.player.back() % 10 < 8 && (bankerComb == 4 && mat.player.back() % 10 > 1 ||
			bankerComb == 5 && mat.player.back() % 10 > 3 || bankerComb == 6 && mat.player.back() % 10 > 5)) {
		rndNum = generateRnd();
		mat.banker.push_back(rndNum);
		cardsVec.push_back(rndNum);
		thirdBankerMove = true;
		banker3->frame = rndNum;
	}
}

int Baccarat::generateRnd() {
	uniform_int_distribution<> distrib(1, 13);

	int num = distrib(game->getGen());
	int i = 0;
	int cont = 0;

	// ya no os quiero (cleon)
	while (i < cardsVec.size() && cardsVec.size() > 4) {
		if (cardsVec[i] == num) {
			cont++;
			if (cont == 4) {
				num = distrib(game->getGen());
				cont = 0;
				i = 0;
			}
		}
		i++;
	}

	return num;
}

void Baccarat::win() {
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
		game->push(new Award(game, (GameState*)this, totalBet, totalBet * multi));
		hasWon = true;
	}
	PlayerEconomy::setBet(0);
	hud->refresh();
	clearBets();
	timeForWin = true;
}

//APUESTAS
void Baccarat::newBet(int multiplier, int betType, ButtonBaccarat* btnBaccarat) {
	moneyBet = ui->currentChipValue();
	ui->setOnBet(true);
	// así es más chuli (cleon)
	bets[clave++] = { multiplier, moneyBet, betType };
	//clave++;
}

void
Baccarat::createBaccaratButton(int x, int y, int width, int height, int multiplier, int betType) {
	ButtonBaccarat* btnBaccarat = new ButtonBaccarat(this, game, ui, x, y, width, height);
	bacButtons.push_back(btnBaccarat);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarat->connect([this, multiplier, betType, btnBaccarat]() { newBet(multiplier, betType, btnBaccarat); });
}

void Baccarat::clearBets() {
	betsHistory = bets;
	bets.clear();
	for (auto i : bacButtons)
	{
		i->clear();
	}
	ui->setOnBet(false);
}

void Baccarat::repeat()
{
	if (mat.player.size() == 0 && mat.player.size() == 0)
	{
		bets = betsHistory;
		int currentBet = 0;
		for (int i = 0; i < bets.size(); i++) {
			currentBet += bets[i].moneyBet;
		}
		for (auto i : bacButtons)
		{
			i->repeat();
		}
		HUDManager::applyBet(currentBet);
	}
}

void Baccarat::startRound() {

	if (mat.player.size() == 0 && mat.player.size() == 0 && ui->getOnBet())
	{
		hasWon = false;
		player1->frame = 0;//inicializamos boca abajo
		banker1->frame = 0;
		player2->frame = 0;
		banker2->frame = 0;
		player3->frame = 14;//inicializamos invisible
		banker3->frame = 14;
		player3->setPos(Vector2D((int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81 + Game::WIN_HEIGHT / 8), (int)(Game::WIN_HEIGHT / 5.33)));
		banker3->setPos(Vector2D((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5 - Game::WIN_HEIGHT / 8), (int)(Game::WIN_HEIGHT / 5.32)));
		handCards();
		cardAnim = true;
		animTime = SDL_GetTicks();
	}

}
