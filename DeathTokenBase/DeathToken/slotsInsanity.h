#pragma once
#include "slots.h"
#include <vector>

class Celda;

class SlotsInsanity : public Slots {
private:
	constexpr static int N_COLUM = 4;
	constexpr static int TAM_CELDA = 200;
	std::vector<std::vector<Celda*>> mat;

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
	SlotsInsanity(Game*);
	~SlotsInsanity() {}
	void update() override;
	void render() const override;
	int getNext();
	inline bool getJugando() { return jugando; }

	void iniciarGiro() override;
};