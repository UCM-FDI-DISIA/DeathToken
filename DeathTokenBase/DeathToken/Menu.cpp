#include "Menu.h"
#include "Game.h"
#include "Player.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 6.8, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 8, yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 12.2;
	PlayerEconomy::EconomyInitialize();
	//Baccarat button
	baccarat = new Button(this,(int) xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(BACCARATBUT));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { gameChanger(new Baccarat(getGame())); });

	slots = new Button(this, (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(SLOTSBUT));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { gameChanger(new Slots(getGame())); });

	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 4.0;
	xBut = Game::WIN_WIDTH * 3.0 / 4.0 - Game::WIN_WIDTH / 25.0; yBut = Game::WIN_HEIGHT / 4.0 + Game::WIN_HEIGHT / 25.0;
	//Marbles button
	marbles = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(CANICASBUT));
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() { gameChanger(new MarblesInsanity(getGame())); });

	fights = new Button(this, (Game::WIN_WIDTH / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(PELEASBUT));
	addObjects(fights);
	addEventListener(fights);
	fights->connect([this]() { gameChanger(new Baccarat(getGame())); });

	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2 - (Game::WIN_WIDTH / 10) / 2, Game::WIN_HEIGHT / 2 }, game->getTexture(GHOST));
		addObjects(ghost);
		addEventListener(ghost);
	}

	hud = new HUDLobby(this);
}

void Menu::gameChanger(GameState* juego) {
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
				hit = true;
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
	fights->Button::getHover() = fights->playerHovered(playerRect);
}

//para que cuando intersecten player y button de a entre y entre en el boton
void Menu::handleEvent(const SDL_Event& event) {
	//GameState::handleEvent(event); //en principio evita repeticiones de codigo pero funciona igual sin esto

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {//return es el enter
		if (baccarat->Button::getHover()) baccarat->Button::getCallback();
		else if (slots->Button::getHover()) slots->Button::getCallback();
		else if (marbles->Button::getHover()) marbles->Button::getCallback();
		else if (fights->Button::getHover()) fights->Button::getCallback();
	}
}
