#include <fstream>
#include <sstream>

#include "checkML.h"
#include "playState.h"

#include "Game.h"
#include "Texture.h"
#include "Collision.h"
#include "TileMap.h"
#include "gameObject.h"
#include "sceneObject.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Block.h"
#include "Lift.h"
#include "Player.h"
#include "Coin.h"
#include "PauseState.h"
#include "EndState.h"



PlayState::PlayState(Game* g, int lvl)
	: GameState(g), objects(), actLevel(lvl)
{
	// Cargamos los tilemaps (csv) de cada nivel
	levelsTile.push_back("../assets/maps/world1.csv"s);
	levelsTile.push_back("../assets/maps/world2.csv"s);

	// Cargamos los archivos con los objetos
	levels.push_back("../assets/maps/world1.txt"s);
	levels.push_back("../assets/maps/world2.txt"s);

	// Cargamos el nivel correspondiente
	actLevel--;
	Mario = nullptr;
	Background = nullptr;
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

void
// Comprueba qué objetos del juego quedan visibles y los añade a la lista
PlayState::addVisibleObjects()
{
	// Borde derecho del mapa (más una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH * Game::TILE_SIDE + Game::TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->position().getX() < rightThreshold) {
		sceneObject* s = objectQueue[nextObject]->clone();
		addToSceneList(s);
		addObjects(s);
		nextObject++; 
	}
}
void PlayState::addToSceneList(sceneObject* h) {
	objects.push_back(h);
}

void
PlayState::update()
{
	// Comprueba si hay nuevos objetos que añadir
	addVisibleObjects();
	// Actualiza los objetos del juego
	GameState::update();
}

//Establece el máximo del nivel según el tamaño del TileMap
void PlayState::setMaxOffset(int max) {
	maxOffset = (max - Game::WIN_WIDTH - 1) * Game::TILE_SIDE;
}
int PlayState::getOffset() const {
	return mapOffset;
}
// Suma cierta cantidad al offset hasta llegar al máximo
void PlayState::offsetPlus(int plus) {
	mapOffset += plus;
	if (mapOffset >= maxOffset) mapOffset = maxOffset;
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
	mapOffset = 0;
	puntos = 0;
	for (sceneObject* obj : objects)
	{
		delete obj;
	}
	nextObject = 0;
	if (Mario != nullptr) {
		std::cout << "Puntos: " << puntos << " Vidas: " << Mario->getVidas() << endl;
		if (Mario->getVidas() == 0) end(false);
	}
}
// Carga el siguiente nivel (siempre que queden) y borra los objetos del nivel anterior para argar los del siguiente.
void PlayState::nextLevel() {
   	restartLevel();
    	actLevel++;
	if (actLevel >= levels.size()) end(true);
	else {
		
		for (sceneObject* obj : objectQueue) delete obj;
		objectQueue.clear();
		delete Background;
		Background = new TileMap(this, levelsTile[actLevel], game->getTexture(BACKGROUND));
		gameObjects.push_front(Background);
		
		loadObjectMap(levels[actLevel]);
	}

	std::cout << "Puntos: " << puntos << " Vidas: " << Mario->getVidas() << endl;
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
	ifstream objects;
	objects.open(file);
	if (!objects.is_open()) throw "File of objects not correctly open"s;

	objects >> color.R >> color.G >> color.B;
	objects.get();
	while (!objects.eof()) {
		string line;
		getline(objects, line);
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		// Uno para cada objeto de la lista
		switch (tipo) {
		case 'M':
			// Solo lee a Mario si no hay uno ya instanciado
			if (Mario == nullptr) {
				Mario = new Player(this, lineStream, game->getTexture(MARIO), game->getTexture(SUPERMARIO));
				addObjects(Mario);
				addEventListener(Mario);
			}
			break;
		case 'G':
			objectQueue.push_back(new Goomba(this, lineStream, game->getTexture(GOOMBA)));
			break;
		case 'K':
			objectQueue.push_back(new Koopa(this, lineStream, game->getTexture(KOOPA)));
			break;
		case 'B':
			objectQueue.push_back(new Block(this, lineStream, game->getTexture(BLOCK), game->getTexture(MUSHROOM)));
			break;
		case 'L':
			objectQueue.push_back(new Lift(this, lineStream, game->getTexture(LIFT)));
			break;
		case 'C':
			objectQueue.push_back(new Coin(this, lineStream, game->getTexture(COIN)));
			break;
		}
	}
	objects.close();
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
			if(target == Collision::PLAYER && Mario->getInv() && col.result == col.DAMAGE) hit = false;
		}
	}
	if (hit) return col;
	else return Background->hit(rect, target);
}
