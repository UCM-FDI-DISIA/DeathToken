#pragma once
#include "texture.h"
#include "gameState.h"
#include "button.h"
#include "baccarat.h"
#include "baccaratInsanityManager.h"
#include "baccaratBlackjack.h"
#include "baccaratBet.h"
#include "slotsNormal.h"
#include "slotsInsanity.h"
#include "marbles.h"
#include "sceneObject.h"
#include "rouletteChoose.h"
#include "marblesInsanity.h"
#include "peleas.h"
#include "peleasInsanity.h"
#include "Mesa.h"
#include <list>

class Player;

class Menu : public GameState, EventHandler
{
	Player* ghost = nullptr;
	Texture* texture;
	Mesa* baccarat;
	Mesa* marbles;
	Mesa* fights;
	Mesa* slots;
	Mesa* roulette;
	//Booleanos para activar el tutorial al entrar por primera vez al juego
	bool tutorialBaccarat = true;
	bool tutorialSlots = true;
	bool tutorialFights = true;
	bool tutorialMarbles = true;
	GameState* baccaratState;
	vector<SDL_Rect> obstaculos;
	vector<Mesa*> juegos;
	GameState* marbleState;

	HUDLobby* hud;
	PlayerEconomy* eco;

	SDL_Rect cambiarColisiones(SDL_Rect);
public:
	Menu(Game* game);
	virtual ~Menu();
	void gameChanger(GameState* juego);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button

};

