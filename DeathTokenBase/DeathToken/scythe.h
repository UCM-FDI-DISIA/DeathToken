#pragma once
#include "gameState.h"
#include "ui.h"
#include "Button.h"

class scythe : public GameState
{
	Texture* rouletteBG;
	Button* buyButton;
	HUDLobby* hudMenu;
	HUDLobby* hud;
	PlayerEconomy* eco;
	UIScythe* ui;
public:
	scythe(Game* game, PlayerEconomy* eco);
	~scythe() {
		HUDManager::setHudLobby(hudMenu, true);
		hudMenu->refresh();
		delete ui;
	};

	void update() override;
	void render() const override;

	void buyScythe();
};

