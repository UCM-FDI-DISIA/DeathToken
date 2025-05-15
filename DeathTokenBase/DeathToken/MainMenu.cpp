#include "FirebaseUtils.h"
#include "MainMenu.h"
#include "EscenaTutorial.h"
#include "Menu.h"
#include "Game.h"
#include "sdlUtils.h"


MainMenu::MainMenu(Game* g) : GameState(g)
{
	back = game->getTexture(BACKGROUND);

	int _y = (int)(Game::WIN_HEIGHT * (600 / 1080.0f));
	int _w = (int)(Game::WIN_WIDTH * (400 / 1920.0f));
	int _h = (int)(Game::WIN_HEIGHT * (200 / 1080.0f));

	
	inputNombre = new InputBox(g->getRenderer(), g->getTypo(MENUT), (Game::WIN_WIDTH / 2)-525 ,
		_y-(int)(Game::WIN_HEIGHT * (250 / 1080.0f)),true,false,(1050), 100);
	inputNombre->setMaxLength(8);
	inputNombre->setActive(true);
	inputNombre->showMessage("ESCRIBE TU NOMBRE");
	addEventListener(inputNombre);


	begin = new Button(this, Game::WIN_WIDTH / 2 - _w / 2, _y, _w, _h, game->getTexture(BTNSLOT));
	addObjects(begin);
	addEventListener(begin);
	begin->connect([this]() {
		
		string nombre = inputNombre->getUserInput();
		FirebaseUtils::RegisterUser(nombre);
		if (game->getTutorial()) {
			game->replace(new Menu(game));
			game->setTutorial(false);
		}
		else {
			game->replace(new Menu(game));
		}
	});

	_y = (int)(Game::WIN_HEIGHT * (800 / 1080.0f));
	salir = new Button(this, Game::WIN_WIDTH / 2 - _w / 2, _y, _w, _h, game->getTexture(BTNSLOTCLICK));
	addObjects(salir);
	addEventListener(salir);
	salir->connect([this]() {
		game->stop();
		FirebaseUtils::SaveState(PlayerEconomy::getBlueSouls(), PlayerEconomy::getRedSouls(), PlayerEconomy::getInsanity());
		});


}
void MainMenu::render() const {
	SDL_Rect rect(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
	back->render(rect);
	GameState::render();
	inputNombre->render();

}

