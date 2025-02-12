#pragma once
#include "sceneObject.h"

class Lift : public sceneObject {
protected:
	int velocity;
public:
	Lift(PlayState*, istream&, Texture*);
	Lift(const Lift&);
	sceneObject* clone() const override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
	void update() override;
	void render() const override;
};