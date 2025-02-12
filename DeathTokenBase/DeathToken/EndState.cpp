#include "Game.h"
#include "EndState.h"
#include "playState.h"
#include "MainMenu.h"

EndState::EndState(Game* g, bool win) : GameState(g)
{
	if (win) {
		box = { 163,70,250,25 };
		result = game->getTexture(WIN);
	}
	else {
		box = { 175,70,225,25 };
		result = game->getTexture(LOST);
	}

	menu = new Button(this, 113, 150, 350, 25, game->getTexture(MENU), game->getTexture(MUSHROOM));
	addObjects(menu);
	addEventListener(menu);
	menu->connect([this]() { backToMenu(); });

	salir = new Button(this, 225, 250, 125, 25, game->getTexture(SALIR), game->getTexture(MUSHROOM));
	addObjects(salir);
	addEventListener(salir);
	salir->connect([this]() { exit(); });
}
void EndState::render() const {
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	result->render(box);
	GameState::render();
}
void EndState::backToMenu() const {
	game->replace(new MainMenu(game));
}
void EndState::exit() const {
	game->stop();
}