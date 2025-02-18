#include "checkML.h"

#include "playState.h"
#include "sceneObject.h"
#include "Texture.h"
#include "Game.h"

sceneObject::sceneObject(GameState* p, istream& in, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), speed(sp), w(w), h(h), frame(0), texture(text)
{
}
sceneObject::sceneObject(GameState* p, Vector2D<> pos, Vector2D<> sp, int w, int h, Texture* text)
	: GameObject(p), pos(pos), speed(sp), w(w), h(h), frame(0), texture(text)
{	}


sceneObject::sceneObject(GameState* p, Vector2D<> position, int width, int height, Texture* t)
	: GameObject(p), pos(position), speed({0,0}), w(width), h(height), frame(0), texture(t)
{}