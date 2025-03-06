#pragma once
#include "Baccarat.h"
class BaccaratBlackjack: public Baccarat
{
public:
	BaccaratBlackjack();
	void render() const override;
	void askCards();
	void bancaAI();
};

