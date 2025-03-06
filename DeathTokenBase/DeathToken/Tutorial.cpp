#include "Tutorial.h"

Tutorial::Tutorial(Game* game) : GameState(game), texture(game->getTexture(TUTORIAL)), ui(new UITutorial(this, game))
{
   
}


void Tutorial::render() const {
	texture->render();
	GameState::render();
}