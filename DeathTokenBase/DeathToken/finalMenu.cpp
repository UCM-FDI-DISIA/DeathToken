#include "finalMenu.h"
#include "Button.h"
#include "Menu.h"

FinalMenu::FinalMenu(Game* g, bool victory) : GameState(g) {
	if (victory) {
		text = game->getTexture(BTNSLOT);
		image = game->getTexture(BTNSLOT);
	}
	else {
		text = game->getTexture(BTNSLOTCLICK);
		image = game->getTexture(BTNSLOTCLICK);
	}
	rectT = { 150,150,500,500 };
	posT = { 800, 800 };
	rectI = { 850,850,500,500 };
	posI = { 600,0 };

	Button* menu = new Button(this, 300, 300, 300, 300, game->getTexture(UICHIP2));
	menu->connect([this] {game->replace(new Menu(game));});
	addObjects(menu);
	addEventListener(menu);
}

void FinalMenu::update() {
	Vector2D t = lerp({ rectT.x,rectT.y }, posT);
	rectT.x += t.getX();
	rectT.y += t.getY();

	Vector2D i = lerp({ rectI.x,rectI.y }, posI);
	rectI.x += i.getX();
	rectI.y += i.getY();

	GameState::update();
}
void FinalMenu::render() const {
	text->render(rectT);
	image->render(rectI);
	GameState::render();
}

Vector2D<float> FinalMenu::lerp(Vector2D<> origen, Vector2D<> destino) {
	Vector2D<int> v = (destino - origen);
	return {v.getX() * 0.01f, v.getY() * 0.01f};
}
