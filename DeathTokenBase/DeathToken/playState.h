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
class TileMap;
class Player;

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class PlayState : public GameState
{
private:
	
	// Interruptor para terminar el juego
	int mapOffset;
	int maxOffset;
	std::vector<std::string> levels;
	std::vector<std::string> levelsTile;
	int actLevel;
	int puntos;

	struct Color { int R, G, B; };
	Color color;

	// Objetos del juego
	TileMap* Background;
	Player* Mario;
	std::vector<sceneObject*> objectQueue;
	int nextObject;
	GameList<sceneObject> objects;
	void addVisibleObjects();
	void end(bool);

public:
	PlayState(Game*, int lvl);
	~PlayState();

	void update() override;
	void setMaxOffset(int max);
	int getOffset() const;
	void offsetPlus(int plus);

	void pausa();

	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);

	void loadObjectMap(const std::string file);
	void addToSceneList(sceneObject*);
	bool getSuper() const;
	void superOrDamage(bool);
	void restartLevel();
	void nextLevel();
	void givePoints(const int sumar);
	Color getColor() { return color; }

	// Constante globales
	static constexpr uint GRAVITY = 4;
};


