#pragma once
#include "gameState.h"
#include "texture.h"
#include "text.h"
#include "UI.h"

class Ranking : public GameState
{
private:
	GameState* state;
	UIRanking* ui;
	Texture* background;

public:
	Ranking(Game* game, GameState* lastState);
	~Ranking() { delete ui; };
	void render()const  override;
	void update() override;
	int relativeX(const float& n);
	int relativeY(const float& n);
};

