#include "EscenaTutorial.h"
#include "Menu.h"
#include "button.h"
#include "texture.h"
#include "game.h"

EscenaTutorial::EscenaTutorial(Game* g) : GameState(g), picked(false), startGame(false),index(-1), fases(0), bet(0) {
	eco = new PlayerEconomy();
	eco->EconomyInitialize();
	_ui = new UIEscenaTutorial(this, g, this);
	_hud = new HUDBet(this);

	float x = Game::WIN_WIDTH * (0.5f - ((210 - 50) / 1920.0f) * (3 / 2.0f));
	float y = Game::WIN_HEIGHT * (40 / 1080.0f);
	float cartaW = Game::WIN_WIDTH * (210 / 1920.0f);
	float cartaH = Game::WIN_HEIGHT * (210 / 1920.0f);

	Button* piedra = new Button(this, (int)(x + 0 * (Game::WIN_WIDTH * (210 / 1920.0f)) + ((Game::WIN_WIDTH * (210 / 1920.0f) - cartaW) / 2)), (int)(y * 2 + (Game::WIN_HEIGHT * (210 / 1080.0f)) * 3),
		(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	piedra->connect([this] {
			if (!picked) {
				setIndex(0);
				picked = true;
			}
		});
	addObjects(piedra);
	addEventListener(piedra);

	Button* papel = new Button(this, (int)(x + 1 * (Game::WIN_WIDTH * (210 / 1920.0f)) + ((Game::WIN_WIDTH * (210 / 1920.0f) - cartaW) / 2)), (int)(y * 2 + (Game::WIN_HEIGHT * (210 / 1080.0f)) * 3),
		(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	papel->connect([this] {
			if (!picked) {
				setIndex(1);
				picked = true;
			}
		});
	addObjects(papel);
	addEventListener(papel);

	Button* tijera = new Button(this, (int)(x + 2 * (Game::WIN_WIDTH * (210 / 1920.0f)) + ((Game::WIN_WIDTH * (210 / 1920.0f) - cartaW) / 2)), (int)(y * 2 + (Game::WIN_HEIGHT * (210 / 1080.0f)) * 3),
		(int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	tijera->connect([this] {
			if (!picked) {
				setIndex(2);
				picked = true;
			}
		});
	addObjects(tijera);
	addEventListener(tijera);

	/*_dialog = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog);
	_dialog->setPosition();
	_dialog->setWidth();
	_dialog->setHeight();*/

	float w = Game::WIN_WIDTH * (200.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (200.0f / 1080.0f);
	float _x = Game::WIN_WIDTH * (0.5f - ((210 - 20) / 1920.0f) * ((3 / 2.0f) + 1.0f));
	float _y = Game::WIN_HEIGHT * 0.5f - h / 2;
	_bet = new ButtonSlots(this, game, _ui, (int)_x, (int)_y, (int)w, (int)h, game->getTexture(BETSLOTS));
	addObjects(_bet);
	addEventListener(_bet);


}
EscenaTutorial::~EscenaTutorial() {
	for (auto a : flechas) a = nullptr;
	delete eco;
}
void
EscenaTutorial::render() const {
	GameState::render();
	SDL_Rect player;
	player.x = Game::WIN_WIDTH * (210 / 1980.0f) * 3;
	player.y = Game::WIN_HEIGHT * (210 / 1080.0f) * 2;
	player.h = Game::WIN_HEIGHT * (210 / 1080.0f);
	player.w = Game::WIN_WIDTH * (210 / 1920.0f);

	SDL_Rect enemy;
	enemy.x = Game::WIN_WIDTH * (370 / 1980.0f) * 3;
	enemy.y = Game::WIN_HEIGHT * (210 / 1080.0f) * 2;
	enemy.h = Game::WIN_HEIGHT * (210 / 1080.0f);
	enemy.w = Game::WIN_WIDTH * (210 / 1920.0f);

	if (!picked) {
		game->getTexture(SLOTSBUT)->render(player);
		game->getTexture(SLOTSBUT)->render(enemy);
	}
	else {
		game->getTexture(ICONOPPT)->renderFrame(player, 0, index);
		if (index == 0) {
			game->getTexture(ICONOPPT)->renderFrame(enemy, 0, 2);
		}
		else {
			game->getTexture(ICONOPPT)->renderFrame(enemy, 0, index - 1);
		}
	}
}
void EscenaTutorial::update() {
	GameState::update();
	if (index != -1 && picked) {
		game->push(new Award(game, (GameState*)this, bet, bet * 2));
		clear();
	}
	
}