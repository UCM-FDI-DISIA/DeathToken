#include "checkML.h"

#include "Pickable.h"

Pickable::Pickable(GameState* g, istream& pos, Vector2D<> speed, Texture* tex, int w, int h)
	: sceneObject(g, pos, speed, w, h, tex)
{
}
Pickable::Pickable(GameState* g, Vector2D<> pos, Vector2D<> speed, Texture* tex, int w, int h)
	: sceneObject(g, pos, speed, w, h, tex)
{
}

// Si colisiona con el jugador llama a trigger action y se elimina
Collision
Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisi�n
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::PLAYER && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();  // m�todo protegido que implementar� la subclase
		delete this;
	}

	return NO_COLLISION; // constante Collision{}
}