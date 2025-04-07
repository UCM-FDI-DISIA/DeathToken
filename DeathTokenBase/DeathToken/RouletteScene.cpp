#include "rouletteScene.h"

RouletteScene::RouletteScene(Game* game, PlayerEconomy* eco) : GameState(game), ui(new UIRoulette(this, game, this)), eco(eco), rouletteBG(game->getTexture(ROULETTEBG)) {
	addEventListener(this);
	roul = new Roulette(this, game, { Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 , Game::WIN_HEIGHT / 2 + Game::WIN_WIDTH / 4 }, game->getTexture(ROULETTE), eco);
	addObjects(roul);
	hud = new HUDBet(this);
	arrowTex = game->getTexture(ROULETTEARROW);
}

void RouletteScene::handleEvent(const SDL_Event& event) {

}

void RouletteScene::update() {
	roul->update();
	ui->update();
	if (canThrow) {
		canThrow = false;
		uniform_int_distribution<> distrib(1000, 1500);

		int num = distrib(game->getGen());
		roul->addSpeed(num);
	}
	hud->refresh();
}

void RouletteScene::render() const {
	rouletteBG->render();
	roul->render();
	ui->render();
	SDL_Rect arrow = { Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 30, Game::WIN_HEIGHT / 2 - Game::WIN_WIDTH / 30,
		Game::WIN_WIDTH / 15, Game::WIN_WIDTH / 15 };
	arrowTex->render(arrow);
}

void RouletteScene::throwRoulette() {
	if (eco->getBlueSouls() >= costPerThrow) {
		canThrow = true;
		eco->addBlueSouls(-500);
	}
}
