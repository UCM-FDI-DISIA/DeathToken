#include "firebaseUtils.h"
#include "playerEconomy.h"
#include "HUD.h"

//Inicialización máquina
long long PlayerEconomy::blueSouls = 0;
long long PlayerEconomy::redSouls = 0;
int PlayerEconomy::insanity = 0;
long long PlayerEconomy::bet = 0;
//Inicialización funcional
void
PlayerEconomy::EconomyInitialize(bool savedGame)
{
	if (!savedGame)
	{
		blueSouls = FirebaseUtils::chips;
		redSouls = FirebaseUtils::souls;
		insanity = FirebaseUtils::insanity;
		bet = 0;
	}
}
long long
PlayerEconomy::getBlueSouls()
{
	return blueSouls;
}
long long
PlayerEconomy::getRedSouls()
{
	return redSouls;
}
int
PlayerEconomy::getInsanity()
{
	return insanity;
}
long long
PlayerEconomy::getBet()
{
	return bet;
}
void
PlayerEconomy::setBlueSouls(long long blueSouls)
{
	PlayerEconomy::blueSouls = blueSouls;
}
void
PlayerEconomy::setRedSouls(long long redSouls)
{
	PlayerEconomy::redSouls = redSouls;
}
void PlayerEconomy::setInsanity(int insanity)
{
	PlayerEconomy::insanity = insanity;
}
void PlayerEconomy::setBet(long long bet)
{
	PlayerEconomy::bet = bet;
}
void
PlayerEconomy::addBlueSouls(long long blueSouls)
{
	PlayerEconomy::blueSouls += blueSouls;
}
void
PlayerEconomy::addRedSouls(long long redSouls)
{
	PlayerEconomy::redSouls += redSouls;
}
void
PlayerEconomy::addInsanity(int insanity)
{
	PlayerEconomy::insanity += insanity;
}
void
PlayerEconomy::addBet(long long bet)
{
	PlayerEconomy::bet += bet;
}
void
PlayerEconomy::subtractBlueSouls(long long blueSouls)
{
	PlayerEconomy::blueSouls -= blueSouls;
}
void
PlayerEconomy::subtractRedSouls(long long redSouls)
{
	PlayerEconomy::redSouls -= redSouls;
}
void
PlayerEconomy::subtractInsanity(int insanity)
{
	PlayerEconomy::insanity -= insanity;
}
void
PlayerEconomy::subtractBet(long long bet)
{
	PlayerEconomy::bet -= bet;
}

