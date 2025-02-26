#include "Marbles.h"

Marbles::Marbles(Game* game) : GameState(game) {
	ui = new UIChips(this, game);
}