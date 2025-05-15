#pragma once
#include "sceneObject.h"
#include "Vector2D.h"
class Cards : public sceneObject
{
	Texture* texture;
	int frameCard = 0;
	double angle = 0;
public:
	int frame = 0;
	Cards(GameState* game, int frame, Point2D<> pos, double angle = 0);
	void render() const override;
	void update() override;
};

