#pragma once
#include "BarraVida.h"
#include "BattleManager.h"
#include "DialogueBox.h"
#include "gameState.h"
#include "UI.h"
#include <SDL_ttf.h>
enum class FSState { CARDS, FIGHT };
class Peleas : public GameState {
public:
	Peleas(Game* game);
	~Peleas()
	{
		delete ui;
		ui = nullptr;
		delete fighter1bar;
		fighter1bar = nullptr;
		delete fighter2bar;
		fighter2bar = nullptr;
		delete Apuesta2;
		Apuesta2 = nullptr;
		delete Apuesta1;
		Apuesta1 = nullptr;
		delete Animo2;
		Animo2 = nullptr;
		delete Animo2;
		Animo2 = nullptr;
		delete Animo1;
		Animo1 = nullptr;
		delete Cuota2;
		Cuota2 = nullptr;
		delete Cuota1;
		Cuota1 = nullptr;
		delete nombre2;
		nombre2 = nullptr;
		delete nombre1;
		nombre1 = nullptr;
		delete dialog;
		dialog = nullptr;
		delete _battleM;
		_battleM = nullptr;
	}
	void render() const override;
	void update() override;
	void StartBattle();
	inline BarraVida* getFighter1Bar() const { return fighter1bar; }
	inline BarraVida* getFighter2Bar() const { return fighter2bar; }

private:
	BattleManager* _battleM;
	DialogueBox* dialog;
	DialogueBox* nombre1;
	DialogueBox* nombre2;
	DialogueBox* Cuota1;
	DialogueBox* Cuota2;
	DialogueBox* Animo1;
	DialogueBox* Animo2;
	DialogueBox* Apuesta1;
	DialogueBox* Apuesta2;
	BarraVida* fighter1bar;
	BarraVida* fighter2bar;
	UIPeleas* ui;
	FSState state;
};
