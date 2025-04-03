#include "Baccarat.h"
#include "Game.h"
#include <random>

Baccarat::Baccarat(Game* game) : GameState(game), texture(game->getTexture(BACMAT)), ui(new UIBaccarat(this, game, this)) {
	addEventListener(this);
	addCards();
	//Buttons
	createBaccaratButton(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 + 10, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8, 8, 0);//x8 apuesta
	createBaccaratButton(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 6, 2, 1);//x2 apuesta
	createBaccaratButton(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8, 2, 2);//x2 apuesta
	hud = new HUDBet(this);
}

Card* Baccarat::createCard(int a, int b, int rot, int frame) {//crea cartas
	Card* carta = new Card(this, frame, { a, b }, rot);
	addObjects(carta);
	return carta;
}

void Baccarat::addCards() {//llama al metodo que crea las cartas
	//derch player
	player1 = createCard((int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3), (int)(Game::WIN_HEIGHT / 5.33), 0, 0);
	//banker izq
	banker1 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42), (int)(Game::WIN_HEIGHT / 5.32), 0, 0);
	//izq player
	player2 = createCard((int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70), (int)(Game::WIN_HEIGHT / 5.33), 0, 0);
	//banker dch
	banker2 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20), (int)(Game::WIN_HEIGHT / 5.32), 0, 0);;
	//tercera player
	player3 = createCard((int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81), (int)(Game::WIN_HEIGHT / 5.33), 90, 14);
	//tercera banca
	banker3 = createCard((int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5), (int)(Game::WIN_HEIGHT / 5.32), 270, 14);
}

void Baccarat::handleEvent(const SDL_Event& event) {
}

void Baccarat::render() const {
	texture->render();
	GameState::render();
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
	GameState::update();
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
	//cout << mat.player[0] << " " << mat.player[1] << endl;
	if (mat.player[0] > 9) mat.player[0] = 0;//para q las figuras no tengan valor
	if (mat.player[1] > 9) mat.player[1] = 0;
	if (mat.banker[0] > 9) mat.banker[0] = 0;
	if (mat.banker[1] > 9) mat.banker[1] = 0;
	playerComb = (mat.player[0] + mat.player[1]) % 10;
	bankerComb = (mat.banker[0] + mat.banker[1]) % 10;//cuando pasa de 10 no se cuentan decena
	//cout << playerComb << " " << bankerComb << endl;
	if (playerComb < 6) {
		rndNum = generateRnd();
		mat.player.push_back(rndNum);
		cardsVec.push_back(rndNum);
		player3->frame = rndNum;
		bankThird();
	}
	else if (playerComb == 6 || playerComb == 7) {
		if (bankerComb < 6) {
			rndNum = generateRnd();
			mat.banker.push_back(rndNum);
			cardsVec.push_back(rndNum);
			banker3->frame = rndNum;
		}
	}
}

void Baccarat::bankThird() {//se llama desde handthird si es necesario
	if (bankerComb < 3 || bankerComb == 3 && mat.player.back() % 10 != 8 ||
		mat.player.back() % 10 < 8 && (bankerComb == 4 && mat.player.back() % 10 > 1 ||
			bankerComb == 5 && mat.player.back() % 10 > 3 || bankerComb == 6 && mat.player.back() % 10 > 5)) {
		rndNum = generateRnd();
		mat.banker.push_back(rndNum);
		cardsVec.push_back(rndNum);
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
	clearDeck();//borramos mazo repartido
	playerComb = playerComb % 10;
	bankerComb = bankerComb % 10;

	if (playerComb > bankerComb) {
		playerBet = true;
	}
	else if (playerComb < bankerComb) {
		bankerBet = true;
	}
	else if (playerComb == bankerComb) {
		tieBet = true;
	}
	for (int i = 0; i < bets.size(); i++) {
		if (bets[i].moneyBet > 0) {
			if (bets[i].betType == 0 && tieBet) {
				game->push(new Award(game, (GameState*)this, bets[i].moneyBet, bets[i].moneyBet * bets[i].multiplier));
				hasWon = true;
			}
			else if (bets[i].betType == 1 && bankerBet) {
				game->push(new Award(game, (GameState*)this, bets[i].moneyBet, bets[i].moneyBet * bets[i].multiplier));
				hasWon = true;
			}
			else if (bets[i].betType == 2 && playerBet) {
				game->push(new Award(game, (GameState*)this, bets[i].moneyBet, bets[i].moneyBet * bets[i].multiplier));
				hasWon = true;
			}
		}
	}

	playerBet = false;
	bankerBet = false;
	tieBet = false;
	PlayerEconomy::setBet(0);
	hud->refresh();
	clearBets();
}

//APUESTAS
void Baccarat::newBet(int multiplier, int betType, ButtonBaccarat* btnBaccarat) {
	moneyBet = ui->currentChipValue();
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
}

void Baccarat::repeat()
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

void Baccarat::startRound() {
	hasWon = false;
	player3->frame = 14;//inicializamos invisible
	banker3->frame = 14;
	handCards();
	//eleccion frame cartas
	player1->frame = mat.player[0];
	banker1->frame = mat.banker[0];
	player2->frame = mat.player[1];
	banker2->frame = mat.banker[1];

	handThird();//reparte tercera
	win();
}
