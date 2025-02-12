#include "GameState.h"

GameState::~GameState() {
	for (GameObject* object : gameObjects)
		delete object;
}
void GameState::update() {
	for ( GameObject* object : gameObjects)
		object->update();
}
void GameState::render() const {
	for (const GameObject* object : gameObjects)
		object->render();
}
void GameState::handleEvent(const SDL_Event& event) {
	for (EventHandler* handler : eventHandlers)
		handler->handleEvent(event);
}
void GameState::addEventListener(EventHandler* obj) {
	eventHandlers.push_back(obj);
}
void GameState::addObjects(GameObject* obj) {
	gameObjects.push_back(obj);
}