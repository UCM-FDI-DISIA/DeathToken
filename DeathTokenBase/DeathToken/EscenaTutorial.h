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
	float counter;
	UI* _ui;
	HUDBet* _hud;
	PlayerEconomy* eco;
	ButtonBet* _bet;
	DialogueBox* _dialog;
	Game* _g;
public:
	EscenaTutorial(Game*);
	~EscenaTutorial();
	void update() override;
	void render() const override;
	inline void setBetTurno(long long n) { bet = n; }
	void iniciaJuego() { startGame = true; };
	void setIndex(int i) { index = i; };
	void apuesta() { hasChip = true; };
	inline void clear() {
		bet = 0;
		_bet->clear();
		PlayerEconomy::setBet(0);
		HUDManager::getHudBet()->refresh();
	}
};