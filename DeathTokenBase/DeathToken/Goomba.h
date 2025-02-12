#pragma once
#include "Enemy.h"

class Goomba : public Enemy{
private:
public:
	Goomba(PlayState* g, istream& in, Texture* text);
	Goomba(const Goomba&);
	sceneObject* clone() const override;
};
