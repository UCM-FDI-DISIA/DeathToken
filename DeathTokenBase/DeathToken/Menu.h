#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Marbles.h"
#include "Collision.h"

class Player;

class Menu : public GameState
{
	GameList<sceneObject> objetos;
	Player* ghost = nullptr;
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* peleas;
	Button* slots;
public:
	Menu(Game* game);
	void cambiaJuego(GameState* juego);
	void render() const override;
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
};

