#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "BaccaratBlackjack.h"
#include "BaccaratBet.h"
#include "Slots.h"
#include "SlotsLocura.h"
#include "Marbles.h"
#include "Collision.h"
#include "SceneObject.h"
#include "Mesa.h"
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
	//Mesa<Slots,SlotsLocura>* slots;
	Mesa* _slots;
	SDL_Rect boundry1;
	SDL_Rect boundry2;
	SDL_Rect boundry3;
	vector<SDL_Rect> limites;

	HUDLobby* hud;
public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
	vector<SDL_Rect> getLimits() const { return limites; };
};

