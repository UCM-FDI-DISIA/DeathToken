#include "rouletteChoose.h"

rouletteChoose::rouletteChoose(Game* game, PlayerEconomy* eco) : GameState(game), ui(new UIRouletteChoose(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG))
{
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 4, hBut = Game::WIN_HEIGHT / 4,
		xBut = Game::WIN_WIDTH / 3 - wBut * 3 / 4, yBut = Game::WIN_HEIGHT / 2 - hBut / 2;
	guadanya = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(BACCARATBUT));
	addEventListener(guadanya);
	addObjects(guadanya);
	guadanya->connect([this, eco]() { chooseGame(new scythe(getGame(), eco));});

	xBut = Game::WIN_WIDTH * 2 / 3 - wBut / 3;
	roulette = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(ROULETTE));
	addEventListener(roulette);
	addObjects(roulette);
	roulette->connect([this, eco]() { chooseGame(new RouletteScene(getGame(), eco));});

	hudMenu = HUDManager::getHudLobby();
	hud = new HUDLobby(this, true);

	demon = game->getTexture(CHOOSEDEMON);
}

void rouletteChoose::chooseGame(GameState* juego)
{
	game->push(juego);
}

void rouletteChoose::update()
{
	GameState::update();
	hud->refresh();
}

void rouletteChoose::render() const
{
	rouletteBG->render();
	float w = Game::WIN_WIDTH / 3.84, h = Game::WIN_HEIGHT / 2.2815, x = Game::WIN_WIDTH / 2 - w / 2, y = Game::WIN_HEIGHT - h;
	SDL_Rect d = { x, y,
		w,  h };
	demon->render(d);
	GameState::render();
}
