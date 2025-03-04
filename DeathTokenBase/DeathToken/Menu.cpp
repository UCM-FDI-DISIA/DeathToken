#include "Menu.h"
#include "Game.h"
#include "Player.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	baccarat = new Button(this, (Game::WIN_WIDTH / 4) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT / 4) + (Game::WIN_HEIGHT / 9) / 2, Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(BACCARATBUT));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	slots = new Button(this, (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(SLOTSBUT));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	marbles = new Button(this, (Game::WIN_WIDTH * 3 / 4) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT / 4) + (Game::WIN_HEIGHT / 9) / 2, Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(CANICASBUT));
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() { cambiaJuego(new Marbles(getGame())); });

	peleas = new Button(this, (Game::WIN_WIDTH / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(PELEASBUT));
	addObjects(peleas);
	addEventListener(peleas);
	peleas->connect([this]() { cambiaJuego(new Baccarat(getGame())); });

	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2 - (Game::WIN_WIDTH / 10) / 2, Game::WIN_HEIGHT/2}, game->getTexture(MARIO));
		addObjects(ghost);
		addEventListener(ghost);
	}
}

void Menu::cambiaJuego(GameState* juego) {
	game->push(juego);
}

void Menu::render() const {
	texture->render();
	GameState::render();
}
Collision Menu::checkCollision(const SDL_Rect& rect, Collision::Target target) {
	Collision col;
	bool hit = false;

	for (sceneObject* obj : objetos) {
		if (!hit) {
			col = obj->hit(rect, target);
			hit = col.result != col.NONE;
			if (target == Collision::PLAYER && col.result == col.OBSTACLE) {
				hit == true;
			}
		}
	}
	if (hit) return col;
	else return col = NO_COLLISION;
}

void Menu::update() {//detecto interseciones player/button
	GameState::update();

	SDL_Rect playerRect = ghost->getRect(); //cojo el rect del player

	baccarat->Button::getHover() = baccarat->playerHovered(playerRect);
	slots->Button::getHover() = slots->playerHovered(playerRect);
	marbles->Button::getHover() = marbles->playerHovered(playerRect);
	peleas->Button::getHover() = peleas->playerHovered(playerRect);
}

//para que cuando intersecten player y button de a entre y entre en el boton
void Menu::handleEvent(const SDL_Event& event) {
	//GameState::handleEvent(event); //en principio evita repeticiones de codigo pero funciona igual sin esto

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {//return es el enter
		if (baccarat->Button::getHover()) baccarat->Button::getCallback();
		else if (slots->Button::getHover()) slots->Button::getCallback();
		else if (marbles->Button::getHover()) marbles->Button::getCallback();
		else if (peleas->Button::getHover()) peleas->Button::getCallback();
	}
}
