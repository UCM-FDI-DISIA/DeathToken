#pragma once

// Biblioteca estándar de C++
#include <array>
#include <string>
#include <vector>
#include <list>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "gameState.h"
class Texture;
class sceneObject;
class TileMap;
class Player;

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class PlayState : public GameState
{
private:

	std::vector<sceneObject*> objectQueue;
	int nextObject;
	std::list<sceneObject*> objects;

public:
	PlayState(Game*, int lvl);
	~PlayState();

	void update() override;
};


