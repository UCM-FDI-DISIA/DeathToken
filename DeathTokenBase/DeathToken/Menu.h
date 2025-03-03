#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Slots.h"
#include "Marbles.h"
class Player;

class Menu : public GameState
{
	Player* ghost = nullptr;
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* fights;
	Button* slots;
public:
	Menu(Game* game);
	void gameChanger(GameState* juego);
	void render() const override;
};

