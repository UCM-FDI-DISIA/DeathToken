#pragma once
#include "gameList.h"

class GameState;

class GameObject {
protected:
	GameState* state;
	GameList<GameObject>::anchor anchor;
public:
	GameObject(GameState* g) : state(g){}
	void setListAnchor(GameList<GameObject>::anchor&& anchor){
		this->anchor = std::move(anchor);
	}
	virtual void render() const = 0;
	virtual void update() = 0;
};