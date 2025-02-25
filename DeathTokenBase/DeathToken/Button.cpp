#include "Button.h"
#include "Game.h"

Button::Button(GameState* g, int x, int y, int w, int h, Texture* t)
	: GameObject(g), text(t), hover(false)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}
void
Button::update()
{
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);

	// Comprueba si el ratón está sobre el rectángulo
	hover = SDL_PointInRect(&point, &box);
}
void Button::render() const {
	if (!hover)
		text->render(box);
	else {
		SDL_Rect point(box.x - Game::TILE_SIDE, box.y, box.h, box.h);
		text->render(box, SDL_Color(255, 255, 0));
	}
}
void Button::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point point{ event.button.x, event.button.y };
		if (SDL_PointInRect(&point, &box))
			cb();
	}
}
void Button::connect(Callback callback) {
	cb = callback;
}

ButtonUI::ButtonUI(GameState* g, int x, int y, int w, int h, Texture* t, Texture* tC)
	: Button(g, x, y, w, h, t), textC(tC), clicked(false) {
	boxB.x = x - (w * 0.05f);
	boxB.y = y - (h * 0.05f);
	boxB.w = w * 1.1f;
	boxB.h = h * 1.1f;
}
void
ButtonUI::update()
{
	Button::update();
	int mouseState = SDL_GetMouseState(NULL, NULL);
	clicked = (hover && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)));
}
void
ButtonUI::render() const
{
	if (clicked)
	{
		textC->render(box);
	}
	else if (!hover)
		text->render(box);
	else {
		SDL_Rect point(box.x - Game::TILE_SIDE, box.y, box.h, box.h);
		text->render(boxB);
	}
}

ButtonBet::ButtonBet(GameState* g, int x, int y, int w, int h, Texture* t, Texture* tC)
	: ButtonUI(g, x, y, w, h, t, tC) {}

ButtonChip::ButtonChip(GameState* g, int x, int y, int w, int h, Texture* t, Texture* tC)
	: ButtonUI(g, x, y, w, h, t, tC) {}