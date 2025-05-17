#pragma once
#include <SDL.h>
#include "gameObject.h"
#include "vector2D.h"
#include "game.h"
class Texture;

class SceneObject : public GameObject {
protected:
	Point2D<> pos;
	Vector2D<> speed;
	Texture* texture;
	int frame;
	int w, h;
	GameState* state;

public:
	SceneObject(GameState*, Vector2D<>, int, int, Texture*);
	SceneObject(GameState*, Vector2D<>, Vector2D<>, int, int, Texture*);
	SceneObject(GameState*, Texture*);
	SceneObject(GameState*, Vector2D<>, Texture*);

	virtual ~SceneObject() { texture = nullptr; state = nullptr; }
	Vector2D<> position() const { return pos; };
	void setPos(Point2D<> pos2) { pos = pos2; };
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};