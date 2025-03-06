#pragma once
#include "Vector2D.h"
#include "sceneObject.h"

class Roulette : public sceneObject
{
	Texture* texture;
	double rot = 0;
	int speed = 0;
	float decelerate = 0.95;
public:
	Roulette(GameState* game, Point2D<> pos, Texture* text);
	void addSpeed(int s);

	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
};

