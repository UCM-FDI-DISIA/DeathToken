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
	static void EconomyInitialize(bool savedFile = false);
	//Getters
	static int getBlueSouls();
	static int getRedSouls();
	static int getInsanity();
	static int getBet();
	//Setters
	static void setBlueSouls(int blueSouls);
	static void setRedSouls(int redSouls);
	static void setInsanity(int insanity);
	static void setBet(int bet);
	//Sumar
	static void addBlueSouls(int blueSouls);
	static void addRedSouls(int redSouls);
	static void addInsanity(int insanity);
	static void addBet(int bet);
	//Restar
	static void subtractBlueSouls(int blueSouls);
	static void subtractRedSouls(int redSouls);
	static void subtractInsanity(int insanity);
	static void subtractBet(int bet);

	friend HUD;
};

