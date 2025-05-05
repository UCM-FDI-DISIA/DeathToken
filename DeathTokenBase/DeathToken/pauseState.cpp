#include "pauseState.h"
#include "game.h"
#include "menu.h"

PauseState::PauseState(Game* game) : GameState(game), texture(game->getTexture(TUTORIAL1))
{
	
	back = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 12, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8,
		Game::WIN_WIDTH / 6, Game::WIN_HEIGHT / 4, game->getTexture(BACCARATBUT));
	addObjects(back);
	addEventListener(back);
	back->connect([this, game]() {
		game->pop();
		game->setPause(false);//si la pausa esta en true no se puede abrir otra
		});
	
	menu = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 12, (Game::WIN_HEIGHT / 3)*2 - Game::WIN_HEIGHT / 8,
		Game::WIN_WIDTH / 6, Game::WIN_HEIGHT / 4, game->getTexture(BACCARATBUT));
	addObjects(menu);
	addEventListener(menu);
	menu->connect([this, game]() {
		game->push(new Menu(game));
		game->setPause(false);//si la pausa esta en true no se puede abrir otra
		});
}

PauseState::~PauseState()
{
}

void PauseState::render() const
{
	texture->render();
	GameState::render();
}

//NO SE COMO HACER QUE NO FALLE CUANDO HACES PAUSE EN UN JUEGO Y VUELVES AL MENU PORQUE FALLA EL POPGAME DE LA UI