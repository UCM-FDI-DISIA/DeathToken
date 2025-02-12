#include "checkML.h"

#include "playState.h"
#include "Texture.h"
#include "Mushroom.h"

// Se crea la seta en un posición que recibe
Mushroom::Mushroom(PlayState* g, Texture* tex, Vector2D<int> pos)
	: Pickable(g, pos, { SPEED_MAG, 0 }, tex, Game::TILE_SIDE, Game::TILE_SIDE)
{	}
Mushroom::Mushroom(const Mushroom& m) : Pickable(m.state, m.pos, m.speed, m.texture, m.w, m.h)
{	}
sceneObject* Mushroom::clone() const
{
	return new Mushroom(*this);
}

void Mushroom::render() const {
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, 0);
}
void Mushroom::update() {
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

	sceneObject::update();
}
// Si Mario es pequeño lo transforma en Super Mario
// Si no, le da puntos
void Mushroom::triggerAction() {
	if (!state->getSuper())state->superOrDamage(true);
	else state->givePoints(POINTS);
}