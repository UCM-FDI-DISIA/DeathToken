#pragma once
#include <SDL.h>
#include "gameObject.h"
#include "Collision.h"
#include "Vector2D.h"
#include "Game.h"
class Texture;
class PlayState;

class sceneObject : public GameObject {
protected:
	static constexpr int SPEED_LIMIT = Game::TILE_SIDE - 4;
	static constexpr int MOVE_PERIOD = 2; 
	Point2D<> pos;
	//Vector2D<> speed;
	Texture* texture;
	int frame;
	int w, h;
	int moveDelay;
	PlayState* state;
	GameList<sceneObject>::anchor anchor;
	
public:
	sceneObject(PlayState*,/* istream&, Vector2D<>,*/ int, int, Texture*);
	sceneObject(PlayState*, Vector2D<>, Vector2D<>, int, int, Texture*);
	sceneObject(PlayState*, Texture*);
	virtual ~sceneObject() { texture = nullptr; state = nullptr; };
	void setListAnchor(GameList<sceneObject>::anchor&& anchor);
	virtual sceneObject* clone() const = 0;
	virtual Collision hit(const SDL_Rect&, Collision::Target) = 0;
	virtual void update();
	Vector2D<> position() const{ return pos; };
	Collision tryToMove(const Vector2D<>&, Collision::Target);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};