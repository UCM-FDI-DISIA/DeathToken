#pragma once
#include <cstdlib>
#include <vector>
#include <map>
#include "gameState.h"
#include "UI.h"
#include "Texture.h"
#include "EventHandler.h"
#include "Button.h"
#include "card.h"
#include "Award.h"
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
		int betType = 0;
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
	bool bankerBet = false, playerBet = false, tieBet = false;
	//bool locura; global?
public:
	Baccarat(Game* game);
	virtual ~Baccarat() {
		HUDManager::popGame();
		delete ui;  // Elimina la interfaz solo si fue creada dinámicamente
		ui = nullptr;  // Evita accesos a memoria liberada

		//for (auto& b : bacButtons) {
		//	delete b;  // Libera cada botón
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
	void createBaccaratButton(int x, int y, int width, int height, int multiplier, int betType);
	void newBet(int multiplier, int betType, ButtonBaccarat* btnBaccarat);
	void clearBets();
	virtual void repeat();
	virtual void startRound();
};