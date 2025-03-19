#include "BaccaratBet.h"

void BaccaratBet::repeat() {
	for (int i = 0; i < betsHistory.size(); i++)
		bets[i] = { betsHistory[i].moneyBet * 2, betsHistory[i].moneyBet * 2 };
	for (auto i : bacButtons)
	{
		i->repeat();
	}
}
