#include "Game.h"
#include "PauseState.h"
#include "MainMenu.h"

PauseState::PauseState(Game* g) : GameState(g)
{
	//las texturas pone mario en todo pero no es asi
	cont = new Button(this, 175, 150, 225, 25, game->getTexture(MARIO));
	addObjects(cont);
	addEventListener(cont);
	cont->connect([this]() { continuar(); });

	menu = new Button(this, 113, 250, 350, 25, game->getTexture(MARIO));
	addObjects(menu);
	addEventListener(menu);
	menu->connect([this]() { backToMenu(); });

	salir = new Button(this, 225, 350, 125, 25, game->getTexture(MARIO));
	addObjects(salir);
	addEventListener(salir);
	salir->connect([this]() { exit(); });
}
void PauseState::render() const {
	SDL_Rect black(0, 0, Game::WIN_WIDTH * Game::TILE_SIDE, Game::WIN_HEIGHT * Game::TILE_SIDE);
	SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
	SDL_RenderFillRect(game->getRenderer(), &black);
		GameState::render();
}
void PauseState::continuar() const {
	game->pop();
}
void PauseState::backToMenu() const {
	game->pop();
	game->replace(new MainMenu(game));
}
void PauseState::exit() const {
	game->stop();
}