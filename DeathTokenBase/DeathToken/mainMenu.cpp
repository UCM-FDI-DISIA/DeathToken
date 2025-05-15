#include "MainMenu.h"
#include "EscenaTutorial.h"
#include "Menu.h"
#include "Game.h"


MainMenu::MainMenu(Game* g) : GameState(g)
{
	back = game->getTexture(BACKGROUND);

	int _y = (int)(Game::WIN_HEIGHT * (500 / 1080.0f));
	int _w = (int)(Game::WIN_WIDTH * (400 / 1920.0f));
	int _h = (int)(Game::WIN_HEIGHT * (200 / 1080.0f));
	begin = new Button(this, Game::WIN_WIDTH / 2 - _w / 2, _y, _w, _h, game->getTexture(BTNSLOT));
	addObjects(begin);
	addEventListener(begin);
	begin->connect([this]() {
		if (game->getTutorial()) {
			game->replace(new Menu(game));
			//game->replace(new EscenaTutorial(game));
			game->setTutorial(false);
		}
		else {
			game->replace(new Menu(game));
		}
	});

	_y = (int)(Game::WIN_HEIGHT * (750 / 1080.0f));
	salir = new Button(this, Game::WIN_WIDTH / 2 - _w / 2, _y, _w, _h, game->getTexture(BTNSLOTCLICK));
	addObjects(salir);
	addEventListener(salir);
	//Aqui a lo mejor hay que incluir tb lo de firebase IVAN
	salir->connect([this]() { game->stop();});
}
void MainMenu::render() const {
	SDL_Rect rect(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
	back->render(rect);
	GameState::render();
}