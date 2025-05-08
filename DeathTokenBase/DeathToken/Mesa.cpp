#include "checkML.h"
#include "Mesa.h"
#include "Menu.h"
#include "Game.h"


Mesa::Mesa(GameState* g, Vector2D<> pos, Texture* tex, int width, int height) : sceneObject(g, pos, tex), hover(false), texture(tex)
{
	w = width;
	h = height;
}

void Mesa::connect(Callback callback) {
	cb = callback;
}

void Mesa::render() const {
	SDL_Rect rect = getRenderRect();
	if (!hover) {
		texture->render(rect);
	}
	else {
		texture->render(rect, SDL_Color(255, 255, 0));
	}
}
void Mesa::update() {}

void Mesa::handleEvent(SDL_Event const& evento) {
	if (evento.key.keysym.sym == SDLK_e && hover) {
		if(hover){
			cb();
		}
	}
}

SDL_Rect Mesa::getRect() const {
	SDL_Rect rect;
	rect.x = pos.getX();
	rect.y = pos.getY() - h;
	rect.w = w;//ancho
	rect.h = h;//alto
	return rect;
}