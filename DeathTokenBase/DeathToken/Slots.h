#pragma once
#include "gameState.h"
#include "Button.h"
#include "ui.h"

class Slots : public GameState {
protected:
	virtual int getResult() = 0;
	long long bet;
	std::vector<int> multiplicadores = { 2,3,5,10,50,80,120 };
	ButtonSlots* btnBet;

	UISlots* ui;

	HUDBet* hud;
public:
	inline Slots(Game* g) : GameState(g), ui(new UISlots(this, g, this)), hud(new HUDBet(this)), bet(0), btnBet()
		{ hud->refresh(); }
	virtual void iniciarGiro() = 0;
	inline void setBetTurno(long long n) { bet = n; }
	inline void clear() {
		btnBet->clear();
		PlayerEconomy::setBet(0);
		hud->refresh();
	}
	inline virtual void showTutorial() override { ui->OnInfo(); }
};