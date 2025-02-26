#include "Marbles.h"

Marbles::Marbles(Game* game) : GameState(game) {
	ui = new UISlots(this, game);
}