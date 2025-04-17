#pragma once
#include <SDL.h>
#include "gameObject.h"
#include "vector2D.h"
#include "game.h"
class Texture;

class sceneObject : public GameObject {
protected:
	static constexpr int SPEED_LIMIT = 4;
	static constexpr int MOVE_PERIOD = 2;
	Point2D<> pos;
	Vector2D<> speed;
	Texture* texture;
	int frame;
	int w, h;
	int moveDelay;
	GameState* state;

public:
	sceneObject(GameState*, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, Vector2D<>, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, Texture*);
	sceneObject(GameState*, Vector2D<>, Texture*);

	virtual ~sceneObject() { texture = nullptr; state = nullptr; }
	Vector2D<> position() const { return pos; };
	void setPos(Point2D<> pos2) { pos = pos2; };
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};