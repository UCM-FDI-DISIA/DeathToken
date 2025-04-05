#pragma once

#include "gameState.h"
#include "vector"
#include "Texture.h"
#include "Button.h"
#include "Game.h"
#include "UI.h"
#include "Award.h"
#include <map>
class Marbles : public GameState
{
protected:
	struct Bet {
		std::vector<int> typeOfBet;
		int multiplier= 0;
		int moneyBet= 0;
	};
	UIMarbles*  ui;
	HUDBet* hud;

	Texture* texture;
	std::vector<int> marbles;
	std::map<int, Bet> bets;
	std::map<int, Bet> betsHistory;
	std::vector<Texture*> RMarbles;
	std::vector<std::pair<Texture*, SDL_Rect>> drawnMarbles;
	std::vector<ButtonMarbles*> marbleButtons;
	bool play = false;
	long long moneyBet;
	long long turnMoneyBet;
	int clave = 0;

	bool bInsanity;
	std::vector<int> blockedMarble;

	double PosPW1 = (118.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH1 = (118.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW3 = (302.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH3 = (102.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW2 = (166.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH2 = (83.0 / 1080.0) * Game::WIN_HEIGHT;
	double PosPW4 = (239.0 / 1920.0) * Game::WIN_WIDTH;
	double PosPH4 = (180.0 / 1080.0) * Game::WIN_HEIGHT;
	double marginW = (10.0 / 1920.0) * Game::WIN_WIDTH;
	double marginH = (10.0 / 1080.0) * Game::WIN_WIDTH;
public:
	Marbles(Game* game, std::vector<int> blockedMarble);
	virtual ~Marbles();
	void render() const override;
	void update() override;

	void  generateMarbles();
	int checkBets();
	void startRound();
	void createMarbleButton(int x, int y, int width, int height, Texture*, Texture*, int type, std::vector<int> NCMarbles);
	void marblesButtonCreation();
	void newBet(std::vector<int> typeOfBet, int multiplier, int moneyBet, ButtonMarbles* btnMarbles);
	void clearBets();
	void repeat();

	void setBlockedMarble(std::vector<int> blocked);
	//static std::vector<int> getBlockedMarble();
	bool getbInsanity();
	void setbInsanity(bool insanity);
};

