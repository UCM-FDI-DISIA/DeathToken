#include "firebaseUtils.h"
#include "pauseState.h"
#include "game.h"
#include "menu.h"
#include "ranking.h"
#include "mainMenu.h"
#include "playerEconomy.h"

PauseState::PauseState(Game* game, GameState* other) : GameState(game), anterior(other), texture(game->getTexture(PAUSE))
{
	
	back = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 12, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 14,
		Game::WIN_WIDTH / 6, Game::WIN_HEIGHT / 7, game->getTexture(BACK));
	addObjects(back);
	addEventListener(back);
	back->connect([this, game]() {
		game->pop();
		game->setPause(false);//si la pausa esta en true no se puede abrir otra
		});
	
	menu = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 12, (Game::WIN_HEIGHT / 3)*2 - Game::WIN_HEIGHT / 14,
		Game::WIN_WIDTH / 6, Game::WIN_HEIGHT / 7, game->getTexture(MENU));
	addObjects(menu);
	addEventListener(menu);
	menu->connect([this, game]() {
		game->stop(); // Pop de pausa y el juego actual
		FirebaseUtils::SaveState(PlayerEconomy::getBlueSouls(), PlayerEconomy::getRedSouls(), PlayerEconomy::getInsanity(), FirebaseUtils::tutorial);
		game->pushState(new MainMenu(game));
		game->setPause(false);//si la pausa esta en true no se puede abrir otra
		});
	
	rank = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 12, (Game::WIN_HEIGHT / 3)+ (Game::WIN_HEIGHT / 6) - Game::WIN_HEIGHT / 14,
		Game::WIN_WIDTH / 6, Game::WIN_HEIGHT / 7, game->getTexture(RANK));
	addObjects(rank);
	addEventListener(rank);
	rank->connect([this, game]() {
		game->pushState(new Ranking(game, anterior));
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
