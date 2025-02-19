#include "Menu.h"
#include "Game.h"
#include "Player.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	baccarat = new Button(this, 405, 195, 125, 125, game->getTexture(BACCARATBUT));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	slots = new Button(this, 1365, 195, 125, 125, game->getTexture(SLOTSBUT));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	marbles = new Button(this, 405, 735, 125, 125, game->getTexture(CANICASBUT));
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() { cambiaJuego(new Marbles(getGame())); });

	peleas = new Button(this, 1365, 735, 125, 125, game->getTexture(PELEASBUT));
	addObjects(peleas);
	addEventListener(peleas);
	peleas->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	if (ghost == nullptr) {
		ghost = new Player(this, { 500, 500 }, game->getTexture(MARIO));
		addObjects(ghost);
		addEventListener(ghost);
	}
}

void Menu::cambiaJuego(GameState* juego) {
	game->push(juego);
}

void Menu::render() const {
	texture->render();
	GameState::render();
}
