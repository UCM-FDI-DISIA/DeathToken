#pragma once
#include "Baccarat.h"
class BaccaratBet : public Baccarat
{
	Button* bet;
	Button* stop;
	bool buttonsOn = false;
public:
	BaccaratBet(Game* game) : Baccarat(game) {};
	void acumulate();
	void repeatBet();
	void update() override;
};

