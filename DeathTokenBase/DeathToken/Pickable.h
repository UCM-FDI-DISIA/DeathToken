#pragma once
#include "sceneObject.h"

class Pickable : public sceneObject {
public:
	Pickable(PlayState*, istream&, Vector2D<>, Texture*, int, int);
	Pickable(PlayState*, Vector2D<>, Vector2D<>, Texture*, int, int);
	Collision hit(const SDL_Rect&, Collision::Target) override;
	virtual void triggerAction() = 0;
};