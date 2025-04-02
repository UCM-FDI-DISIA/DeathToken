#pragma once
#include "gameState.h"
#include "UI.h"

class Slots : public GameState {
protected:
	virtual int getResult() = 0;

	UISlots* ui;

	HUDBet* hud;
public:
	inline Slots(Game* g) : GameState(g), ui(new UISlots(this, g, this)), hud(new HUDBet(this))
		{ HUDManager::getHudBet()->refresh(); }
	virtual void iniciarGiro() = 0;
};