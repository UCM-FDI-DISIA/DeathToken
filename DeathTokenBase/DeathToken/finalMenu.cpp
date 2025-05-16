#include "finalMenu.h"
#include "button.h"
#include "MainMenu.h"
#include <cmath>


FinalMenu::FinalMenu(Game* g, bool victory) : GameState(g), show(false) {
	if (victory) {
		text = game->getTexture(GOODENDTEXT);
		image = game->getTexture(GOODENDIMG);
	}
	else {
		text = game->getTexture(BADENDTEXT);
		image = game->getTexture(BADENDIMG);
	}

	int _x = (int)(Game::WIN_WIDTH * (1400 / 1920.0f));
	int _y = (int)(Game::WIN_HEIGHT * (400 / 1080.0f));
	rectT = { Game::WIN_WIDTH / 2 - _x / 2,-_y,_x,_y };
	posT = { Game::WIN_WIDTH / 2 - _x / 2, (int)(_y * 0.2f) };

	_x = (int)(Game::WIN_WIDTH * (500 / 1920.0f));
	_y = (int)(Game::WIN_HEIGHT * (500 / 1080.0f));
	rectI = { Game::WIN_WIDTH / 2 - _x / 2,Game::WIN_HEIGHT,_x,_y };
	posI = { Game::WIN_WIDTH / 2 - _x / 2,Game::WIN_HEIGHT - (int)(_y * 1.2f) };


	_x = (int)(Game::WIN_WIDTH * (566 / 1920.0f));
	_y = (int)(Game::WIN_HEIGHT * (277 / 1080.0f));
	Button* menu = new Button(this, Game::WIN_WIDTH / 2 - _x / 2, Game::WIN_HEIGHT / 2 - (int)(_y * 0.6f), _x, _y, game->getTexture(MENU));
	menu->connect([this] {game->replace(new MainMenu(game));});
	addObjects(menu);
	addEventListener(menu);
}

void FinalMenu::update() {
	if (!show) {
		Vector2D t = lerp({ rectT.x,rectT.y }, posT);
		rectT.x += (int)t.getX();
		rectT.y += (int)t.getY();

		Vector2D i = lerp({ rectI.x,rectI.y }, posI);
		rectI.x += (int)i.getX();
		rectI.y += (int)i.getY();
		if (abs(i.getY()) <= 1.0f) {
			show = true;
		}
	}
	else {
		GameState::update();
	}
}
void FinalMenu::render() const {
	text->render(rectT);
	image->render(rectI);
	if (show) {
		GameState::render();
	}
}

Vector2D<float> FinalMenu::lerp(Vector2D<> origen, Vector2D<> destino) {
	Vector2D<int> v = (destino - origen);
	return { v.getX() * 0.02f, v.getY() * 0.02f };
}
