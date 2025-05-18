#pragma once
#include "gameState.h"
#include "roulette.h"
#include "eventHandler.h"
#include "ui.h"

class RouletteScene : public GameState
{
	Roulette* roul;
	Texture* rouletteBG;
	Texture* rouletteFrame;
	Texture* arrowTex;
	int costPerThrow = 2000;
	int canThrow = false;
	HUDLobby* hud;
	UIRoulette* ui;
public:
	RouletteScene(Game* g);
	virtual ~RouletteScene() {
		delete ui;
	};
	void throwRoulette();
	void update() override;
	void render() const override;
};

