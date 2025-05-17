#include "celda.h"
#include "slotsInsanity.h"

Celda::Celda(SlotsInsanity* g, Point2D<int> p, int w, int h, Texture* tx, Texture* ic) 
	: Button(g,p.getX(), p.getY(), w, h, tx), elem(-1), iconos (ic), slots(g){
	//La celda funciona como un botón. Su callback comprueba que está vacia y que se está jugando.
	//En ese caso pide a SlotsInsanity el icono. (getNext devuelve -1 si no es el turno del jugador, por lo que permanecerá vacía)
	connect([this] {if (elem == -1 && slots->getJugando()) { elem = slots->getNext(); }});
	g->addEventListener(this);
}
void Celda::render() const {
	//Renderiza la celda y el icono correspondiente (salvo que esté vacía)
	text->render(box);
	if (elem != -1) iconos->renderFrame(box, 0, elem);
}