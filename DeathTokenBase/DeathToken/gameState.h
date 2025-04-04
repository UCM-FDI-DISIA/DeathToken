#pragma once
#include <SDL.h>
#include <list>
#include "gameList.h"
#include "gameObject.h"
#include "EventHandler.h"
class Game;

class GameState {
protected:
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
	Game* game;
public:
	GameState(Game* g) : game(g) {}
	virtual ~GameState();
	Game* getGame() { return game; }
	virtual void update();
	virtual void render() const;
	void handleEvent(const SDL_Event&);
	void addEventListener(EventHandler* obj);
	void addObjects(GameObject* obj);
	virtual void showTutorial() {};
};

