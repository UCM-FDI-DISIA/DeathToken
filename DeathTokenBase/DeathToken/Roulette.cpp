#include "Roulette.h"

Roulette::Roulette(GameState* game, Point2D<> pos, Texture* text) : sceneObject(game, pos, text), texture(text) {
	w = Game::WIN_WIDTH / 2;
	h = Game::WIN_WIDTH / 2;
}

void Roulette::render() const {
	SDL_Rect rect = getRenderRect();
	texture->render(rect, rot);
}

void Roulette::update() {
	rot += speed;
	if (rot > 360.0) rot -= 360.0;
	speed *= decelerate;
}

Collision Roulette::hit(const SDL_Rect&, Collision::Target) {
	return NO_COLLISION;
}

void Roulette::addSpeed(int s) {
	if (speed == 0)
		speed = s;
}