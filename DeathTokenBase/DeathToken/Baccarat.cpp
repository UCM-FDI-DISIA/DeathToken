#include "Baccarat.h"
#include "Game.h"
#include <random>

Baccarat::Baccarat(Game* game) : GameState(game), texture(game->getTexture(BACMAT)) {
	addEventListener(this);
	repartir();
	//derch player
	int a = Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 21.2, b = Game::WIN_HEIGHT / 5.34;
	player1 = new Cards(this, 0, { a, b });
	addObjects(player1);
	//banker izq
	a = Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42; b = Game::WIN_HEIGHT / 5.32;
	player2 = new Cards(this, 0, { a, b });
	addObjects(player2);
	//izq player
	a = Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.35; b = Game::WIN_HEIGHT / 5.34;
	banker1 = new Cards(this, 0, { a , b });
	addObjects(banker1);
	//banker dch
	a = Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20; b = Game::WIN_HEIGHT / 5.32;
	banker2 = new Cards(this, 0, { a, b });
	addObjects(banker2);

	clearDeck();
}

void Baccarat::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
		repartir();

		player1->frame = tap.jugador[0];
		banker1->frame = tap.banca[0];
		player2->frame = tap.jugador[1];
		banker2->frame = tap.banca[1];

		clearDeck();
	}
}

void Baccarat::render() const {
	texture->render();
	GameState::render();
}

void Baccarat::clearDeck() {
	while (0 < cartas.size())
		cartas.pop_back();
	while (0 < tap.jugador.size())
		tap.jugador.pop_back();
	while (0 < tap.banca.size())
		tap.banca.pop_back();
}

void Baccarat::update() {

}

void Baccarat::repartir() {
	for (int i = 0; i < 2; i++) {
		numAleatorio = generaAleatorio();
		tap.jugador.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
		numAleatorio = generaAleatorio();
		tap.banca.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
	}
}

void Baccarat::repartirTercera() {
	sumaJug = (tap.jugador[0] + tap.jugador[1]) % 10;
	sumaBanca = (tap.banca[0] + tap.banca[1]) % 10;
	if (sumaJug < 6) {
		numAleatorio = generaAleatorio();
		tap.jugador.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
		terceraBanca();
	}
	else if (sumaJug == 6 || sumaJug == 7) {
		if (sumaBanca < 6) {
			numAleatorio = generaAleatorio();
			tap.banca.push_back(numAleatorio);
			cartas.push_back(numAleatorio);
		}
	}
}

void Baccarat::terceraBanca() {
	if (sumaBanca < 3 || sumaBanca == 3 && tap.jugador.back() % 10 != 8 ||
		tap.jugador.back() % 10 < 8 && (sumaBanca == 4 && tap.jugador.back() % 10 > 1 ||
			sumaBanca == 5 && tap.jugador.back() % 10 > 3 || sumaBanca == 6 && tap.jugador.back() % 10 > 5)) {

		numAleatorio = generaAleatorio();
		tap.banca.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
	}
}

int Baccarat::generaAleatorio() {
	random_device rd;  // Semilla basada en hardware (si está disponible)
	mt19937 gen(rd()); // Mersenne Twister como generador de números aleatorios
	uniform_int_distribution<> distrib(1, 13);

	int num = distrib(gen);
	int i = 0;
	int cont = 0;

	while (i < cartas.size() && cartas.size() > 4) {
		if (cartas[i] == num) {
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