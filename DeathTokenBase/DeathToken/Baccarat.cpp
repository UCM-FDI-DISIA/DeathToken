#include "Baccarat.h"

Baccarat::Baccarat() {}

void Baccarat::repartir() {
	for (int i = 0; i < 2; i++) {
		numAleatorio = generaAleatorio();
		tap.jugador.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
		numAleatorio = generaAleatorio();
		tap.banca.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
	}
	sumaJug = (tap.jugador[0] + tap.jugador[1]) % 10;
	sumaBanca = (tap.banca[0] + tap.banca[1]) % 10;
	if (sumaJug < 6) {
		numAleatorio = generaAleatorio();
		tap.jugador.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
		terceraBanca();
	}
	else if (sumaJug == 6 || sumaJug == 7) {
		if (sumaBanca < 6) {
			numAleatorio = generaAleatorio();
			tap.banca.push_back(numAleatorio);
			cartas.push_back(numAleatorio);
		}
	}
}

void Baccarat::terceraBanca() {
	if (sumaBanca < 3 || sumaBanca == 3 && tap.jugador.back() % 10 != 8 ||
		tap.jugador.back() % 10 < 8 && (sumaBanca == 4 && tap.jugador.back() % 10 > 1 ||
			sumaBanca == 5 && tap.jugador.back() % 10 > 3 || sumaBanca == 6 && tap.jugador.back() % 10 > 5)) {

		numAleatorio = generaAleatorio();
		tap.banca.push_back(numAleatorio);
		cartas.push_back(numAleatorio);
	}
}

int Baccarat::generaAleatorio() {
	int num = rand() % 12 + 1;
	int i = 0;
	int cont = 0;
	while (i < cartas.size() && cartas.size() > 4) {
		if (cartas[i] == num) {
			cont++;
			if (cont == 4) {
				num = rand() % 12 + 1;
				cont = 0;
				i = 0;
			}
		}
	}
	return num;
}