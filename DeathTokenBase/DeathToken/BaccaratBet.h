#pragma once
#include "Baccarat.h"
class BaccaratBet : public Baccarat
{
	Button* bet = nullptr;
	Button* stop = nullptr;
	bool buttonsOn = false;
public:
	BaccaratBet(Game* game) : Baccarat(game) {};
	void acumulate();
	void repeatBet();
	void update() override;
	void didntWin();
};

