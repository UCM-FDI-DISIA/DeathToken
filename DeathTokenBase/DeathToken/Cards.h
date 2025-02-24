#pragma once
#include "Vector2D.h"
#include "sceneObject.h"
class Cards : public sceneObject
{
	Texture* texture;
	int frame = 0;
	int frameCard = 0;
public:
	Cards(GameState* game, int frame, Point2D<> pos);
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
};

