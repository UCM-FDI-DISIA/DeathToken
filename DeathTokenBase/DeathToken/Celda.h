#pragma once
#include "button.h"
#include "vector2D.h"
class SlotsInsanity;

//Clase auxiliar que usa SlotsInsanity para la gestión del 3 en raya
//Funciona como un botón para el jugador, es cada celda individual con su icono
class Celda : public Button {
public:
	Celda(SlotsInsanity*, Point2D<int>, int, int, Texture*, Texture*);
	inline ~Celda() { iconos = nullptr; };
	void render() const override;
	inline int getElem() { return elem; } // devuelve el elemento
	inline void setElem(int n) { elem = n; } //Setea el elemento (usado por la IA, pues esta no acciona botones)
	inline void resetElem() { elem = -1; } //Casilla vacía, representada con elem = -1
private:
	int elem; //Elemento que representa la casilla
	Texture* iconos;
	SlotsInsanity* slots;
};