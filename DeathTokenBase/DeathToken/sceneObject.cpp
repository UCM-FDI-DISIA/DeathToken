#include "checkML.h"

#include "gameState.h"
#include "sceneObject.h"
#include "texture.h"
#include "game.h"

SceneObject::SceneObject(GameState* p, Vector2D<> pos, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), state(p), pos(pos), speed(sp), w(w), h(h), frame(0), texture(text)
{	}
SceneObject::SceneObject(GameState* p, Texture* text) : GameObject(p), state(p), texture(text)
{	}
SceneObject::SceneObject(GameState* p, Vector2D<> pos, Texture* text) : GameObject(p), pos(pos), texture(text) {

}
SceneObject::SceneObject(GameState* p, Vector2D<> position, int width, int height, Texture* t)
	: GameObject(p), pos(position), speed({0,0}), w(width), h(height), frame(0), texture(t)
{}

// Devuelve el rect de collision
SDL_Rect
SceneObject::getCollisionRect() const
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
SceneObject::getRenderRect() const
{
	return SDL_Rect{
		pos.getX() - 0,  // coordenadas de la ventana
		pos.getY() - h,
		w,
		h
	};
}