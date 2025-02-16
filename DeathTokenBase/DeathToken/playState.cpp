#include <fstream>
#include <sstream>

#include "checkML.h"
#include "playState.h"

#include "Game.h"
#include "Texture.h"
#include "Collision.h"
#include "gameObject.h"
#include "sceneObject.h"
#include "Player.h"
#include "PauseState.h"
#include "EndState.h"



PlayState::PlayState(Game* g, int lvl)
	: GameState(g), objects(), actLevel(lvl)
{
	// Cargamos el nivel correspondiente
	Mario = nullptr;
	nextLevel();
}

PlayState::~PlayState()
{
	// Elimina los objetos del juego
	for (sceneObject* object : objects)
		delete object;
	for (sceneObject* obj : objectQueue) delete obj;
	objectQueue.clear();
}

void PlayState::addToSceneList(sceneObject* h) {
	objects.push_back(h);
}

void
PlayState::update()
{
	// Actualiza los objetos del juego
	GameState::update();
}

// Suma cierta cantidad de puntos y los presenta junto a la vidas actuales por consola
void PlayState::givePoints(const int sumar)
{
	puntos += sumar;

	std::cout << "Puntos: " << puntos << " Vidas: " << Mario->getVidas() << endl;
}

bool PlayState::getSuper() const { return Mario->getSuper(); }
// Gestiona si Mario ha recibido un power up o daño y se lo comunica.
void PlayState::superOrDamage(bool sup) {
	Mario->superOrDamage(sup);
}
// Reinicia el nivel borrando los objetos de la lista y seteando mapoffset y otros parametros a 0
// Avisa también a Mario para que vuelva a su posicion de origen
void PlayState::restartLevel() {
	for (sceneObject* obj : objects)
	{
		delete obj;
	}
	if (Mario != nullptr) {
		std::cout << "Puntos: " << puntos << " Vidas: " << Mario->getVidas() << endl;
		if (Mario->getVidas() == 0) end(false);
	}
}
// Carga el siguiente nivel (siempre que queden) y borra los objetos del nivel anterior para argar los del siguiente.
void PlayState::nextLevel() {
	game->push(new PauseState(game, this));
}

void PlayState::pausa() {
	game->push(new PauseState(game, this));
}

void PlayState::end(bool win) {
	game->replace(new EndState(game, win));
}
// Carga los objetos del mapa
void
PlayState::loadObjectMap(const std::string file) {

}

// Comprueba las colisiones de los objetos
Collision PlayState::checkCollision(const SDL_Rect& rect, Collision::Target target) {
	// Comprueba las colisiones entre los objetos en pantalla hasta que encuentre alguna.
	// Si no la ha encontrado comprueba la colision con el TileMap
	Collision col;
	bool hit = false;

	for (sceneObject* obj : objects) {
		if (!hit) {
			col = obj->hit(rect, target);
			hit = col.result != col.NONE;
			if (target == Collision::PLAYER && Mario->getInv() && col.result == col.DAMAGE) hit = false;
		}
	}
	if (hit) return col;
}
