#pragma once
#include "vector2D.h"
#include "sceneObject.h"
#include "award.h"

class Roulette : public sceneObject
{
	Game* game;
	GameState* gS;
	Texture* texture;
	double rot = 0;
	double speed = 0;
	float decelerate = 0.95;
	bool started = false;
	PlayerEconomy* eco;
	float animTime = 0.0f;
	int i = 0;
public:
	Roulette(GameState* gS, Game* game, Point2D<> pos, Texture* text, PlayerEconomy* eco);
	void addSpeed(int s);

	void render() const override;
	void update() override;
};

