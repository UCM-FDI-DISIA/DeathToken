#include "checkML.h"

#include "Player.h"
#include "Texture.h"
#include "AnimState.h"

// Se crea el jugador leyendo de archivo su posición y vidas
Player::Player(GameState* g, istream& in, Texture* tex, Texture* superTex)
	:sceneObject(g, in, Vector2D{ 0, JUMP_MAG }, 1, 1, tex), miniTexture(tex), superTexture(superTex),
	super(false), invencible(false), timeInv(0), salto(SUELO), currentjump(0)
{
	OGpos = pos;
	vidas;
	in >> vidas;
}
Player::Player(const Player& p) : sceneObject(p.state, p.pos, p.speed, p.w, p.h, p.texture),
miniTexture(p.miniTexture), superTexture(superTexture), super(p.super), invencible(p.invencible), timeInv(p.timeInv),
salto(SUELO), currentjump(0), vidas(p.vidas), OGpos(p.pos)
{	}
sceneObject* Player::clone() const {
	return new Player(*this);
}

// Al cambiar o reiniciar nivel, Mario vuelve a su posicion de inicios
void Player::resetLevel() {
	vidas--;
	frame = 1;
	int tile = Game::TILE_SIDE;
	speed.setY(-tile);
	//AnimState* dead = new AnimState(state->getGame(), state);
	//dead->connect([this]() -> bool { return deadAnim();});
	//state->getGame()->push(dead);
}
// Gestiona si Mario recibe super o si le hacen daño y pierde el super o una vida y se reinicia
void Player::superOrDamage(bool sup) {
	if (!super && !sup) {
		resetLevel();
	}
	else {
		super = sup;
		if (sup) {
			h = 2 * Game::TILE_SIDE;
			texture = superTexture;
		}
		else {
			h = Game::TILE_SIDE;
			texture = miniTexture;
		}
	}
}

void Player::render() const {
	SDL_Rect render = getRenderRect();
	if (speed.getX() < 0) {
		texture->renderFrame(render, 0, frame, SDL_FLIP_HORIZONTAL);
	}
	else {
		texture->renderFrame(render, 0, frame);
	}

}
//Gestion de frames dependendo de si el personaje esta saltando o andando
void Player::MovementFrames() {
	if (frame != 1) {
		if (salto != SUELO) frame = 6;
		else if (speed.getX() == 0) frame = 0;
		else {
			if (frame == 0) frame = 2;
			else if (frame >= 4) {
				frame = 2;
			}
			else {
				frame++;
			}
		}
	}
}
// Actualización y colisiones del personaje
void Player::update() {
	// Si esta saltando y llega a la maxima distancia, empieza a caer
	if (salto == SALTO) {
		currentjump++;
		if (currentjump == (Game::TILE_SIDE * MAX_JUMP / JUMP_MAG)) {
			salto = CAIDA;
			speed.setY(JUMP_MAG);
			currentjump = 0;
		}
	}

	// Comprueba que Mario no caiga al vacio o salga por la pantalla por arriba
	int side = Game::TILE_SIDE;
	SDL_Rect rect = getCollisionRect();
	if (rect.y + rect.h >= Game::WIN_HEIGHT * side
		|| rect.y < -side) {
		super = false;
		superOrDamage(false);
	}

	// Intenta moverse
	Collision collision = tryToMove(speed, Collision::PLAYER);

	// Gestión de daño
	if (collision.result == Collision::DAMAGE && !invencible) {
		invencible = true;
		superOrDamage(false);
	}
	else {
		// Si ha colisionado en vertical gestiona si empieza a caer o ha tocado el suelo
		if (collision.vertical) {
			if (salto == SALTO) salto = CAIDA;
			else if (salto == CAIDA) salto = SUELO;
			speed.setY(JUMP_MAG);
			currentjump = 0;
		}
		else if (speed.getY() > 0) salto = CAIDA;
		else if (speed.getY() < 0) salto = SALTO;

		// Si el personaje está a la mitad, se avanza el offset
		//if (pos.getX() >= (Game::WIN_WIDTH / 2) * Game::TILE_SIDE + state->getOffset() && speed.getX() > 0) {
		//	state->offsetPlus(speed.getX());
		//}
		//// Evitar que hay retroceso de la pantalla
		//if (pos.getX() <= state->getOffset() && speed.getX() < 0) pos.setX(state->getOffset());

		if (invencible) {
			timeInv++;
			if (timeInv == INV_TIME) {
				invencible = false;
				timeInv = 0;
			}
		}
		MovementFrames();
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
		case SDLK_SPACE:
			if (salto == SUELO) {
				salto = SALTO;
				speed.setY(-JUMP_MAG);
			}
			break;
		case SDLK_ESCAPE:
			//state->pausa();
			break;
		}
	}
	else if (evento.type == SDL_KEYUP && evento.key.keysym.sym != SDLK_SPACE) speed.setX(0);
}

bool Player::deadAnim() {
	if (speed.getY() < SPEED_LIMIT)
		//speed += {0, GameState::GRAVITY};
	int newY = pos.getY() + speed.getY();
	/*if (newY >= Game::WIN_HEIGHT * Game::TILE_SIDE) {
		pos = OGpos;
		frame = 0;
		timeInv = 0;
		invencible = false;
		speed = { 0,JUMP_MAG };
		return false;
	}*/
	//pos.setY(newY);
	return true;
}