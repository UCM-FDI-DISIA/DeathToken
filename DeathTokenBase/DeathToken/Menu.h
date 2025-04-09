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
#include "rouletteScene.h"
#include "marblesInsanity.h"
#include "peleas.h"
#include <list>

class Player;

class Menu : public GameState
{
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
	virtual ~Menu() { delete eco; };
	void gameChanger(GameState* juego);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
};

