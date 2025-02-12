#include "MainMenu.h"
#include "Game.h"
#include "playState.h"

MainMenu::MainMenu(Game* g) : GameState(g)
{
	portada = game->getTexture(PORTADA);

	level1 = new Button(this, 200, 260, 175, 25, game->getTexture(NIVEL1), game->getTexture(MUSHROOM));
	addObjects(level1);
	addEventListener(level1);
	level1->connect([this]() { lvl1(); });

	level2 = new Button(this, 200, 300, 175, 25, game->getTexture(NIVEL2), game->getTexture(MUSHROOM));
	addObjects(level2);
	addEventListener(level2);
	level2->connect([this]() { lvl2(); });

	salir = new Button(this, 225, 340, 125, 25, game->getTexture(SALIR), game->getTexture(MUSHROOM));
	addObjects(salir);
	addEventListener(salir);
	salir->connect([this]() { exit(); });
}
void MainMenu::render() const {
	SDL_Rect rect(0, 0, Game::TILE_SIDE * Game::WIN_WIDTH, Game::TILE_SIDE * Game::WIN_HEIGHT);
	portada->render(rect);
	GameState::render();
}
void MainMenu::lvl1() const {
	game->replace(new PlayState(game, 0));
}
void MainMenu::lvl2() const {
	game->replace(new PlayState(game, 1));
}
void MainMenu::exit() const {
	game->stop();
}