#pragma once
#include "Button.h"
#include "Cards.h"
#include "EventHandler.h"
#include "gameState.h"
#include "Texture.h"
#include "UI.h"
#include <cstdlib>
#include <map>
#include <vector>
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

	Card* player1;
	Card* player2;
	Card* player3;
	Card* banker1;
	Card* banker2;
	Card* banker3;
	Texture* texture;
	Mat mat;
	vector<int> cardsVec;
	HUDBet* hud;
	int rndNum;
	int playerComb = 0;
	int bankerComb = 0;
	const int xTwo = 2;
	const int xEight = 8;
	int clave = 0;//para verla apuesta que es
	//bool locura; global?
public:
	bool hasWon = false;
	Baccarat(Game* game, bool bJ = false);
	virtual ~Baccarat() {
		HUDManager::popGame();
		delete ui;  // Elimina la interfaz solo si fue creada din�micamente
		ui = nullptr;  // Evita accesos a memoria liberada

		//for (auto& b : bacButtons) {
		//	delete b;  // Libera cada bot�n
		//}

	};
	void handleEvent(const SDL_Event& event) override;
	virtual void clearDeck();
	void update() override;
	void render() const override;
	virtual void handCards();
	void handThird();
	void bankThird();
	int generateRnd();
	Card* createCard(int a, int b, int rot, int frame);
	void addCards();
	void win();

	//metodos apuestas
	void createBaccaratButton(int x, int y, int width, int height, int multiplier);
	void newBet(int multiplier, int moneyBet, ButtonBaccarat* btnBaccarat);
	void clearBets();
	void repeat();
	virtual void startRound();
};