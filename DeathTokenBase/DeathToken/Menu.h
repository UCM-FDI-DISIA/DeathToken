#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Marbles.h"

class Menu : public GameState
{
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* peleas;
	Button* slots;
public:
	Menu(Game* game);
	void cambiaJuego(GameState* juego);
	void render() const override;
};

