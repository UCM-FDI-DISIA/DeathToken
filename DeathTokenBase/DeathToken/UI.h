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
	virtual void OnInfo() {};
	virtual void OnRepeat() {};
	

public:
	UIChips(GameState* gS, Game* game);
};
class Slots;
class UISlots : public UI
{
protected:
	Slots* slots;
	ButtonUI* x2;
	ButtonUI* x3;
	ButtonUI* x5;
	ButtonUI* info;
public:
	UISlots(GameState*, Game*, Slots*);
	void OnGo() override;
	void Onx2();
	void Onx3();
	void Onx5();
	void OnInfo();
};
class Marbles;
class UIMarbles :public   UIChips{
	Marbles* marbles;
	std::vector<ButtonBet*> bets;
public:
	UIMarbles(GameState* gS, Game* game, Marbles* marbles);

	void OnGo() override;
	void OnErase() override;
	void OnRepeat() override;
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
};

class Peleas;
//class UIPeleas : public UIChips {
//public:
//	UIPeleas(Game* game, Peleas* peleas) : UIChips(peleas,game) 
//	{
//		
//	};
//
//	void OnGo() override;
//	void OnErase() override;
//	void OnRepeat() override;
//
//protected:
//	ButtonUI* autoText;
//	ButtonUI* historial;
//};
