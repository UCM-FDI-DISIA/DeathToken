#include "checkML.h"

#include "Block.h"
#include "playState.h"
#include "Texture.h"
#include "Coin.h"
#include "Mushroom.h"

// La constructora lee de archivo la posición del bloque, su tipo y el contenido (Seta o Moneda)
Block::Block(PlayState* g, istream& in, Texture* text, Texture* mush)
	:sceneObject(g, in, { 0,0 }, 1, 1, text), mushTex(mush)
{
	char type;
	in >> type;
	if (type == '?' || type == 'H') {
		if (type == '?') {
			frame = 0;
			tipo = Surprise;
		}
		else tipo = Hidden;
		char content;
		in >> content;
		if (content == 'C') contenido = Coin;
		else if (content == 'P') contenido = Mush;
	}
	else {
		frame = 5;
		tipo = Brick;
	}
}
Block::Block(const Block& b) : sceneObject(b.state, b.pos, b.speed, b.w, b.h, b.texture)
{
	tipo = b.tipo;
	contenido = b.contenido;
	mushTex = b.mushTex;
	frame = b.frame;
}
sceneObject* Block::clone() const
{
	return new Block(*this);
}
// Se renderiza el bloque si no es hidden
void Block::render() const {
	if (tipo != Hidden) {
		SDL_Rect render = getRenderRect();
		texture->renderFrame(render, 0, frame);
	}
}
// Gestiona la animacion de ?
void Block::update() {
	if (tipo == Surprise) {
		if (moveDelay-- == 0) {
			moveDelay = MOVE_PERIOD;
			frame++;
			if (frame > 3) frame = 0;
		}
	}
}
// Comprobación de las colisiones del bloque con los elementos del juego
Collision Block::hit(const SDL_Rect& hit, Collision::Target target) {
	SDL_Rect rect = getCollisionRect();
	SDL_Rect inter;
	if (SDL_IntersectRect(&hit, &rect, &inter)) {
		// Si la colisión ha sido con el jugador desde justo abajo del bloque,
		// el ladrillo se rompe (si Mario es grande) o el bloque ? o escondido revela su contenido
		if (target == Collision::PLAYER && rect.y + rect.h >= hit.y && rect.y + rect.h <= hit.y + Game::TILE_SIDE &&
			rect.x <= hit.x + hit.w / 2 && rect.x + rect.w >= hit.x + hit.w / 2) {
			switch (tipo) {
			case Brick:
				if (state->getSuper()) delete this;
				break;
			case Surprise:
			case Hidden:
				// Se crea una seta
				if (contenido == Mush) {
					int side = Game::TILE_SIDE;
					
					Mushroom* m = new Mushroom(state, mushTex, { pos.getX(), pos.getY() - side });
					state->addObjects(m);
					state->addToSceneList(m);
				}
				// Se dan puntos
				else if (contenido == Coin) {
					state->givePoints(Coin::POINTS);
				}
				frame = 4;
				tipo = Hit;
				break;
			}
		}
		Collision col{ Collision::OBSTACLE, inter.w, inter.h };
		return col;
	}
	return NO_COLLISION;
}