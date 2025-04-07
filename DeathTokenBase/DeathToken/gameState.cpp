#include "GameState.h"

GameState::~GameState() {
	for (GameObject* object : gameObjects)
		delete object;
	for (GameObject* object : gameObjectsUI)
		delete object;
}
void GameState::update() {
	for (GameObject* object : gameObjects)
		object->update();
	for (GameObject* object : gameObjectsUI)
		object->update();
}
void GameState::render() const {
	for (const GameObject* object : gameObjects)
		object->render();
	for (const GameObject* object : gameObjectsUI)
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
void GameState::addObjectsUI(GameObject* obj) {
	gameObjectsUI.push_back(obj);
}