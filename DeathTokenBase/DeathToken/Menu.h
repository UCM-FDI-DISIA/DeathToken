#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"

class Menu : public GameState
{
	Texture* texture;
	Button* baccarat;
	Button* canicas;
	Button* peleas;
	Button* slots;
public:
	Menu(Game* game);
	void cambiaJuego(GameState* juego);
	void render() const override;
};

