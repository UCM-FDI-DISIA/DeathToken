#include "Tutorial.h"

Tutorial::Tutorial(Game* game, GameState* gameState) : GameState(game), texture(game->getTexture(TUTORIAL)), ui(new UITutorial(this, game)), anterior(gameState)
{
   
}


void Tutorial::render() const {
	anterior->render();
	texture->render();
	GameState::render();
}