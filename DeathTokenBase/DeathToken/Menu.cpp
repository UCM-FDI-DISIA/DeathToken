#include "Menu.h"
#include "Game.h"
#include "Player.h"

#include "Baccarat.h"
#include "SlotsNormal.h"
#include "SlotsLocura.h"
#include "Marbles.h"
#include "marblesInsanity.h"

Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {

	PlayerEconomy::EconomyInitialize();
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 6.8, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 8, yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 12.2;
	PlayerEconomy::EconomyInitialize();
	//Baccarat button
	baccarat = new Button(this,(int) xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(BACCARATBUT));
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() { gameChanger(new BaccaratBet(getGame())); });

	slots = new Button(this, (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9, game->getTexture(SLOTSBUT));
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { gameChanger(new Slots(getGame())); });

	wBut = (125.0f / 1980.f) * Game::WIN_WIDTH; hBut = 125.0f / 1080.0f * Game::WIN_HEIGHT;
	xBut = (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2; yBut = Game::WIN_HEIGHT * 3 / 4;
	_slots = new Mesa(this, { (int)xBut,(int)yBut }, game->getTexture(SLOTSBUT), 0,(int)wBut,(int)hBut,game);
	addObjects(_slots);
	addEventListener(_slots);
	
	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 4.0;
	xBut = Game::WIN_WIDTH * 3.0 / 4.0 - Game::WIN_WIDTH / 25.0; yBut = Game::WIN_HEIGHT / 4.0 + Game::WIN_HEIGHT / 25.0;
	//Marbles button 
	_marbles = new Mesa(this, { (int)xBut,(int)yBut }, game->getTexture(CANICASBUT), 2, (int)wBut, (int)hBut, game);
	addObjects(_marbles);
	addEventListener(_marbles);

	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 9; hBut = Game::WIN_HEIGHT / 9;
	xBut = (Game::WIN_WIDTH / 8) - (Game::WIN_WIDTH / 9) / 2; yBut = (Game::WIN_HEIGHT * 3 / 4);
	//Peleas button 
	_fights = new Mesa(this, { (int)xBut,(int)yBut }, game->getTexture(SLOTSBUT), 3, (int)wBut, (int)hBut, game);
	addObjects(_fights);
	addEventListener(_fights);
	
	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 2 }, game->getTexture(GHOST), this);
		addObjects(ghost);
		addEventListener(ghost);
	}

	//Boundries
	boundry1.h = Game::WIN_HEIGHT;
	boundry1.w = (85.0f /1920.0f) * Game::WIN_WIDTH;
	boundry1.x = 0;
	boundry1.y = 0;
	limites.push_back(boundry1);

	boundry2.h = (180.0f/1080.0f) * Game::WIN_HEIGHT;
	boundry2.w = Game::WIN_WIDTH;
	boundry2.x = 0;
	boundry2.y = 0;
	limites.push_back(boundry2);

	boundry3.h = Game::WIN_HEIGHT;
	boundry3.w = (85.0f / 1920.0f) * Game::WIN_WIDTH;
	boundry3.x = Game::WIN_WIDTH - boundry3.w;
	boundry3.y = 0;
	limites.push_back(boundry3);

	limites.push_back(_slots->getCollisionRect());
	limites.push_back(_fights->getCollisionRect());
	limites.push_back(_marbles->getCollisionRect());
	limites.push_back(_baccarat->getCollisionRect());

	hud = new HUDLobby(this);

	games.push_back(_slots);
	games.push_back(_marbles);
	games.push_back(_fights);
	games.push_back(_baccarat);

	juegos.push_back(_slots->getCollisionRect());
	juegos.push_back(_marbles->getCollisionRect());
	juegos.push_back(_fights->getCollisionRect());
	juegos.push_back(_baccarat->getCollisionRect());
}

void Menu::render() const {
	texture->render();
	GameState::render();

}
void Menu::update() {//detecto interseciones player/button
	GameState::update();

	SDL_Rect playerRect = ghost->getCollisionRect(); //cojo el rect del player
	playerRect.w += 5;
	playerRect.h += 5;

	
	
	for (int i = 0; i < juegos.size(); ++i) {
		if (SDL_HasIntersection(&playerRect, &juegos[i])) {
			games[i]->inGame(true);
		}
		else {
			games[i]->inGame(false);
		}		
	}
}

//para que cuando intersecten player y button de a entre y entre en el boton
void Menu::handleEvent(const SDL_Event& event) {
	if (_baccarat->getHover()) 
		_baccarat->Mesa::handleEvent(event);
	else if (_slots->getHover()) 
		_slots->Mesa::handleEvent(event);
	else if (_marbles->getHover()) 
		_marbles->Mesa::handleEvent(event);
	else if (_fights->getHover()) 
		_fights->Mesa::handleEvent(event);
}
