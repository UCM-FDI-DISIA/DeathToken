#pragma once
#include "Baccarat.h"
class BaccaratBet : public Baccarat
{
public:
	BaccaratBet(Game* game) : Baccarat(game) {};
	void repeat() override;
};

