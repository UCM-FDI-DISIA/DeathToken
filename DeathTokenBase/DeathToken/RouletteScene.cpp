#include "RouletteScene.h"

RouletteScene::RouletteScene(Game* game) : GameState(game), rouletteBG(game->getTexture(ROULETTEBG)) {
	addEventListener(this);
	int wBut = Game::WIN_WIDTH / 6, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH * 4 / 5, yBut = Game::WIN_HEIGHT * 3 / 4;
	rouletteThrow = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(ROULETTEPLAY));
	addObjects(rouletteThrow);
	addEventListener(rouletteThrow);
	rouletteThrow->connect([this]() { throwRoulette(); });
	roul = new Roulette(this, { Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 , Game::WIN_HEIGHT * 14 / 15 }, game->getTexture(ROULETTE));
	addObjects(roul);
}

void RouletteScene::handleEvent(const SDL_Event& event) {

}

void RouletteScene::update() {
	GameState::update();
	if (canThrow) {
		canThrow = false;
		uniform_int_distribution<> distrib(1000, 1500);

		int num = distrib(game->getGen());
		roul->addSpeed(num);
	}
}

void RouletteScene::render() const {
	rouletteBG->render();
	GameState::render();
}

void RouletteScene::throwRoulette() {
	/*if (totalMoney >= costPerThrow)*/
	canThrow = true;
}
