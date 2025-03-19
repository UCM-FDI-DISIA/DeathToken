#pragma once
#include <SDL.h>
#include "gameObject.h"
#include "Collision.h"
#include "Vector2D.h"
#include "Game.h"
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
	GameList<sceneObject>::anchor anchor;

public:
	sceneObject(GameState*, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, istream&, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, Vector2D<>, Vector2D<>, int, int, Texture*);
	sceneObject(GameState*, Texture*);
	sceneObject(GameState*, Vector2D<>, Texture*);
	virtual ~sceneObject() { texture = nullptr; state = nullptr; };
	void setListAnchor(GameList<sceneObject>::anchor&& anchor);
	virtual Collision hit(const SDL_Rect&, Collision::Target) = 0;
	virtual void update();
	Vector2D<> position() const { return pos; };
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};