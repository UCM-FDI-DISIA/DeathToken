#pragma once
class HUD;

class PlayerEconomy
{
private:
	static long long blueSouls;
	static long long redSouls;
	static int insanity;
	static long long bet;
public:
	static void EconomyInitialize(bool savedGame = false);
	//Getters
	static long long getBlueSouls();
	static long long getRedSouls();
	static int getInsanity();
	static long long getBet();
	//Setters
	static void setBlueSouls(long long blueSouls);
	static void setRedSouls(long long redSouls);
	static void setInsanity(int insanity);
	static void setBet(long long bet);
	//Sumar
	static void addBlueSouls(long long blueSouls);
	static void addRedSouls(long long redSouls);
	static void addInsanity(int insanity);
	static void addBet(long long bet);
	//Restar
	static void subtractBlueSouls(long long blueSouls);
	static void subtractRedSouls(long long redSouls);
	static void subtractInsanity(int insanity);
	static void subtractBet(long long bet);

	friend HUD;
};

