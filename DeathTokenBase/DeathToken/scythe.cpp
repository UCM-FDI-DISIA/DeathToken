#include "scythe.h"
#include "finalMenu.h"

Scythe::Scythe(Game* game) : GameState(game), ui(new UIScythe(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG))
{
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 4, hBut = Game::WIN_HEIGHT / 2,
		xBut = Game::WIN_WIDTH / 2 - wBut / 2, yBut = Game::WIN_HEIGHT / 2 - hBut / 2;
	buyButton = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(SCYTHE));
	addEventListener(buyButton);
	addObjects(buyButton);
	buyButton->connect([this]() { buyScythe();});

	HUDLobby* hud = new HUDLobby(this, true);
	hud->refresh();
}

void Scythe::render() const
{
	rouletteBG->render();
	GameState::render();
}

void Scythe::buyScythe()
{
	if (PlayerEconomy::getRedSouls() >= 0) {
		game->stop();
		game->pushState(new FinalMenu(game, true));
	}
}
