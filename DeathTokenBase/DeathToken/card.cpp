#include "card.h"
#include "game.h"

Card::Card(GameState* game, int frame, Point2D<> pos, double angle) :
	SceneObject(game, pos, game->getGame()->getTexture(CARDS)),
	texture(game->getGame()->getTexture(CARDS)),
	frame(frame),
	angle(angle)
{
	w = Game::WIN_WIDTH / 20; //96px
	h = Game::WIN_HEIGHT / 8; //135px
}

void Card::render() const {
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, frame, angle);
}


void Card::update() {

}