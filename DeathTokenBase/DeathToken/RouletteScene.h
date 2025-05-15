#pragma once
#include "gameState.h"
#include "roulette.h"
#include "eventHandler.h"
#include "ui.h"

class RouletteScene : public GameState, public EventHandler
{
	Roulette* roul;
	Texture* rouletteBG;
	Texture* rouletteFrame;
	Texture* arrowTex;
	int costPerThrow = 500;
	int canThrow = false;
	PlayerEconomy* eco;
	HUDLobby* hudMenu;
	HUDLobby* hud;
	UIRoulette* ui;
public:
	RouletteScene(Game* g, PlayerEconomy* eco);
	virtual ~RouletteScene() {
		delete ui; 
		HUDManager::setHudLobby(hudMenu);
		hudMenu->refresh();
	};
	void handleEvent(const SDL_Event& event) override;
	void throwRoulette();
	void update() override;
	void render() const override;
};

