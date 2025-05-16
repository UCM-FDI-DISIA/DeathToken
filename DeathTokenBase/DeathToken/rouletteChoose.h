#pragma once
#include "button.h"
#include "gameState.h"
#include "rouletteScene.h"
#include "scythe.h"
#include "ui.h"

class rouletteChoose : public GameState
{
	Texture* rouletteBG;
	Texture* demon;
	Button* guadanya;
	Button* roulette;
	HUDLobby* hudMenu;
	HUDLobby* hud;
	UIRouletteChoose* ui;
public:
	rouletteChoose(Game* game, PlayerEconomy* eco);
	~rouletteChoose() {
		delete ui;
		HUDManager::setHudLobby(hudMenu, false);
		hudMenu->refresh();
	};

	void chooseGame(GameState* juego);

	void update() override;
	void render() const override;
};

