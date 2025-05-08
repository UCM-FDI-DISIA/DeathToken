#pragma once
#include "sceneObject.h"

class Pickable : public sceneObject {
public:
	Pickable(GameState*, istream&, Vector2D<>, Texture*, int, int);
	Pickable(GameState*, Vector2D<>, Vector2D<>, Texture*, int, int);
	Collision hit(const SDL_Rect&, Collision::Target) override;
	virtual void triggerAction() = 0;
};