#pragma once
#include <cstdlib>
#include <vector>
#include "gameState.h"
#include "Texture.h"
#include "EventHandler.h"
#include "Cards.h"
using namespace std;
struct Tapete {
	vector<int> banca;
	vector<int> jugador;
};

class Baccarat : public GameState, public EventHandler
{
protected:
	Cards* player1;
	Cards* player2;
	Cards* banker1;
	Cards* banker2;
	Texture* texture;
	Tapete tap;
	vector<int> cartas;
	int numAleatorio;
	int sumaJug;
	int sumaBanca;
	const int xDos = 2;
	const int xOcho = 8;
	//bool locura; global?
public:
	Baccarat(Game* game);

	void handleEvent(const SDL_Event& event) override;
	void clearDeck();
	void update() override;
	void render() const override;
	void repartir();
	void repartirTercera();
	void terceraBanca();
	int generaAleatorio();
};