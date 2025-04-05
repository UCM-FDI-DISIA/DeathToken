#pragma once
#include "gameState.h"
#include "Texture.h"
#include "Button.h"
#include "Carrete.h"
#include "MatrizSlots.h"

#include <iostream>


class SlotsLocura : public GameState {
private:
	constexpr static int N_COLUM = 4;
	constexpr static int TAM_CELDA = 150;
	MatrizSlots* mat;

	const std::vector<int> frecuencias = { 8,7,6,5,4,3,3 };
	std::vector<int> resultante;

	int indice;
	bool turnoPlayer;
	bool jugando;
	Uint32 IAstartTime;

	std::vector<int> vectorAleatorio();
	int checkBoard() const;
	void IA();
	void ClearBoard();
	int getResult() override { return 0; }
public:
	SlotsLocura(Game*);
	~SlotsLocura() {}
	void update() override;
	void render() const override;
	int getNext();
	inline bool getJugando() { return jugando; }

	void iniciarGiro() override;
};