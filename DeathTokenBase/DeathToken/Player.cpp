#include "checkML.h"
#include "Player.h"
#include "Texture.h"


// Se crea el jugador leyendo de archivo su posición y vidas
Player::Player(GameState* g, Point2D<> pos, Texture* texture)
	:sceneObject(g, pos, texture), texture(texture)
{
	w = Game::WIN_WIDTH / 14;
	h = Game::WIN_HEIGHT / 7;
}

void Player::render() const {
	SDL_Rect render = getRenderRect();
	if (speed.getX() < 0) {
		texture->renderFrame(render, 0, 0);
	}
	else {
		texture->renderFrame(render, 0, 0, SDL_FLIP_HORIZONTAL);
	}

}

// Actualización y colisiones del personaje
void Player::update() {
	if (speed.getX() == SPEED_MAG && pos.getX() < Game::WIN_WIDTH - w) {//el por diez sobra es pq ahora esta mal puesto el width
		pos.setX(pos.getX() + speed.getX());
	}

	if (speed.getX() == -SPEED_MAG && pos.getX() > 0) {
		pos.setX(pos.getX() + speed.getX());
	}

	if (speed.getY() == SPEED_MAG && pos.getY() < Game::WIN_HEIGHT) {
		pos.setY(pos.getY() + speed.getY());
	}

	if (speed.getY() == -SPEED_MAG && pos.getY() > 0 + h) {
		pos.setY(pos.getY() + speed.getY());
	}
}

Collision Player::hit(const SDL_Rect& rect, Collision::Target target) {
	return NO_COLLISION;
}
// Recibe el input y establece la nueva dirección de movimiento (solo salta si está en el suelo)
void Player::handleEvent(const SDL_Event& evento) {
	if (evento.type == SDL_KEYDOWN) {
		switch (evento.key.keysym.sym) {
		case SDLK_d:
		case SDLK_RIGHT:
			speed.setX(SPEED_MAG);
			break;
		case SDLK_a:
		case SDLK_LEFT:
			speed.setX(-SPEED_MAG);
			break;
		case SDLK_s:
		case SDLK_DOWN:
			speed.setY(SPEED_MAG);
			break;
		case SDLK_w:
		case SDLK_UP:
			speed.setY(-SPEED_MAG);
			break;
		case SDLK_ESCAPE:
			//state->pausa();
			break;
		}
	}
	else  { speed.setX(0); speed.setY(0); }
}

//cojo el rect del player para hacer colisiones con botones
SDL_Rect Player::getRect() const {
	SDL_Rect rect;
	rect.x = pos.getX();
	rect.y = pos.getY() - h;
	rect.w = w;//ancho
	rect.h = h;//alto
	return rect;
}
