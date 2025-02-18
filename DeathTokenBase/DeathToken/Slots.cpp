#include "Slots.h"
#include "Carrete.h"

Slots::Slots(Game* g) : GameState(g)
{
	for (int i = 0; i < nColum; ++i) {
		int x = game->WIN_WIDTH / 4 * (i + 1);
		gameObjects.push_back(new Carrete(this, { x , 100 }, tamCelda,tamCelda,game->getTexture(CELDA), game->getTexture(CELDA)));
		}
	}