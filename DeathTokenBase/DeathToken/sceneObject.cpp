#include "checkML.h"

#include "gameState.h"
#include "sceneObject.h"
#include "texture.h"
#include "game.h"

sceneObject::sceneObject(GameState* p, istream& in, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), state(p), moveDelay(0), speed(sp), w(w* Game::TILE_SIDE), h(h* Game::TILE_SIDE), frame(0), texture(text)
{
	in >> pos;
	pos = pos * Game::TILE_SIDE;
}
sceneObject::sceneObject(GameState* p, Vector2D<> pos, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), state(p), moveDelay(0), pos(pos), speed(sp), w(w), h(h), frame(0), texture(text)
{	}
sceneObject::sceneObject(GameState* p, Texture* text) : GameObject(p), state(p), texture(text)
{	}
sceneObject::sceneObject(GameState* p, Vector2D<> pos, Texture* text) : GameObject(p), pos(pos), texture(text) {

}
sceneObject::sceneObject(GameState* p, Vector2D<> position, int width, int height, Texture* t)
	: GameObject(p), pos(position), speed({0,0}), w(width), h(height), frame(0), texture(t)
{}

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
		pos.getX() - 0,  // coordenadas de la ventana
		pos.getY() - h,
		w,
		h
	};
}