#include "BaccaratFlip.h"

BaccaratFlip::BaccaratFlip(Game* game) : Baccarat(game), text(game->getTexture(FLIPCARD)) {
	addCards();
	cardButton();
}

//añade las tres cartas extra
void BaccaratFlip::addCards()
{
	Baccarat::addCards();
	extra1 = createCard(Game::WIN_WIDTH / 2 - 200, Game::WIN_HEIGHT / 3, 0, 14); // frame 14 = invisible
	extra2 = createCard(Game::WIN_WIDTH / 2 - 50, Game::WIN_HEIGHT / 3, 0, 14);
	extra3 = createCard(Game::WIN_WIDTH / 2 + 100, Game::WIN_HEIGHT / 3, 0, 14);
}
//crea las tres cartas extra
void BaccaratFlip::handleExtraCards()
{
	// Generar 3 cartas aleatorias
	extraVals.clear();
	for (int i = 0; i < 3; ++i) {
		int val = generateRnd();
		extraVals.push_back(val);
	}
}

void BaccaratFlip::startRound()
{
	active = true;//ACORDARME PONER EN FALSE EN EL CLEAR DECK
	handleExtraCards();
	extra1->frame = 0;
	extra2->frame = 0;
	extra3->frame = 0;
	player3->frame = 14;//inicializamos invisible
	banker3->frame = 14;
	handCards();
	//eleccion frame cartas
	player1->frame = mat.player[0];
	banker1->frame = mat.banker[0];
	player2->frame = mat.player[1];
	banker2->frame = mat.banker[1];

	handThird();//reparte tercera
}
//crea los botonees para llas cartas
void BaccaratFlip::cardButton()
{

	carta1 = new Button(this, Game::WIN_WIDTH / 2 - 200, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta1);
	addEventListener(carta1);
	carta1->connect([this] {if (active && flips < 2) { extra1->frame = extraVals[0]; flips++; }});

	carta2 = new Button(this, Game::WIN_WIDTH / 2 - 50, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta2);
	addEventListener(carta2);
	carta2->connect([this] {if (active && flips < 2) { extra2->frame = extraVals[1]; flips++; }});

	carta3 = new Button(this, Game::WIN_WIDTH / 2 + 100, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta3);
	addEventListener(carta3);
	carta3->connect([this] {if (active && flips < 2) { extra3->frame = extraVals[2];flips++; }});
	//Resetear flips en clear deck!!!!!!!!!!!!!!
}

void BaccaratFlip::render() const {
	Baccarat::render();
	GameState::render();
}

void
BaccaratFlip::createBaccaratBetButton(int x, int y, int width, int height) {
	ButtonBaccarat* btnBaccarat = new ButtonBaccarat(this, game, ui, x, y, width, height);
	bacButtons.push_back(btnBaccarat);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarat->connect([this, x, btnBaccarat]() { newBet(0, moneyBet, btnBaccarat); });
}
