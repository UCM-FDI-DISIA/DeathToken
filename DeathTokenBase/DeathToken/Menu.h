﻿#pragma once
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
#include "mesa.h"
#include <list>

class Player;

class Menu : public GameState
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
	bool tutorialSlotsLocura = true;
	bool tutorialFights = true;
	bool tutorialMarbles = true;
	GameState* baccaratState;
	GameState* slotsState;
	GameState* marbleState;
	GameState* peleasState;
	vector<SDL_Rect> obstaculos;
	vector<Mesa*> juegos;

	HUDLobby* hud;
	PlayerEconomy* eco;

	SDL_Rect cambiarColisiones(SDL_Rect);
public:
	Menu(Game* game);
	virtual ~Menu();
	GameState* gameSelec(int id);
	void OnEnter();
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button

};

