#pragma once
#include "gameState.h"
#include "button.h"
#include "ui.h"
#include "dialogueBox.h"
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
class Menu;
class EscenaTutorial : public GameState {
protected:
	long long bet;
	int a;
	int index;
	int fases;
	bool picked;
	bool startGame;
	bool hasChip;
	bool resultado;
	bool inState;
	bool dialog;
	float counter;

private:

	UI* _ui;
	HUDBet* _hud;
	int saldo;
	ButtonBet* _bet;
	Game* _g;	

	DialogueBox* _dialog1;
	DialogueBox* _dialog2;
	DialogueBox* _dialog3;
	DialogueBox* _dialog4;
	DialogueBox* _dialog5;
	DialogueBox* _dialog6;

public:
	EscenaTutorial(Game*);
	~EscenaTutorial();
	void update() override;
	void render() const override;
	inline void clear() {
		_bet->clear();
		PlayerEconomy::setBet(0);
		HUDManager::getHudBet()->refresh();
	}

	void inDialog() { dialog = true; };
	void outDialog() { dialog = false; };
	bool itIsInDIalog() const { return dialog; };
	inline void setBetTurno(long long n) { bet = n; }
	void iniciaJuego() { startGame = true; };
	void setIndex(int i) { index = i; };
	int getFase() { return fases; };
	void apuesta() { hasChip = true; };
	int getSaldo() const { return saldo; }

	void showDialog1() const;
	void showDialog2() const;
	void showDialog3() const;
	void showDialog4() const;
	void showDialog5() const;
	void showDialog6() const;

};