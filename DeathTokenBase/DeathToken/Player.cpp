#include "checkML.h"
#include "Player.h"
#include "Texture.h"
#include "Menu.h"

// Se crea el jugador leyendo de archivo su posición y vidas
Player::Player(GameState* g, Point2D<> pos, Texture* texture, Menu* men)
	:sceneObject(g, pos, texture), texture(texture), menu(men),colisionando(false), isColliding(false)
{
	w = (125.0f / 1980.f) * Game::WIN_WIDTH;
	h = (125.0f / 1080.0f) * Game::WIN_HEIGHT;
}

void Player::render() const {
	SDL_Rect render = getCollisionRect();
	if (speed.getX() < 0) {
		texture->renderFrame(render, 0, 0);
	}
	else {
		texture->renderFrame(render, 0, 0, SDL_FLIP_HORIZONTAL);
	}

}

// Actualización y colisiones del personaje
void Player::update() {
	SDL_Rect collision;
	SDL_Rect playerRect = getCollisionRect();
	vector<SDL_Rect> limite = menu->getLimits();
	for (int i = 0; i < limite.size(); ++i) {
		SDL_IntersectRect(&playerRect, &limite[i], &collision);
		if (speed.getY() != 0) {
			int fix = 0;
			colisionando = collision.h > 0 && collision.h < playerRect.h;
			if (colisionando) {
				fix = collision.h * (speed.getY() > 0 ? 1 : -1);				
			}
			if (fix != 0) {
				fix *= -1;
				pos += {0, speed.getY() + fix};
			} 
			else {
				pos += {0, speed.getY()};
			}
		}
		if (speed.getX() != 0) {
			int fix = 0;
			colisionando = collision.w > 0 && collision.w < playerRect.w;
			if (colisionando) {
				fix = collision.w * (speed.getX() > 0 ? 1 : -1);
			}
			if (fix != 0) {
				fix *= -1;
				pos += {speed.getX() + fix, 0};
			} 
			else {
				pos += {speed.getX(), 0};
			} 
		}
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
	else if (evento.type == SDL_KEYUP && evento.key.keysym.sym != SDLK_SPACE) { speed.setX(0); speed.setY(0);}
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
