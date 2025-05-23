﻿#include "rouletteScene.h"
#include "soundManager.h"

RouletteScene::RouletteScene(Game* game) : GameState(game), ui(new UIRoulette(this, game, this)), rouletteBG(game->getTexture(ROULETTEBG)) {
	hud = new HUDLobby(this, true);
	hud->refresh();

	roul = new Roulette(this, game, { Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 4 , Game::WIN_HEIGHT / 2 + Game::WIN_WIDTH / 4 }, game->getTexture(ROULETTE));
	addObjects(roul);
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
	if (PlayerEconomy::getBlueSouls() >= costPerThrow) 
	{
		if (roul->getSpeed() == 0) {
			SoundManager::obtenerInstancia().reproducirEfecto("RuletaSonido");
		}	
		canThrow = true;
		ui->seOnBet(true);
	}
}
