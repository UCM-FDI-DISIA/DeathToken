#pragma once
#include "Enemy.h"

class Koopa : public Enemy{
public:
	Koopa(PlayState* g, istream& in, Texture* text);
	Koopa(const Koopa&);
	sceneObject* clone() const override;
};