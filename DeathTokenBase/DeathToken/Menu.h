#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "CrazyBaccaratManager.h"
#include "BaccaratBlackjack.h"
#include "BaccaratBet.h"
#include "SlotsNormal.h"
#include "SlotsLocura.h"
#include "Marbles.h"
#include "Collision.h"
#include "SceneObject.h"
#include "RouletteScene.h"
#include "marblesInsanity.h"
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
	Button* roulette;
	//Booleanos para activar el tutorial al entrar por primera vez al juego
	bool tutorialBaccarat = true;
	bool tutorialSlots = true;
	bool tutorialFights = true;
	bool tutorialMarbles = true;
	GameState* baccaratState;

	HUDLobby* hud;
	PlayerEconomy* eco;
public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
};

