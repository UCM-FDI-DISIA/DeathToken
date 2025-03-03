#include "Baccarat.h"
#include "Game.h"
#include <random>

Baccarat::Baccarat(Game* game) : GameState(game), texture(game->getTexture(BACMAT)), ui(new UIBaccarat(this, game, this)) {
	addEventListener(this);
	handCards();
	//derch player
	int a = Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3, b = Game::WIN_HEIGHT / 5.33;
	player1 = new Cards(this, 0, { a , b });
	addObjects(player1);
	//banker izq
	a = Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42; b = Game::WIN_HEIGHT / 5.32;
	banker1 = new Cards(this, 0, { a, b });
	addObjects(banker1);
	//izq player
	a = Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70; b = Game::WIN_HEIGHT / 5.33;
	player2 = new Cards(this, 0, { a, b });
	addObjects(player2);
	//banker dch
	a = Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20; b = Game::WIN_HEIGHT / 5.32;
	banker2 = new Cards(this, 0, { a, b });
	addObjects(banker2);
	//tercera player
	a = Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81; b = Game::WIN_HEIGHT / 5.33;
	player3 = new Cards(this, 14, { a, b }, 270);
	addObjects(player3);
	//tercera banca
	a = Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5, b = Game::WIN_HEIGHT / 5.32;
	banker3 = new Cards(this, 14, { a, b }, 90);
	addObjects(banker3);
	clearDeck();

	//Buttons
	createMarbleButton(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 2, Game::WIN_WIDTH / 5, Game::WIN_HEIGHT / 8, 8);//x8 apuesta
	//a = Game::WIN_WIDTH / 2, b = Game::WIN_HEIGHT /2;
	//banker3 = new Cards(this, 10, { a, b });
	//addObjects(banker3);
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
	random_device rd;  // Semilla basada en hardware (si está disponible)
	mt19937 gen(rd()); // Mersenne Twister como generador de números aleatorios
	uniform_int_distribution<> distrib(1, 13);

	int num = distrib(gen);
	int i = 0;
	int cont = 0;

	// ya no os quiero (cleon)
	while (i < cardsVec.size() && cardsVec.size() > 4) {
		if (cardsVec[i] == num) {
			cont++;
			if (cont == 4) {
				num = distrib(gen);
				cont = 0;
				i = 0;
			}
		}
		i++;
	}

	return num;
}
//APUESTAS
void Baccarat::newBet(int multiplier, int moneyBet, ButtonBaccarat* btnBaccarat) {
	moneyBet = btnBaccarat->getBet();

	// así es más chuli (cleon)
	bets[clave++] = { multiplier, moneyBet };
	//clave++;
}

void
Baccarat::createMarbleButton(int x, int y, int width, int height, int type) {

	int multiplier = 0;

	// cleon cree que "type" sobra
	// cleon cree que el copypaste es el mal
	if (type == 1) {
		multiplier = 2;
	}
	else if (type == 2) {
		multiplier = 5;

	}
	else if (type == 3) {
		multiplier = 20;

	}
	else if (type == 4) {
		multiplier = 5;
	}
	ButtonBaccarat* btnBaccarat = new ButtonBaccarat(this, game, ui, x, y, width, height, type);
	bacButtons.push_back(btnBaccarat);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarat->connect([this, multiplier, btnBaccarat]() { newBet(multiplier, moneyBet, btnBaccarat); });
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
	for (auto i : bacButtons)
	{
		i->repeat();
	}
}

void Baccarat::startRound() {
	player3->frame = 14;//inicializamos invisible
	banker3->frame = 14;
	handCards();
	//eleccion frame cartas
	player1->frame = mat.player[0];
	banker1->frame = mat.banker[0];
	player2->frame = mat.player[1];
	banker2->frame = mat.banker[1];

	handThird();//reparte tercera

	clearDeck();//borramos mazo repartido
}
