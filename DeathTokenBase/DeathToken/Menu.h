#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Marbles.h"
#include "Peleas.h"
class Player;

class Menu : public GameState
{
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
};

