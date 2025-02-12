#include "checkML.h"

#include "playState.h"
#include "Texture.h"
#include "Coin.h"

// Se crea la seta en un posición que recibe
Coin :: Coin(PlayState* g, istream& is, Texture* tex)
	: Pickable(g, is, { 0, 0 }, tex, 1, 1)
{	}
Coin::Coin(const Coin& c) : Pickable(c.state, c.pos, c.speed, c.texture, c.w, c.h)
{	}
sceneObject* Coin ::clone() const
{
	return new Coin(*this);
}

void Coin::render() const {
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, frame);
}
void Coin::update() {
	if (moveDelay-- == 0) {
		moveDelay = MOVE_PERIOD;
		frame++;
		if (frame > 3) frame = 0;
	}
}
// Al ser recogida la moneda se dan puntos
void Coin ::triggerAction() {
	state->givePoints(POINTS);
}