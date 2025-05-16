#include "checkML.h"
#include "player.h"
#include "texture.h"
#include "menu.h"

// Se crea el jugador leyendo de archivo su posición y vidas
Player::Player(GameState* g, Point2D<> pos, Texture* texture, Menu* men)
	:sceneObject(g, pos, texture), texture(texture), menu(men),locura(false)
{
	w = (int)((125.0f / 1980.f) * Game::WIN_WIDTH);
	h = (int)((125.0f / 1080.0f) * Game::WIN_HEIGHT);
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
		}
	}
	else if (evento.type == SDL_KEYUP) { speed.setX(0); speed.setY(0); }
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
void Player::collision(vector<SDL_Rect> obstaculos) {

	SDL_Rect collision;

	int fixY = 0;
	int fixX = 0;
	SDL_Rect playerRect = getCollisionRect();
	// Recorre cada uno de los limites y comprueba las colisiones
	for (int i = 0; i < obstaculos.size(); ++i) {
		// Si la velocidad en Y es distinta de 0, mueve el rect provisional del jugador (playerRect) y comprueba si está colisionando. Luego restaura la posición
		if (speed.getY() != 0) {
			playerRect.y += speed.getY(); //* multiplicarlo por delta time;
			int fix = 0;
			if (SDL_IntersectRect(&playerRect, &obstaculos[i], &collision))
				fix = collision.h * (speed.getY() > 0 ? 1 : -1);
			fixY += fix;
			playerRect.y -= speed.getY();
		}
		// hacemos lo mismo con la velocidad en x
		if (speed.getX() != 0) {
			playerRect.x += speed.getX();
			int fix = 0;
			if (SDL_IntersectRect(&playerRect, &obstaculos[i], &collision))
				fix = collision.w * (speed.getX() > 0 ? 1 : -1);
			fixX += fix;
			playerRect.x -= speed.getX();
		}
	}
	pos += {speed.getX() - fixX, speed.getY() - fixY};

}
