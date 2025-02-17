#include "Menu.h"
#include "Game.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	baccarat = new Button(this, 405, 195, 125, 125, game->getTexture(BACCARATBUT), game->getTexture(MARIO));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	slots = new Button(this, 1365, 195, 125, 125, game->getTexture(SLOTSBUT), game->getTexture(MARIO));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	canicas = new Button(this, 405, 735, 125, 125, game->getTexture(CANICASBUT), game->getTexture(MARIO));
	addObjects(canicas);
	addEventListener(canicas);
	canicas->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	peleas = new Button(this, 1365, 735, 125, 125, game->getTexture(PELEASBUT), game->getTexture(MARIO));
	addObjects(peleas);
	addEventListener(peleas);
	peleas->connect([this]() { cambiaJuego(new Baccarat(getGame())); });
}

void Menu::cambiaJuego(GameState* juego) {
	game->push(juego);
}

void Menu::render() const {
	texture->render();
	GameState::render();
}
