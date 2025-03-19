#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Slots.h"
#include "Marbles.h"
#include "Collision.h"
#include "SceneObject.h"

class Player;

class Menu : public GameState
{
	GameList<sceneObject> objetos;
	Player* ghost = nullptr;
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* fights;
	Button* slots;
	SDL_Rect boundry1;
	SDL_Rect boundry2;
	SDL_Rect boundry3;
	vector<SDL_Rect> limites;

public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
	void update() override;
	void handleEvent(const SDL_Event& event);//para colisiones con button
	vector<SDL_Rect> getLimits() const { return limites; };
};

