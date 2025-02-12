#include "checkML.h"

#include "playState.h"
#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(PlayState* g, istream& in, Texture* text, int w, int h)
	: sceneObject(g, in, Vector2D{ -SPEED_MAG,0 }, w, h, text)
{	}
Enemy::Enemy(PlayState* g, Vector2D<> position, Texture* text, int w, int h)
	: sceneObject(g, position, Vector2D{ -SPEED_MAG,0 }, w, h, text)
{	}

void Enemy::render() const {
	SDL_Rect render = getRenderRect();
	if (speed.getX() > 0)texture->renderFrame(render, 0, frame, SDL_FLIP_HORIZONTAL);
	else texture->renderFrame(render, 0, frame);
}

void Enemy::update() {
	// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed += {0, PlayState::GRAVITY};

	// Intenta moverse
	Collision collision = tryToMove(speed, Collision::ENEMIES);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	if (moveDelay-- == 0) {
		moveDelay = MOVE_PERIOD;
		frame++;
		if (frame == 2) frame = 0;
	}

	sceneObject::update();
}
Collision Enemy::hit(const SDL_Rect& region, Collision::Target target) {
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	// Si la interseccion ha sido con el jugador muere si ha sido por arriba o le hace daño
	if (target == Collision::PLAYER && hasIntersection) {
		if (ownRect.y <= region.y + region.h && ownRect.y + ownRect.h > region.y + region.h){
			state->givePoints(POINTS);
			delete this;
		}
		else return Collision{ Collision::DAMAGE };
	}
	return NO_COLLISION;
}