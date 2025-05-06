#include "pauseState.h"
#include "game.h"
#include "menu.h"

PauseState::PauseState(Game* game, GameState* other) : GameState(game), anterior(other), texture(game->getTexture(TUTORIAL1))
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
		game->stop(); // Pop de pausa y el juego actual
		game->pushState(new Menu(game));
		game->setPause(false);//si la pausa esta en true no se puede abrir otra
		});
}

PauseState::~PauseState()
{
}

void PauseState::render() const
{
	anterior->render();
	SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
	SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
	SDL_RenderFillRect(game->getRenderer(), &black);

	texture->render();
	GameState::render();
}

//NO SE COMO HACER QUE NO FALLE CUANDO HACES PAUSE EN UN JUEGO Y VUELVES AL MENU PORQUE FALLA EL POPGAME DE LA UI