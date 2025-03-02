#include "Cards.h"
#include "Game.h"

Cards::Cards(GameState* game, int frame, Point2D<> pos, double angle) :
	sceneObject(game, pos, game->getGame()->getTexture(CARDS)),
	texture(game->getGame()->getTexture(CARDS)),
	frame(frame),
	angle(angle)
{
	w = Game::WIN_WIDTH / 20;
	h = Game::WIN_HEIGHT / 8;
}

void Cards::render() const {
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, frame, angle);
}


void Cards::update() {

}
Collision Cards::hit(const SDL_Rect&, Collision::Target) {
	return NO_COLLISION;
}