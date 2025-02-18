#pragma once
#include <SDL.h>
#include "gameObject.h"
#include "Vector2D.h"
#include "Game.h"
class Texture;
class PlayState;

class sceneObject : public GameObject {
protected:
	Point2D<> pos;
	Vector2D<> speed;
	Texture* texture;
	int frame;
	int w, h;
	GameList<sceneObject>::anchor anchor;
	
public:
	sceneObject(GameState*,istream&, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, Vector2D<>, Vector2D<>, int, int, Texture*);

	sceneObject(GameState*, Vector2D<>, int, int, Texture*);
	virtual ~sceneObject() { texture = nullptr; state = nullptr; };
	virtual void update() {}
	Vector2D<> position() const{ return pos; };
};