#include "Baccarat.h"
#include "Game.h"
#include <random>

Baccarat::Baccarat(Game* game) : GameState(game), texture(game->getTexture(BACMAT)) {
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
}

void Baccarat::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
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
	cout << playerComb << " " << bankerComb << endl;
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