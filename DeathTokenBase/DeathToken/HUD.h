#pragma once
#include "text.h"
#include "texture.h"
#include "playerEconomy.h"
#include "game.h"

class HUD : public GameObject
{
protected:
	GameState* gS;
	long long& balance = PlayerEconomy::blueSouls;
	long long& redSouls = PlayerEconomy::redSouls;
	long long& bet = PlayerEconomy::bet;
	int& insanity = PlayerEconomy::insanity;
	Text* balanceDescText;
	Text* balanceText;
	Texture* insanityFrameW;
	Texture* insanityFrameY;
	Texture* insanitySlot;
	SDL_Rect insanityRectsH[10u];
	SDL_Rect insanityRectsV[10u];
	inline int relativeX(const float& n);
	inline int relativeY(const float& n);
	int getNumberSize(long long n);
	int getNumberY(long long n);
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
	HUDLobby(GameState* gS, bool roulette);
	void refresh() override;
	void render() const override;
};

class HUDBet : public HUD
{
private:
	Text* betDescText;
	Text* betText;
	bool verticalInsanity;
public:
	HUDBet(GameState* gS, bool verticalInsanity);
	void refresh() override;
	void render() const override;
};

class HUDManager
{
private:
	static HUDBet* currentHudBet;
	static HUDLobby* currentHudLobby;
	static bool rouletteSwitch;
public:
	static HUDBet* getHudBet() { return currentHudBet; };
	static void setHudBet(HUDBet* hudBet) { currentHudBet = hudBet; };
	static HUDLobby* getHudLobby() { return currentHudLobby; };
	static void setHudLobby(HUDLobby* hudLobby, bool roulette) {
		currentHudLobby = hudLobby;
		rouletteSwitch = roulette;
	};
	static void applyBet(int bet);
	static void resetBet();
	static void applyWinBet(long long win);
	static void popGame();
	static bool getRouletteSwitch() { return rouletteSwitch; };
};
