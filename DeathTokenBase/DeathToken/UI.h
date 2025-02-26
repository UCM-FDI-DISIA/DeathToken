#pragma once
#include "Texture.h"
#include "GameState.h"
#include "Button.h"
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
	UI(GameState* g, Game* game);

	void changeChip(const int& id);
	
	void OnExit();
	virtual void OnGo() {};
};

class UIChips : public UI
{
protected:
	ButtonUI* erase;
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

