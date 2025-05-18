#include "rouletteChoose.h"

RouletteChoose::RouletteChoose(Game* game) : GameState(game), ui(new UIRouletteChoose(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG))
{
	double wBut = Game::WIN_WIDTH / 4, hBut = Game::WIN_HEIGHT / 2,
		xBut = Game::WIN_WIDTH / 3 - wBut * 3 / 4, yBut = Game::WIN_HEIGHT / 2 - hBut / 2;
	guadanya = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(SCYTHE));
	addEventListener(guadanya);
	addObjects(guadanya);
	guadanya->connect([this]() { chooseGame(new Scythe(getGame()));});

	xBut = Game::WIN_WIDTH * 2 / 3 - wBut / 3;
	roulette = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(ROULETTE));
	addEventListener(roulette);
	addObjects(roulette);
	roulette->connect([this]() { chooseGame(new RouletteScene(getGame()));});

	hudMenu = HUDManager::getHudLobby();
	hud = new HUDLobby(this, true);

	demon = game->getTexture(CHOOSEDEMON);

	Text* price = new Text(this, game->getTypo(GRAND_CASINO1), (int)(Game::WIN_WIDTH * 0.75f), (int)(Game::WIN_HEIGHT * 0.8f), 5, Text::CENTRO);
	price->setMessage("500 FICHAS");
	this->addObjects(price);
	Text* souls = new Text(this, game->getTypo(GRAND_CASINO1), (int)(Game::WIN_WIDTH * 0.25f), (int)(Game::WIN_HEIGHT * 0.8f), 5, Text::CENTRO);
	souls->setMessage("200 ALMAS");
	this->addObjects(souls);
}

void RouletteChoose::chooseGame(GameState* juego)
{
	game->push(juego);
}

void RouletteChoose::update()
{
	GameState::update();
	hud->refresh();
}

void RouletteChoose::render() const
{
	rouletteBG->render();
	float w = Game::WIN_WIDTH / 3.84, h = Game::WIN_HEIGHT / 2.2815, x = Game::WIN_WIDTH / 2 - w / 1.5, y = Game::WIN_HEIGHT - h;
	SDL_Rect d = { x, y,
		w,  h };
	demon->render(d);
	GameState::render();
}
