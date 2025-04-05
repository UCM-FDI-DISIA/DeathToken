#pragma once
#include "Baccarat.h"
#include "Button.h"
#include "Collision.h"
#include "GameState.h"
#include "Marbles.h"
#include "Peleas.h"
#include "SceneObject.h"
#include "Slots.h"
#include "BaccaratBlackjack.h"
#include "Texture.h"
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
	HUDLobby* hud;
	//Booleanos para activar el tutorial al entrar por primera vez al juego
	bool tutorialBaccarat = true;
	bool tutorialSlots = true;
	bool tutorialFights = true;
	bool tutorialMarbles = true;
	GameState* baccaratState;
public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
};

