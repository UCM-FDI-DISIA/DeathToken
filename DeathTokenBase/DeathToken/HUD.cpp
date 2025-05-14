#include "hud.h"

inline int
HUD::relativeX(const float& n)
{
	return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}
inline int
HUD::relativeY(const float& n)
{
	return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}
int HUD::getNumberSize(long long n)
{
	if (n <= 999999)
	{
		return 0;
	}
	else if (n <= 9999999999)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
int HUD::getNumberY(long long n)
{
	if (n <= 999999)
	{
		return 0;
	}
	else if (n <= 9999999999)
	{
		return 5;
	}
	else
	{
		return 10;
	}
}
HUD::HUD(GameState* gS) : GameObject(gS), gS(gS)
{
	gS->addObjectsUI(this);

	balanceDescText = new Text(gS, gS->getGame()->getTypo(GRAND_CASINO1), relativeX((float)1600.0f), relativeY((float)70.0f),
							   relativeX((float)3.0f), Text::DERECHA);
	balanceDescText->setMessage("SALDO");
	gS->addObjectsUI(balanceDescText);
	balanceText = new Text(gS, gS->getGame()->getTypo((TypoName)getNumberSize(balance)), relativeX((float)1870.0f), relativeY((float)70.0f + getNumberY(balance)),
						   relativeX((float)3.0f), Text::DERECHA);
	balanceText->setMessage(std::to_string(balance));
	gS->addObjectsUI(balanceText);
}
void
HUD::refresh()
{
	balanceText->setMessage(std::to_string(balance));
	balanceText->setPos(relativeX((float)1870), relativeY((float)70 + getNumberY(balance)));
	balanceText->setFont(gS->getGame()->getTypo((TypoName)getNumberSize(balance)));;
	balanceText->render();
}

HUDLobby::HUDLobby(GameState* gS) : HUD(gS)
{
	redSoulsDescText = new Text(gS, gS->getGame()->getTypo(GRAND_CASINO1), relativeX((float)1600), relativeY((float)150),
								relativeX((float)3), Text::DERECHA);
	redSoulsDescText->setMessage("ALMAS");
	gS->addObjectsUI(redSoulsDescText);
	redSoulsText = new Text(gS, gS->getGame()->getTypo((TypoName)getNumberSize(redSouls)), relativeX((float)1870), relativeY((float)150 + getNumberY(redSouls)),
							relativeX((float)3), Text::DERECHA);
	redSoulsText->setMessage(std::to_string(redSouls));
	gS->addObjectsUI(redSoulsText);

	HUDManager::setHudLobby(this);
}
void
HUDLobby::refresh()
{
	HUD::refresh();
	redSoulsText->setMessage(std::to_string(redSouls));
	redSoulsText->setPos(relativeX((float)1870), relativeY((float)150 + getNumberY(redSouls)));
	redSoulsText->setFont(gS->getGame()->getTypo((TypoName)getNumberSize(redSouls)));;
	redSoulsText->render();
}

HUDBet::HUDBet(GameState* gS) : HUD(gS)
{
 	betDescText = new Text(gS, gS->getGame()->getTypo(GRAND_CASINO1), relativeX((float)1600), relativeY((float)150),
						   relativeX((float)3), Text::DERECHA);
	betDescText->setMessage("APUESTA");
	gS->addObjectsUI(betDescText);
	betText = new Text(gS, gS->getGame()->getTypo((TypoName)getNumberSize(bet)), relativeX((float)1870), relativeY((float)150 + getNumberY(bet)),
					   relativeX((float)3), Text::DERECHA);
	betText->setMessage(std::to_string(bet));
	gS->addObjectsUI(betText);

	HUDManager::setHudBet(this);
}
void
HUDBet::refresh()
{
	HUD::refresh();
	betText->setMessage(std::to_string(bet));
	betText->setPos(relativeX((float)1870), relativeY((float)150 + getNumberY(bet)));
	betText->setFont(gS->getGame()->getTypo((TypoName)getNumberSize(bet)));
	betText->render();
}

HUDBet* HUDManager::currentHudBet = nullptr;
HUDLobby* HUDManager::currentHudLobby = nullptr;
bool HUDManager::rouletteSwitch = true;
void
HUDManager::applyBet(int bet)
{
	PlayerEconomy::addBet(bet);
	PlayerEconomy::subtractBlueSouls(bet);
	currentHudBet->refresh();
}
void HUDManager::resetBet()
{
	PlayerEconomy::addBlueSouls(PlayerEconomy::getBet());
	PlayerEconomy::setBet(0);
	if (!rouletteSwitch)
		currentHudBet->refresh();
	else
		currentHudLobby->refresh();
}
void
HUDManager::applyWinBet(long long win)
{
	PlayerEconomy::addBlueSouls(win);
	PlayerEconomy::setBet(0);
	currentHudBet->refresh();
}

void HUDManager::popGame()
{
	HUDManager::resetBet();
	currentHudLobby->refresh();
}
