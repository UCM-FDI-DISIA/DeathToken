#pragma once
#include "gameState.h"
#include "ui.h"
#include "button.h"

class Scythe : public GameState
{
	Texture* rouletteBG;
	Button* buyButton;
	UIScythe* ui;
public:
	Scythe(Game* game);
	~Scythe() {
		delete ui;
	};
	void render() const override;

	void buyScythe();
};

