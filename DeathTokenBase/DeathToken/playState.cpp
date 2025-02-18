#include <fstream>
#include <sstream>

#include "checkML.h"
#include "playState.h"

#include "Game.h"
#include "Texture.h"
#include "gameObject.h"
#include "sceneObject.h"
#include "Player.h"



PlayState::PlayState(Game* g, int lvl)
	: GameState(g), objects()
{

}

PlayState::~PlayState()
{
	// Elimina los objetos del juego
	for (sceneObject* object : objects)
		delete object;
	for (sceneObject* obj : objectQueue) delete obj;
	objectQueue.clear();
}

void
PlayState::update()
{
	// Actualiza los objetos del juego
	GameState::update();
}