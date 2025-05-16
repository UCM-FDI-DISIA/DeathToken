#pragma once
#include "slots.h"
#include <vector>

class Celda;

// Slots Locura, que funciona como un tres en raya
class SlotsInsanity : public Slots {
private:
	constexpr static int N_COLUM = 4;
	constexpr static int TAM_CELDA = 180;
	std::vector<std::vector<Celda*>> mat; // Matriz con las celdas del tablero

	const std::vector<int> frecuencias = { 8,7,6,5,4,3,3 }; // Frecuencia de apariciones de los 7 iconos
	std::vector<int> resultante; // Vector aleatorio con los indices de los iconos formado segun las frecuencias

	int indice; //
	bool turnoPlayer; // Marca si el turno es del jugador o de la IA
	bool jugando; // Comprobante de cuando está en marcha el juego
	Uint32 IAstartTime; // Tiempo para el delay de la IA

	std::vector<int> vectorAleatorio(); // Metodo para formar el vector 'resutante'
	int checkBoard() const; // Metodo de comprobacion del tablero para buscar el 3 en raya
	void IA(); // logica de movimiento de la IA
	void ClearBoard(); // Pone el tablero en blanco
public:
	SlotsInsanity(Game*);
	~SlotsInsanity() {}
	void update() override;
	void render() const override;
	int getNext();
	inline bool getJugando() { return jugando; }

	bool iniciarGiro() override;
};