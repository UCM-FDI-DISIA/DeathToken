#pragma once
#include "gameState.h"
#include "Button.h"
#include "ui.h"
#include "DialogueBox.h"
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
class Menu;
class EscenaTutorial : public GameState {
private:
	long long bet;
	int index;
	int fases;
	bool picked;
	bool startGame;
	bool hasChip;
	bool resultado;
	bool inDialog;
	bool inState;
	float counter;
	UI* _ui;
	HUDBet* _hud;
	PlayerEconomy* eco;
	ButtonBet* _bet;
	DialogueBox* _dialog;
	Game* _g;
		int a;
public:
	EscenaTutorial(Game*);
	~EscenaTutorial();
	void update() override;
	void render() const override;
	inline void setBetTurno(long long n) { bet = n; }
	void iniciaJuego() { startGame = true; };
	void setIndex(int i) { index = i; };
	int getFase() { return fases; };
	void apuesta() { hasChip = true; };
	inline void clear() {
		bet = 0;
		_bet->clear();
		PlayerEconomy::setBet(0);
		HUDManager::getHudBet()->refresh();
	}
	void fase0(uint);
	void fase1(uint);
	void fase2(uint);
	void fase3(uint);
	void fase4(uint);
	void fase5(uint);
};