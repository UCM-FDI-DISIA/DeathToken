#include "SlotsLocura.h"


SlotsLocura::SlotsLocura(Game* g) : GameState(g)
{
	mat = new MatrizSlots(this,(0,0),TAM_CELDA,TAM_CELDA, game->getTexture(CELDA), game->getTexture(ICONOS),
		N_COLUM,N_COLUM);
	addObjects(mat);
}
