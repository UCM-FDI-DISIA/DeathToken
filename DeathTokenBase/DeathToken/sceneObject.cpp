#include "checkML.h"

#include "playState.h"
#include "sceneObject.h"
#include "Texture.h"
#include "Game.h"

sceneObject::sceneObject(PlayState* p, /*istream& in, Vector2D<> sp,*/ int w, int h, Texture* text)
	: GameObject(p), state(p), moveDelay(0), /*speed(sp),*/ w(w* Game::TILE_SIDE), h(h* Game::TILE_SIDE), frame(0), texture(text)
{
	//in >> pos;
	pos = pos * Game::TILE_SIDE;
}
sceneObject::sceneObject(PlayState* p, Vector2D<> pos, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), state(p), moveDelay(0), pos(pos), /*speed(sp),*/ w(w), h(h), frame(0), texture(text)
{	}
sceneObject::sceneObject(PlayState* p, Texture* text) : GameObject(p), state(p), texture(text)
{	}

// Devuelve el rect de collision
SDL_Rect
sceneObject::getCollisionRect() const
{
	return SDL_Rect{
		pos.getX(),
		pos.getY() - h,  // la referencia es la esquina inferior izquierda
		w,
		h
	};
}
// Devuelve el rect de renderizado
SDL_Rect
sceneObject::getRenderRect() const
{
	return SDL_Rect{
		pos.getX() - state->getOffset(),  // coordenadas de la ventana
		pos.getY() - h,
		w,
		h
	};
}
void sceneObject::setListAnchor(GameList<sceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}

// Comprueba que os objetos se eliminen cuando caen al vacío
void sceneObject::update() {
	int side = Game::TILE_SIDE;
	SDL_Rect rect = getCollisionRect();
	if (rect.y + rect.h >= Game::WIN_HEIGHT * side - side/2
		|| pos.getX() < 0)
		delete this;
}
// Intenta mover el objeto segun su velocidad comprobando las colisiones
Collision
sceneObject::tryToMove(const Vector2D<>& speed, Collision::Target target)
{
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0) {
		rect.y += speed.getY();

		collision = state->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		pos += {0, speed.getY() - fix};

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	if (speed.getX() != 0) {
		rect.x += speed.getX();

		Collision partial = state->checkCollision(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		pos += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
	}

	return collision;
}
