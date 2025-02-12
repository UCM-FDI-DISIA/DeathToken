#include "checkML.h"

#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(PlayState* g, istream& in, Texture* text) : Enemy(g, in, text, 1, 1)
{	}
Goomba::Goomba(const Goomba& g) : Enemy(g.state, g.pos, g.texture, g.w, g.h)
{	}
sceneObject* Goomba::clone() const
{
	return new Goomba(*this);
}