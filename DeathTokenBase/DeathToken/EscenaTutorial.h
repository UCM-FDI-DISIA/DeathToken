#pragma once
#include "gameState.h"
#include "Button.h"
#include "ui.h"
#include "DialogueBox.h"
#include <SDL_ttf.h>
using namespace std;
class Menu;
class EscenaTutorial : public GameState {
private:
	long long bet;
	int index;
	int fases;
	vector<Texture*> flechas;
	bool picked;
	bool startGame;
	UI* _ui;
	HUDBet* _hud;
	PlayerEconomy* eco;
	ButtonBet* _bet;
	DialogueBox* _dialog;
public:
	EscenaTutorial(Game*);
	~EscenaTutorial();
	void update() override;
	void render() const override;
	inline void setBetTurno(long long n) { bet = n; }
	void iniciaJuego() { startGame = true; };
	void setIndex(int i) { index = i; };
	inline void clear() {
		bet = 0;
		_bet->clear();
		PlayerEconomy::setBet(0);
		HUDManager::getHudBet()->refresh();
	}
};