#include "EscenaTutorial.h"
#include "Menu.h"
#include "button.h"
#include "texture.h"
#include "game.h"
#include "sdlutils.h"

EscenaTutorial::EscenaTutorial(Game* g) : GameState(g),_g(g), picked(false), startGame(false), resultado(false), index(-1), fases(0), bet(0) {
	float x = Game::WIN_WIDTH * (600.0f / 1920.0f);
	float y = Game::WIN_HEIGHT * (680.0f / 1080.0f);
	float cartaW = Game::WIN_WIDTH * (110.0f / 1920.0f);
	float cartaH = Game::WIN_HEIGHT * (210.0f / 1920.0f);
	//Botones juego
	Button* piedra = new Button(this, (int)(x), (int)(y),(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	piedra->connect([this] {
		if (!picked && startGame) {
			setIndex(0);
			picked = true;
		}
		});
	addObjects(piedra);
	addEventListener(piedra);

	x = Game::WIN_WIDTH * (900.0f / 1920.0f);
	Button* papel = new Button(this, (int)x, (int)y,(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	papel->connect([this] {
		if (!picked && startGame) {
			setIndex(1);
			picked = true;
		}
		});
	addObjects(papel);
	addEventListener(papel);

	x = Game::WIN_WIDTH * (1200.0f / 1920.0f);
	Button* tijera = new Button(this, (int)x, (int)y,(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	tijera->connect([this] {
		if (!picked && startGame) {
			setIndex(2);
			picked = true;
		}
		});
	addObjects(tijera);
	addEventListener(tijera);
	//Interfaz

	_dialog = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog);
	_dialog->setX(Game::WIN_WIDTH / 3);
	_dialog->setY(3 * Game::WIN_HEIGHT / 4);
	_dialog->setWidth(Game::WIN_WIDTH / 3);

	eco = new PlayerEconomy();
	eco->EconomyInitialize();
	_ui = new UIEscenaTutorial(this, g, this);
	_hud = new HUDBet(this);

	float w = Game::WIN_WIDTH * (200.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (200.0f / 1080.0f);
	float _x = (350.0f / 1920.0f) * Game::WIN_WIDTH;
	float _y = (400.0f / 1080.0f) * Game::WIN_HEIGHT;
	_bet = new ButtonTutorial(this, game, _ui, (int)_x, (int)_y, (int)w, (int)h, game->getTexture(BETSLOTS), this);
	addObjects(_bet);
	addEventListener(_bet);


}
EscenaTutorial::~EscenaTutorial() {
	delete eco;
}
void
EscenaTutorial::render() const {
	GameState::render();

	SDL_Rect flechaUP;
	SDL_Rect flechaDown;

	flechaUP.w = Game::WIN_WIDTH * (140 / 1980.0f);
	flechaUP.h = Game::WIN_HEIGHT * (140 / 1080.0f);
	
	flechaDown.w = Game::WIN_WIDTH * (140 / 1980.0f);
	flechaDown.h = Game::WIN_HEIGHT * (140 / 1080.0f);

	if (fases == 1) {
		flechaDown.x = (340.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (785.0f / 1080.0f) * Game::WIN_HEIGHT;
		flechaUP.x = (420.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (500.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 2) {
		flechaDown.x = (1720.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (800.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 3) {
		flechaDown.x = (600.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (630.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 4) {
		flechaUP.x = (1500.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (200.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);
	}

	//_dialog->render();

	SDL_Rect player;
	player.x = (720.0f / 1980.0f) * Game::WIN_WIDTH;
	player.y = (400.0f / 1080.0f) * Game::WIN_HEIGHT;
	player.h = (210.0f / 1080.0f) * Game::WIN_HEIGHT;
	player.w = (210.0f / 1920.0f) * Game::WIN_WIDTH;

	SDL_Rect enemy;
	enemy.x = Game::WIN_WIDTH * (1020.0f / 1980.0f);
	enemy.y = Game::WIN_HEIGHT * (400.0f / 1080.0f);
	enemy.h = Game::WIN_HEIGHT * (210.0f / 1080.0f);
	enemy.w = Game::WIN_WIDTH * (210.0f / 1920.0f);
	if (!picked) {
		game->getTexture(SLOTSBUT)->render(player);
		game->getTexture(SLOTSBUT)->render(enemy);
		
	}
	else {
		game->getTexture(ICONOPPT)->renderFrame(player, 0, index);
		if (resultado && picked) {
			if (index == 0) {
				game->getTexture(ICONOPPT)->renderFrame(enemy, 0, 2);
			}
			else {
				game->getTexture(ICONOPPT)->renderFrame(enemy, 0, index - 1);
			}

		}
	}


}
void EscenaTutorial::update() {
	GameState::update();
	/*_dialog->resetDialogStateFlag();
	_dialog->showMessage("probando,1,2,3");*/
	/*switch (fases) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		game.pushState(new Menu(_g));
		break;
	}
	if (startGame) {
		if (picked) {
			float aux = SDLUtils::getDeltaTime();
			counter += aux;
			if (counter >= 2) {
				counter = 0;
				resultado = true;
				game->push(new Award(game, (GameState*)this, bet, bet * 2));
				clear();
				startGame = !startGame;
			}
		}
	}*/

}