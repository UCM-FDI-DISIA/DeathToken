#include "BaccaratFlip.h"

BaccaratFlip::BaccaratFlip(Game* game) : Baccarat(game), text(game->getTexture(BACCARATBUT)) {
	addCards();

}

//añade las tres cartas extra
void BaccaratFlip::addCards()
{
	Baccarat::addCards();
	extra1 = createCard(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14); // frame 14 = invisible
	extra2 = createCard(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14);
	extra3 = createCard(Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14);//a
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
	cardButton();
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
	clearDeck();
}
//crea los botonees para llas cartas
void BaccaratFlip::cardButton()
{
	carta1 = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta1);
	addEventListener(carta1);
	carta1->connect([this] {if (active && flips < 2) { extra1->frame = extraVals[0]; flips++; deckButton(); } chosen = 0; });

	carta2 = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta2);
	addEventListener(carta2);
	carta2->connect([this] {if (active && flips < 2) { extra2->frame = extraVals[1]; flips++; deckButton(); }chosen = 1;});

	carta3 = new Button(this, Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
	addObjects(carta3);
	addEventListener(carta3);
	carta3->connect([this] {if (active && flips < 2) { extra3->frame = extraVals[2];flips++; deckButton(); } chosen = 2;});
	//Resetear flips en clear deck!!!!!!!!!!!!!!

}

void BaccaratFlip::deckButton()
{
	if (flips == 2) {
		player = new Button(this, Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 90, Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20 * 2.72, Game::WIN_HEIGHT / 8, text);
		addObjects(player);
		addEventListener(player);
		player->connect([this] {
			mat.player.push_back(extraVals[chosen]);
			/*int xPos = 0;
			if (flips == 2) {
				xPos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3);
			}
			else if (flips == 1) {
				xPos = (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70);
			}*/
			int a = flips;
			if (chosen == 0) {
				extra1->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
				deleteSpecificEH(carta1);
				deleteSpecificGO(carta1);
				chosen = 1;
				
			}
			else if (chosen == 1) {
				extra2->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
				deleteSpecificEH(carta2);
				deleteSpecificGO(carta2);
				chosen = 2;
				
			}
			else if (chosen == 2) {
				extra3->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 20), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
				deleteSpecificEH(carta3);
				deleteSpecificGO(carta3);
				chosen = 0;
			}

			});

		banker = new Button(this, Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42, Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20 * 2.72, Game::WIN_HEIGHT / 8, text);
		addObjects(banker);
		addEventListener(banker);
		banker->connect([this] {
			mat.banker.push_back(extraVals[chosen]);
			if (chosen == 0) {
				extra1->setPos({ (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
				deleteSpecificEH(carta1);
				deleteSpecificGO(carta1);
				//chosen = 1;
			}
			});
	}
}

void BaccaratFlip::clearDeck()
{
	Baccarat::clearDeck();
	/*flips = 0;
	active = false;*/
}

void BaccaratFlip::render() const {
	Baccarat::render();
}

void BaccaratFlip::update()
{
	Baccarat::update();

}

