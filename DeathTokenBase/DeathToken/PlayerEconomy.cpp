#include "PlayerEconomy.h"

//Inicialización máquina
long long PlayerEconomy::blueSouls = 0;
long long PlayerEconomy::redSouls = 0;
int PlayerEconomy::insanity = 0;
long long PlayerEconomy::bet = 0;
//Inicialización funcional
void
PlayerEconomy::EconomyInitialize(bool savedFile)
{
	if (!savedFile)
	{
		blueSouls = 2000;
		redSouls = 0;
		insanity = 0;
		bet = 0;
	}
	else
	{
		blueSouls = 2000;
		redSouls = 0;
		insanity = 0;
		bet = 0;
	}
}
int
PlayerEconomy::getBlueSouls()
{
	return blueSouls;
}
int
PlayerEconomy::getRedSouls()
{
	return redSouls;
}
int
PlayerEconomy::getInsanity()
{
	return insanity;
}
int
PlayerEconomy::getBet()
{
	return bet;
}
void
PlayerEconomy::setBlueSouls(int blueSouls)
{
	PlayerEconomy::blueSouls = blueSouls;
}
void
PlayerEconomy::setRedSouls(int redSouls)
{
	PlayerEconomy::redSouls = redSouls;
}
void PlayerEconomy::setInsanity(int insanity)
{
	PlayerEconomy::insanity = insanity;
}
void PlayerEconomy::setBet(int bet)
{
	PlayerEconomy::bet = bet;
}
void
PlayerEconomy::addBlueSouls(int blueSouls)
{
	PlayerEconomy::blueSouls += blueSouls;
}
void
PlayerEconomy::addRedSouls(int redSouls)
{
	PlayerEconomy::redSouls += redSouls;
}
void
PlayerEconomy::addInsanity(int insanity)
{
	PlayerEconomy::insanity += insanity;
}
void
PlayerEconomy::addBet(int bet)
{
	PlayerEconomy::bet += bet;
}
void
PlayerEconomy::subtractBlueSouls(int blueSouls)
{
	PlayerEconomy::blueSouls -= blueSouls;
}
void
PlayerEconomy::subtractRedSouls(int redSouls)
{
	PlayerEconomy::redSouls -= redSouls;
}
void
PlayerEconomy::subtractInsanity(int insanity)
{
	PlayerEconomy::insanity -= insanity;
}
void
PlayerEconomy::subtractBet(int bet)
{
	PlayerEconomy::bet -= bet;
}

