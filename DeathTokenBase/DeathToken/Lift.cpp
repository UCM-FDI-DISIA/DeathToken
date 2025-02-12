#include "checkML.h"

#include "Lift.h"
#include "Texture.h"

Lift::Lift(PlayState* g, istream& in, Texture* tex) : sceneObject(g, in, {0, 1}, 4, 1, tex)
{
	// cambia de velocidad según la entrada que reciba
	in >> velocity;
	speed = speed * velocity;
}
Lift::Lift(const Lift& l) : sceneObject(l.state, l.pos, l.speed, l.w, l.h, l.texture)
{
	velocity = l.velocity;
}

sceneObject* Lift::clone() const
{
	return new Lift(*this);
}

void Lift::render() const{
	SDL_Rect render = getRenderRect();
	texture->renderFrame(render, 0, frame);
}
// Mueve la plataforma según su velocidad y si llega a un borde de la pantalla lo mueve al contrario
void Lift::update(){
	pos += speed;
	int lowBorder = Game::WIN_HEIGHT * Game::TILE_SIDE;
	if (velocity < 0 && pos.getY() <= 0) pos.setY(lowBorder);
	else if (velocity > 0 && (pos.getY() - h) >= lowBorder)
		pos.setY(0);
}

// Devuelve obstacúlo si colisiona con cualquier objeto
Collision Lift::hit(const SDL_Rect& hit, Collision::Target target) {
	SDL_Rect rect = getCollisionRect();
	SDL_Rect inter;
	if (SDL_IntersectRect(&hit, &rect, &inter)) {
		Collision col{ Collision::OBSTACLE, inter.w, inter.h };
		return col;
	}
	return NO_COLLISION;
}