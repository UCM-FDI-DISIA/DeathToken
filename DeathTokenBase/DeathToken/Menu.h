#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Slots.h"
#include "SlotsLocura.h"
#include "Marbles.h"
#include "marblesInsanity.h"
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
	Mesa* _baccarat;
	Mesa* _marbles;
	Mesa* _fights;
	Mesa* _slots;
	vector<SDL_Rect> obstaculos;
	vector<SDL_Rect> juegos;
	vector<Mesa*> games;

	HUDLobby* hud;
	SDL_Rect cambiarColisiones(SDL_Rect);
public:
	Menu(Game* game);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
	vector<SDL_Rect> getLimits() const { return obstaculos; };
};

