#pragma once
#include <cstdlib>
#include <vector>
#include <map>
#include "gameState.h"
#include "UI.h"
#include "Texture.h"
#include "EventHandler.h"
#include "Button.h"
#include "Cards.h"
using namespace std;

struct Mat {
	vector<int> banker;
	vector<int> player;
};

class Baccarat : public GameState, public EventHandler
{
protected:
	struct Bet {
		int multiplier = 0;
		int moneyBet = 0;
	};
	UIBaccarat* ui;

	std::map<int, Bet> bets;
	std::map<int, Bet> betsHistory;
	std::vector<ButtonBaccarat*> bacButtons;
	int moneyBet;

	Cards* player1;
	Cards* player2;
	Cards* player3;
	Cards* banker1;
	Cards* banker2;
	Cards* banker3;
	Texture* texture;
	Mat mat;
	vector<int> cardsVec;
	int rndNum;
	int playerComb;
	int bankerComb;
	const int xTwo = 2;
	const int xEight = 8;
	int clave = 0;//para verla apuesta que es
	//bool locura; global?
public:
	Baccarat(Game* game);

	void handleEvent(const SDL_Event& event) override;
	void clearDeck();
	void update() override;
	void render() const override;
	void handCards();
	void handThird();
	void bankThird();
	int generateRnd();


	void createMarbleButton(int x, int y, int width, int height, int type);
	void newBet(int multiplier, int moneyBet, ButtonBaccarat* btnBaccarat);
	void clearBets();
	void repeat();
	void startRound();
};