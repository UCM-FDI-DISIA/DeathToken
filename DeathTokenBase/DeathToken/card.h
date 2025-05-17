#pragma once
#include "vector2D.h"
#include "sceneObject.h"
class Card : public SceneObject
{
	Texture* texture;
	int frameCard = 0;
	double angle = 0;
public:
	int frame = 0;
	Card(GameState* game, int frame, Point2D<> pos, double angle = 0);
	void render() const override;
	void update() override;
};

