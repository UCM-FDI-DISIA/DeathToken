#pragma once
#include <SDL.h>
#include "sceneObject.h"
#include "Texture.h"

class Enemy : public sceneObject {
protected:
	static constexpr int POINTS = 500;
	static constexpr int SPEED_MAG = 4;

public:
	Enemy(PlayState*, istream&, Texture*, int, int);
	Enemy(PlayState*, Vector2D<>, Texture*, int, int);
	Collision hit(const SDL_Rect&, Collision::Target) override;
	void update() override;
	void render() const override;
};