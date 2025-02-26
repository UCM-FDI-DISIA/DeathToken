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

Button::Button(GameState* g, int x, int y, int w, int h, Texture* t, int type, std::vector<int>NCMarbles)
	: GameObject(g),text(t), hover(false), NCMarbles(NCMarbles), type(type)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	stop = type;
	CMarbles.push_back(g->getGame()->getTexture(REDMARBLE)); 
	CMarbles.push_back(g->getGame()->getTexture(GREENMARBLE));
	CMarbles.push_back(g->getGame()->getTexture(BLUEMARBLE));
	CMarbles.push_back(g->getGame()->getTexture(YELLOWMARBLE));

	
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


		SDL_Rect auxBox;
		int pos = 0;

		switch (type)
		{
		case 1 : {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 1) {
					auxBox.x = box.x + box.w / 2-(74.0/1080.0 * Game::WIN_HEIGHT)/2;
					auxBox.y = box.y + box.h / 2-(74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					break;

				}
			}

			break;
		}case 2: {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 2 ) {
					
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
						auxBox.x = box.x +  box.w/4 - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						pos++;
					}
					else {
						auxBox.x = box.x + (box.w -box.w/4) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 2 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						break;
					}
				}
			}
			break;
		}case 3 : {
			for (int i = 0; i < NCMarbles.size(); i++) {
				if (NCMarbles[i] == 3) {
					auxBox.x = box.x + box.w / 4 - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					auxBox.x = box.x +(box.w- box.w / 4) - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
					auxBox.y = box.y + box.h / 2 - (74.0 / 1920.0 * Game::WIN_WIDTH) / 2;
					auxBox.w = (74.0 / 1920.0 * Game::WIN_WIDTH);
					auxBox.h = (74.0 / 1080.0 * Game::WIN_HEIGHT);
					CMarbles[i]->render(auxBox);
					auxBox.x = box.x + 2*box.w / 4 - (74.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
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
					else if (i ==1) {
						//1/2
						auxBox.x = box.x + 2 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y + box.h / 4 - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
						auxBox.w = (52.0 / 1920.0 * Game::WIN_WIDTH);
						auxBox.h = (52.0 / 1080.0 * Game::WIN_HEIGHT);
						CMarbles[i]->render(auxBox);
						//2/2
						auxBox.x = box.x + 2 * (box.w / 5) - (52.0 / 1080.0 * Game::WIN_HEIGHT) / 2;
						auxBox.y = box.y  + 2 * (box.h / 4) - (52.0 / 1920.0 * Game::WIN_WIDTH) / 2;
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
Button::~Button() {
	for (auto texture : CMarbles) {
		delete texture;
	}
	CMarbles.clear();
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