#pragma once
#include "gameState.h"
#include "UI.h"
#include <vector>

class Celda;

class SlotsLocura : public GameState {
private:
	constexpr static int N_COLUM = 4;
	constexpr static int TAM_CELDA = 200;
	std::vector<std::vector<Celda*>> mat;

	const std::vector<int> frecuencias = { 4,3,3,3,2,2,1 };
	std::vector<int> resultante;
	UISlots* ui;
	int indice;
	bool turnoPlayer;

	std::vector<int> vectorAleatorio();
	bool checkBoard() const;
	void IA();
public:
	SlotsLocura(Game*);
	~SlotsLocura(){}
	void update() override;
	void render() const override;
	int getNext();
};