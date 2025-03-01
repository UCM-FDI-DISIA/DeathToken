#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
#include "Baccarat.h"
#include "Marbles.h"
class Player;

class Menu : public GameState
{
	Player* ghost = nullptr;
	Texture* texture;
	Button* baccarat;
	Button* marbles;
	Button* figths;
	Button* slots;
public:
	Menu(Game* game);
	void gameChanger(GameState* game);
	void render() const override;
};

