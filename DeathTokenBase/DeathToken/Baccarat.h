#pragma once
#include <cstdlib>
#include <vector>
#include "gameState.h"
#include "Texture.h"
#include "EventHandler.h"
#include "Cards.h"
using namespace std;
struct Mat {
	vector<int> banker;
	vector<int> player;
};

class Baccarat : public GameState, public EventHandler
{
protected:
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
};