#include "scythe.h"
#include "finalMenu.h"

scythe::scythe(Game* game, PlayerEconomy* eco) : GameState(game), eco(eco), ui(new UIScythe(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG))
{
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 4, hBut = Game::WIN_HEIGHT / 4,
		xBut = Game::WIN_WIDTH / 2 - wBut / 2, yBut = Game::WIN_HEIGHT / 2 - hBut / 2;
	buyButton = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(BACCARATBUT));
	addEventListener(buyButton);
	addObjects(buyButton);
	buyButton->connect([this, eco]() { buyScythe();});

	hudMenu = HUDManager::getHudLobby();
	hud = new HUDLobby(this);
}

void scythe::update()
{
	GameState::update();
	hud->refresh();
}

void scythe::render() const
{
	rouletteBG->render();
	GameState::render();
}

void scythe::buyScythe()
{
	if (eco->getRedSouls() >= 200) {
		game->stop();
		game->pushState(new FinalMenu(game, true));
	}
}
