#include "Cards.h"
#include "Game.h"

Cards::Cards(GameState* game, int frame, Point2D<> pos) :
	sceneObject(game, pos, game->getGame()->getTexture(CARDS)),
	texture(game->getGame()->getTexture(CARDS)),
	frame(frame)
{
	w = Game::WIN_WIDTH / 14;
	h = Game::WIN_HEIGHT / 7;
}

void Cards::render() const {
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, frame);
}


void Cards::update() {

}
Collision Cards::hit(const SDL_Rect&, Collision::Target) {
	return NO_COLLISION;
}