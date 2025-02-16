#pragma once

// Biblioteca estándar de C++
#include <array>
#include <string>
#include <vector>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "gameState.h"
#include "Collision.h"
class Texture;
class sceneObject;
class Player;

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class PlayState : public GameState
{
private:

	// Interruptor para terminar el juego
	int actLevel;
	int puntos;

	// Objetos del juego
	Player* Mario;
	std::vector<sceneObject*> objectQueue;
	GameList<sceneObject> objects;
	void end(bool);

public:
	PlayState(Game*, int lvl);
	~PlayState();

	void update() override;

	void pausa();

	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);

	void loadObjectMap(const std::string file);
	void addToSceneList(sceneObject*);
	bool getSuper() const;
	void superOrDamage(bool);
	void restartLevel();
	void nextLevel();
	void givePoints(const int sumar);

	// Constante globales
	static constexpr uint GRAVITY = 4;
};


