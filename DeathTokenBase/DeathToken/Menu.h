#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "BaccaratBlackjack.h"
#include "BaccaratFlip.h"
#include "Slots.h"
#include "Marbles.h"
#include "Collision.h"
#include "SceneObject.h"
#include <list>

class Player;

class Menu : public GameState
{
	list<sceneObject*> objetos;
	Player* ghost = nullptr;
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* fights;
	Button* slots;
public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
};

