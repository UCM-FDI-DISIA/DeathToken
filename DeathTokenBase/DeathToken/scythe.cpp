#include "scythe.h"
#include "finalMenu.h"

Scythe::Scythe(Game* game, PlayerEconomy* eco) : GameState(game), eco(eco), ui(new UIScythe(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG))
{
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 4, hBut = Game::WIN_HEIGHT / 2,
		xBut = Game::WIN_WIDTH / 2 - wBut / 2, yBut = Game::WIN_HEIGHT / 2 - hBut / 2;
	buyButton = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(SCYTHE));
	addEventListener(buyButton);
	addObjects(buyButton);
	buyButton->connect([this, eco]() { buyScythe();});

	hudMenu = HUDManager::getHudLobby();
	hud = new HUDLobby(this, true);
}

void Scythe::update()
{
	GameState::update();
	hud->refresh();
}

void Scythe::render() const
{
	rouletteBG->render();
	GameState::render();
}

void Scythe::buyScythe()
{
	if (eco->getRedSouls() >= 200) {
		game->stop();
		game->pushState(new FinalMenu(game, true));
	}
}
