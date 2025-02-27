#include "Boundries.h"

Boundries::Boundries(GameState* g, Point2D<> pos) : sceneObject(g, pos, nullptr){}

Collision Boundries::hit(const SDL_Rect& rect, Collision::Target target) {
	
}