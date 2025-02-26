#include "Button.h"
#include "Game.h"
#include "UI.h"

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
	if (!hover) {
		text->render(box);
	}
	else {
		SDL_Rect point(box.x, box.y, box.h, box.h);
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

ButtonChip::ButtonChip(GameState* g, UI* ui, int x, int y, int w, int h, int id,
						int v0, int v1, int v2, Texture* t0, Texture* t1, Texture* t2)
	: Button(g, x, y, w, h, t0), ui(ui), onUse(false), clicked(false), id(id), slot(false)
{
	value = v0;
	values[0] = v0;
	values[1] = v1;
	values[2] = v2;
	textures[0] = t0;
	textures[1] = t1;
	textures[2] = t2;
	boxB.x = x;
	boxB.y = y - 20;
	boxB.w = w;
	boxB.h = h;
	boxC = boxB;
}
void
ButtonChip::update()
{
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);
	int mouseState = SDL_GetMouseState(NULL, NULL);
	if (clicked)
	{
		hover = SDL_PointInRect(&point, &boxC);
	}
	else
	{
		hover = SDL_PointInRect(&point, &box);
	}
	if (hover && !onUse)
		ui->changeChip(id);
	else if (!clicked && hover && !slot && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
		clicked = true;
	else if (clicked && (!mouseState))
		clicked = false;
	if (clicked)
	{
		boxC.x = point.x - (boxC.w / 2);
		boxC.y = point.y -(boxC.h / 2);
	}
}
void
ButtonChip::render() const
{
	if (clicked)
		text->render(boxC);
	else if (onUse)
		text->render(boxB);
	else
		text->render(box);
}
void
ButtonChip::setOnUse(const bool& val)
{
	onUse = val;
	if (!val) clicked = false;
}
void
ButtonChip::changePage(const int& n)
{
	value = values[n];
	text = textures[n];
}
void
ButtonChip::setSlot()
{
	slot = true;
}

ButtonMarbles::ButtonMarbles(GameState* g, int x, int y, int w, int h, Texture* t, int type, std::vector<int>NCMarbles)
	: Button(g, x, y, w, h, t), NCMarbles(NCMarbles), type(type)
{
	stop = type;
	CMarbles.push_back(g->getGame()->getTexture(REDMARBLE));
	CMarbles.push_back(g->getGame()->getTexture(GREENMARBLE));
	CMarbles.push_back(g->getGame()->getTexture(BLUEMARBLE));
	CMarbles.push_back(g->getGame()->getTexture(YELLOWMARBLE));
}
void
ButtonMarbles::render() const
{
	if (!hover) {
		text->render(box);


		SDL_Rect auxBox;
		int pos = 0;

		switch (type)
		{
		case 1: {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 1) {
					auxBox.x = box.x + box.w / 2 - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					break;

				}
			}

			break;
		}case 2: {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 2) {

					auxBox.x = box.x + box.w / 4 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);



					auxBox.x = box.x + (box.w - box.w / 4) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);


				}
				else if (NCMarbles[i] == 1) {
					if (pos == 0) {
						auxBox.x = box.x + box.w / 4 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						pos++;
					}
					else {
						auxBox.x = box.x + (box.w - box.w / 4) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						break;
					}
				}
			}
			break;
		}case 3: {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 3) {
					auxBox.x = box.x + box.w / 4 - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					auxBox.x = box.x + (box.w - box.w / 4) - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					auxBox.x = box.x + 2 * box.w / 4 - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					break;
				}
			}

			break;
		}case 4: {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 3) {
					if (i == 0) {
						//1/1
						auxBox.x = box.x + box.w / 5 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 4 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//2/1
						auxBox.x = box.x + box.w / 5 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 2 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//3/1
						auxBox.x = box.x + box.w / 5 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 3 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);


					}
					else if (i == 1) {
						//1/2
						auxBox.x = box.x + 2 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 4 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//2/2
						auxBox.x = box.x + 2 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 2 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//3/2
						auxBox.x = box.x + 2 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 3 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);


					}
					else if (i == 2) {
						//1/3
						auxBox.x = box.x + 3 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 4 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//2/3
						auxBox.x = box.x + 3 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 2 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//3/3
						auxBox.x = box.x + 3 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 3 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);

					}
					else if (i == 3) {

						//1/4
						auxBox.x = box.x + 4 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 4 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//2/4
						auxBox.x = box.x + 4 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 2 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//3/4
						auxBox.x = box.x + 4 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + 3 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
					}
				}
			}

			break;
		}
		default:
			break;
		}
	}
	else {
		SDL_Rect point(box.x, box.y, box.h, box.h);
		text->render(box, SDL_Color(255, 255, 0));
	}
}