#include "Carrete.h"
Carrete::Carrete(PlayState* g,Texture* celdas,Texture* iconos): sceneObject(g, 1,1,celdas), simbolos(iconos) {
}
vector<int> Carrete::vectorAleatorio() {
	vector<int> vector;
	for (int i = 0; i < NUM_ELEMS; ++i) {
		for (int j : frecuencias) {
			vector.push_back(i);
		}
	}

	return vector;
}