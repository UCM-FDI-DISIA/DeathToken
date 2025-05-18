#pragma once
#include "button.h"
#include "gameState.h"
#include "rouletteScene.h"
#include "scythe.h"
#include "ui.h"

class RouletteChoose : public GameState
{
	Texture* rouletteBG;
	Texture* demon;
	Button* guadanya;
	Button* roulette;
	HUDLobby* hudMenu;
	HUDLobby* hud;
	UIRouletteChoose* ui;
public:
	RouletteChoose(Game* game);
	~RouletteChoose() {
		delete ui;
		HUDManager::setHudLobby(hudMenu, false);
	};

	void chooseGame(GameState* juego);

	void update() override;
	void render() const override;
};

