#include "checkML.h"

#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(PlayState* g, istream& in, Texture* text) : Enemy(g, in, text, 1, 2)
{	}
Koopa::Koopa(const Koopa& g) : Enemy(g.state, g.pos, g.texture, g.w, g.h)
{	}
sceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}