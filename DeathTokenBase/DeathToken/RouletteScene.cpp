#include "rouletteScene.h"

RouletteScene::RouletteScene(Game* game, PlayerEconomy* eco) : GameState(game), ui(new UIRoulette(this, game, this)), eco(eco), rouletteBG(game->getTexture(ROULETTEBG)) {
	roul = new Roulette(this, game, { Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 , Game::WIN_HEIGHT / 2 + Game::WIN_WIDTH / 4 }, game->getTexture(ROULETTE), eco);
	addObjects(roul);
	hudMenu = HUDManager::getHudLobby();
	hud = new HUDLobby(this, true);
	arrowTex = game->getTexture(ROULETTEARROW);
	rouletteFrame = game->getTexture(ROULETTEFRAME);
}

void RouletteScene::update() {
	GameState::update();
	if (canThrow) {
		canThrow = false;
		uniform_int_distribution<> distrib(1000, 1500);

		int num = distrib(game->getGen());
		roul->addSpeed(num);
	}
	hud->refresh();
	if (roul->getSpeed() == 0) {
		ui->seOnBet(false);
	}
	else {
		ui->seOnBet(true);
	}
}

void RouletteScene::render() const {
	rouletteBG->render();
	rouletteFrame->render();
	GameState::render();
	float x = Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 5.5, y = Game::WIN_HEIGHT / 2 - Game::WIN_HEIGHT / 8.35,
		w = Game::WIN_WIDTH / 5.12, h = Game::WIN_HEIGHT / 3.042;
	SDL_Rect arrow = { x, y,
		w,  h };

	arrowTex->render(arrow);

}

void RouletteScene::throwRoulette() {
	if (eco->getBlueSouls() >= costPerThrow) {
		canThrow = true;
		ui->seOnBet(true);
	}
}
