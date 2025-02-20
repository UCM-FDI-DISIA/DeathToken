#include "Marbles.h"
#include "Game.h"	

Marbles::Marbles(Game* game) : GameState(game), texture(game->getTexture(MARBLESBACK)) {}


void generateMarbles() {
}

void Marbles::render() const {
	texture->render();
	GameState::render();
}
