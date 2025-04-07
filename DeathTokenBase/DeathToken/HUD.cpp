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
long long HUD::getNumberSize(long long n)
{
	if (n <= 999999)
	{
		return 50;
	}
	else if (n <= 9999999999)
	{
		return 40;
	}
	else
	{
		return 30;
	}
}
long long HUD::getNumberY(long long n)
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
HUD::HUD(GameState* gS) : GameObject(gS)
{
	gS->addObjectsUI(this);

	typo = gS->getGame()->getTypo(GRAND_CASINO);
	balanceDescText = new Text(gS, typo, relativeX(1600), relativeY(70),
							   relativeX(50), relativeX(3), Text::DERECHA);
	balanceDescText->setMessage("SALDO");
	gS->addObjectsUI(balanceDescText);
	balanceText = new Text(gS, typo, relativeX(1870), relativeY(70 + getNumberY(balance)),
						   relativeX(getNumberSize(balance)), relativeX(3), Text::DERECHA);
	balanceText->setMessage(std::to_string(balance));
	gS->addObjectsUI(balanceText);
}
void
HUD::refresh()
{
	balanceText->setMessage(std::to_string(balance));
	balanceText->setPos(relativeX(1870), relativeY(70 + getNumberY(balance)));
	balanceText->setSize(getNumberSize(balance));
	balanceText->render();
}

HUDLobby::HUDLobby(GameState* gS) : HUD(gS)
{
	redSoulsDescText = new Text(gS, typo, relativeX(1600), relativeY(150),
								relativeX(50), relativeX(3), Text::DERECHA);
	redSoulsDescText->setMessage("ALMAS");
	gS->addObjectsUI(redSoulsDescText);
	redSoulsText = new Text(gS, typo, relativeX(1870), relativeY(150 + getNumberY(redSouls)),
							relativeX(getNumberSize(redSouls)), relativeX(3), Text::DERECHA);
	redSoulsText->setMessage(std::to_string(redSouls));
	gS->addObjectsUI(redSoulsText);

	HUDManager::setHudLobby(this);
}
void
HUDLobby::refresh()
{
	HUD::refresh();
	redSoulsText->setMessage(std::to_string(redSouls));
	redSoulsText->setPos(relativeX(1870), relativeY(150 + getNumberY(redSouls)));
	redSoulsText->setSize(getNumberSize(redSouls));
	redSoulsText->render();
}

HUDBet::HUDBet(GameState* gS) : HUD(gS)
{
	betDescText = new Text(gS, typo, relativeX(1600), relativeY(150),
		relativeX(50), relativeX(3), Text::DERECHA);
	betDescText->setMessage("APUESTA");
	gS->addObjectsUI(betDescText);
	betText = new Text(gS, typo, relativeX(1870), relativeY(150 + getNumberY(bet)),
		relativeX(getNumberSize(bet)), relativeX(3), Text::DERECHA);
	betText->setMessage(std::to_string(bet));
	gS->addObjectsUI(betText);

	HUDManager::setHudBet(this);
}
void
HUDBet::refresh()
{
	HUD::refresh();
	betText->setMessage(std::to_string(bet));
	betText->setPos(relativeX(1870), relativeY(150 + getNumberY(bet)));
	betText->setSize(getNumberSize(bet));
	betText->render();
}

HUDBet* HUDManager::currentHudBet = nullptr;
HUDLobby* HUDManager::currentHudLobby = nullptr;
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
	currentHudBet->refresh();
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
