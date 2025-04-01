#pragma once
#include "Text.h"
#include "PlayerEconomy.h"
#include "Game.h"

class HUD : public GameObject
{
protected:
	const char* typo;
	long long& balance = PlayerEconomy::blueSouls;
	long long& redSouls = PlayerEconomy::redSouls;
	long long& bet = PlayerEconomy::bet;
	Text* balanceDescText;
	Text* balanceText;
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	long long getNumberSize(long long n);
	long long getNumberY(long long n);
public:
	HUD(GameState* gS);
	virtual void refresh();
	void update() override {};
	void render() const override {};
};

class HUDLobby : public HUD
{
private:
	Text* redSoulsDescText;
	Text* redSoulsText;
public:
	HUDLobby(GameState* gS);
	void refresh() override;
};

class HUDBet : public HUD
{
private:
	Text* betDescText;
	Text* betText;
public:
	HUDBet(GameState* gS);
	void refresh() override;
};

class HUDManager
{
private:
	static HUDBet* currentHudBet;
	static HUDLobby* currentHudLobby;
public:
	static HUDBet* getHudBet() { return currentHudBet; };
	static void setHudBet(HUDBet* hudBet) { currentHudBet = hudBet; };
	static HUDLobby* getHudLobby() { return currentHudLobby; };
	static void setHudLobby(HUDLobby* hudLobby) { currentHudLobby = hudLobby; };
	static void applyBet(int bet);
	static void resetBet();
	static void applyWinBet(long long win);
	static void popGame();
};
