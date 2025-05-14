#include "Celda.h"
#include "slotsInsanity.h"

Celda::Celda(SlotsInsanity* g, Point2D<int> p, int w, int h, Texture* tx, Texture* ic) 
	: Button(g,p.getX(), p.getY(), w, h, tx), elem(-1), iconos (ic), slots(g){
	connect([this] {if (elem == -1 && slots->getJugando()) { elem = slots->getNext(); }});
	g->addEventListener(this);
}
void Celda::render() const {
	text->render(box);
	if (elem != -1) iconos->renderFrame(box, 0, elem);
}