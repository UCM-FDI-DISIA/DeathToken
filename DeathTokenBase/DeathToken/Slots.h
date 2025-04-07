#pragma once
#include "gameState.h"
#include "ui.h"

class Slots : public GameState {
protected:
	virtual int getResult() = 0;
	int bet;
	std::vector<int> multiplicadores = { 2,3,5,10,50,80,150 };

	UISlots* ui;

	HUDBet* hud;
public:
	inline Slots(Game* g) : GameState(g), ui(new UISlots(this, g, this)), hud(new HUDBet(this)), bet(0)
		{ HUDManager::getHudBet()->refresh(); }
	virtual void iniciarGiro() = 0;
	inline void setBetTurno(int n) { bet = n; }
};