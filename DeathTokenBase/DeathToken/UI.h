#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
class Player;

class UI
{
protected:
	GameState* gS;
	Game* game;
	ButtonUI* exit;
	ButtonUI* go;
	bool onBet;
public:
	inline int relativePosX(const float& n);
	inline int relativePosY(const float& n);
	UI(GameState* g, Game* game);
	
	void OnExit();
	virtual void OnGo() {};
};

class UIChips : public UI
{
protected:
	ButtonUI* erase;
	ButtonUI* arrowL;
	ButtonUI* arrowR;
	ButtonUI* info;
	ButtonUI* repeat;

	virtual void OnErase() {};
	virtual void OnInfo() {};
	virtual void OnRepeat() {};

public:
	UIChips(GameState* gS, Game* game);
};

class UISlots : public UI
{
protected:
	ButtonUI* x2;
	ButtonUI* x3;
	ButtonUI* x5;
	ButtonUI* info;

	void Onx2();
	void Onx3();
	void Onx5();
	void OnInfo();

public:
	UISlots(GameState* gS, Game* game);
};

