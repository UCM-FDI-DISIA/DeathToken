#pragma once
#include "checkML.h"
#include <vector>


#include "sceneObject.h"

class Boundries : public sceneObject {
private:
	SDL_Rect colision;
public:
	Boundries(GameState*,Point2D<>);
	Collision hit(const SDL_Rect&, Collision::Target) override;
};