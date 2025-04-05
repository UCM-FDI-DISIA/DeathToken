#pragma once
#include "Vector2D.h"
#include "sceneObject.h"
#include "Award.h"

class Roulette : public sceneObject
{
	Game* game;
	GameState* gS;
	Texture* texture;
	double rot = 0;
	int speed = 0;
	float decelerate = 0.95;
	bool started = false;
	PlayerEconomy* eco;
public:
	Roulette(GameState* gS, Game* game, Point2D<> pos, Texture* text, PlayerEconomy* eco);
	void addSpeed(int s);

	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
};

