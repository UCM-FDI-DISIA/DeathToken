#include "Menu.h"
#include "Game.h"
#include "Player.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	//Widht, height, position baccarat button
	int wBut = Game::WIN_WIDTH / 6.8, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 8, yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 12.2;
	//Baccarat button
	baccarat = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(BACCARATBUT));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { gameChanger(new Baccarat(getGame())); });

	slots = new Button(this, (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(SLOTSBUT));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { gameChanger(new Baccarat(getGame())); });

	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 4;
	xBut = Game::WIN_WIDTH * 3 / 4 - Game::WIN_WIDTH / 25; yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 25;
	//Marbles button
	marbles = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(CANICASBUT));
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() { gameChanger(new Marbles(getGame())); });

	figths = new Button(this, (Game::WIN_WIDTH / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(PELEASBUT));
	addObjects(figths);
	addEventListener(figths);
	figths->connect([this]() { gameChanger(new Baccarat(getGame())); });

	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2 - (Game::WIN_WIDTH / 10) / 2, Game::WIN_HEIGHT / 2 }, game->getTexture(MARIO));
		addObjects(ghost);
		addEventListener(ghost);
	}
}

void Menu::gameChanger(GameState* g) {
	game->push(g);
}

void Menu::render() const {
	texture->render();
	GameState::render();
}
