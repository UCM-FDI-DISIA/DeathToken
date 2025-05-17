#pragma once
#include "texture.h"
#include "gameState.h"
#include "button.h"
#include "text.h"
#include <vector>
class Player;
class UI
{
protected:
	GameState* gS;
	Game* game;
	ButtonUI* exit;
	ButtonUI* go;
	bool onBet;

	ButtonUI* arrowL;
	ButtonUI* arrowR;
	int chipPage;
	std::vector<ButtonChip*> chips;
	int chipOnUse;
	void OnArrow(const bool& left);
public:
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	bool getOnBet() { return onBet; };
	void setOnBet(bool onBet) { this->onBet = onBet; };
	UI(GameState* g, Game* game);
	virtual ~UI() = default;
	void changeChip(const int& id);
	int currentChipValue();

	void OnExit();
	virtual void OnGo() = 0;
};

class UIChips : public UI
{
protected:
	ButtonUI* erase;
	ButtonUI* info;
	ButtonUI* repeat;

	virtual void OnErase() {};
	virtual void OnRepeat() {};
	virtual void OnInfo() {};


public:
	UIChips(GameState* gS, Game* game);
	virtual ~UIChips() = default;
};
class Slots;
class UISlots : public UI
{
protected:
	Slots* slots;
	ButtonUI* erase;
	ButtonUI* info;
	std::vector<ButtonBet*> bets;
public:
	UISlots(GameState*, Game*, Slots*);
	void OnGo() override;
	void OnErase();
	void OnInfo();
};
class Marbles;
class UIMarbles :public   UIChips {
	Marbles* marbles;
	std::vector<ButtonBet*> bets;
public:
	UIMarbles(GameState* gS, Game* game, Marbles* marbles);

	void OnGo() override;
	void OnErase() override;
	void OnRepeat() override;
	void OnInfo() override;
};


class MarblesInsanity;
class UIMarblesInsanity : public UIChips {
	MarblesInsanity* marblesI;
public:
	UIMarblesInsanity(GameState* gS, Game* game, MarblesInsanity* marbles);
	~UIMarblesInsanity() override = default;
	void OnGo() override;
	void render() const;
	void update();
	void OnInfo() override;
};


class Baccarat;
class UIBaccarat :public   UIChips {
	Baccarat* baccarat;
	std::vector<ButtonBet*> bets;
public:
	UIBaccarat(GameState* gS, Game* game, Baccarat* baccarat);

	void OnGo() override;
	void OnErase() override;
	void OnRepeat() override;
	void OnInfo() override;
};

class RouletteScene;
class UIRoulette {
protected:
	GameState* gS;
	RouletteScene* rouletteS;
	Game* game;
	ButtonUI* exit;
	ButtonUI* go;

public:
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	UIRoulette(GameState* g, Game* game, RouletteScene* rouletteS);

	void OnExit();
	void OnGo();
};

class rouletteChoose;
class UIRouletteChoose {
protected:
	GameState* gS;
	rouletteChoose* rouletteC;
	Game* game;
	ButtonUI* exit;

public:
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	UIRouletteChoose(GameState* g, Game* game, rouletteChoose* rouletteC);

	void OnExit();
};

class scythe;
class UIScythe {
protected:
	GameState* gS;
	scythe* s;
	Game* game;
	ButtonUI* exit;

public:
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	UIScythe(GameState* g, Game* game, scythe* s);

	void OnExit();
};

class UITutorial
{
protected:
	GameState* gS;
	Game* game;
	ButtonUI* exit;
	size_t totalPages;//pags totales tuto
	bool arrow = false;
public:
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);

	UITutorial(GameState* gS, Game* game, size_t tam);
	void OnExit();
	ButtonUI* downArrow();
	ButtonUI* upArrow();
};

class Peleas;
class UIPeleas : public UI {
public:
	UIPeleas(Game* game, Peleas* peleas)
		: UI((GameState*)peleas, game)
		, _peleas(peleas)
		, autoText(nullptr)
		, historial(nullptr)
	{
	};

	void OnGo() override;

protected:
	Peleas* _peleas;
	ButtonUI* autoText;
	ButtonUI* historial;
};

class EscenaTutorial;
class UIEscenaTutorial :public UI {
protected:
	EscenaTutorial* escenaTutorial;
	std::vector<ButtonBet*> bets;
public:
	UIEscenaTutorial(GameState* gS, Game* g, EscenaTutorial* tut);
	void OnGo() override;
};