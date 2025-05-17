#pragma once
#include "gameState.h"
#include "ui.h"
#include "button.h"

class Scythe : public GameState
{
	Texture* rouletteBG;
	Button* buyButton;
	HUDLobby* hudMenu;
	HUDLobby* hud;
	PlayerEconomy* eco;
	UIScythe* ui;
public:
	Scythe(Game* game, PlayerEconomy* eco);
	~Scythe() {
		HUDManager::setHudLobby(hudMenu, true);
		hudMenu->refresh();
		delete ui;
	};

	void update() override;
	void render() const override;

	void buyScythe();
};

