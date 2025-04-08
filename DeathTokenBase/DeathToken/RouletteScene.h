#pragma once
#include "gameState.h"
#include "roulette.h"
#include "eventHandler.h"
#include "ui.h"

class RouletteScene : public GameState, public EventHandler
{
	Roulette* roul;
	Texture* rouletteBG;
	Texture* arrowTex;
	int costPerThrow = 500;
	int canThrow = false;
	PlayerEconomy* eco;
	HUDBet* hud;
	UIRoulette* ui;
public:
	RouletteScene(Game* g, PlayerEconomy* eco);
	virtual ~RouletteScene() { HUDManager::popGame(); delete ui; };
	void handleEvent(const SDL_Event& event) override;
	void throwRoulette();
	void update() override;
	void render() const override;
};

