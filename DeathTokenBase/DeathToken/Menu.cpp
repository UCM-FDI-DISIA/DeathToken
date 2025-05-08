#include "checkML.h"
#include "menu.h"
#include "game.h"
#include "player.h"



Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {
	//Widht, height, position baccarat button
	double wBut = Game::WIN_WIDTH / 6.8, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 8, yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 12.2;
	//HUDManager::getHudBet()->refresh();
	eco = new PlayerEconomy();
	eco->EconomyInitialize();

	//Baccarat button
	baccarat = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(BACCARATBUT), (int)wBut, (int)hBut);
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() {
		gameChanger(baccaratState = new Baccarat(getGame()));
		if (tutorialBaccarat)//Entra una vez y cuando se pone en false no vuelve a entrar sin pulsar boton info
		{
			tutorialBaccarat = false;
			baccaratState->showTutorial();
		}
		});
	obstaculos.push_back(cambiarColisiones(baccarat->getCollisionRect()));

	wBut = Game::WIN_WIDTH / 9; hBut = Game::WIN_HEIGHT / 9;
	xBut = (Game::WIN_WIDTH * 7 / 8) - (Game::WIN_WIDTH / 9) / 2; yBut = (Game::WIN_HEIGHT * 3 / 4);
	slots = new Mesa(this, { (int)xBut,(int)yBut}, game->getTexture(SLOTSBUT),(int)wBut ,(int)hBut );
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() { gameChanger(new SlotsNormal(getGame()));});
	obstaculos.push_back(cambiarColisiones(slots->getCollisionRect()));

	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 4.0;
	xBut = Game::WIN_WIDTH * 3.0 / 4.0 - Game::WIN_WIDTH / 25.0; yBut = Game::WIN_HEIGHT / 4.0 + Game::WIN_HEIGHT / 25.0;
	//Marbles button
	marbles = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(CANICASBUT), (int)wBut, (int)hBut);
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() { gameChanger(new Marbles(getGame(), {0,0,0,0})); });
	obstaculos.push_back(cambiarColisiones(marbles->getCollisionRect()));

	fights = new Mesa(this, { (Game::WIN_WIDTH / 8) - (Game::WIN_WIDTH / 9) / 2, (Game::WIN_HEIGHT * 3 / 4) }, game->getTexture(PELEASBUT), Game::WIN_WIDTH / 9, Game::WIN_HEIGHT / 9);
	addObjects(fights);
	addEventListener(fights);
	fights->connect([this]() { gameChanger(new Peleas(getGame())); });
	obstaculos.push_back(cambiarColisiones(fights->getCollisionRect()));

	//Widht, height, position roulette button
	wBut = Game::WIN_WIDTH / 5.33; hBut = Game::WIN_HEIGHT / 5.967;
	xBut = Game::WIN_WIDTH / 2.0 - wBut / 2; yBut = 0.0;
	roulette = new Button(this, (int)xBut, (int)yBut, (int)wBut, (int)hBut, game->getTexture(ROULETTEBUT));
	addObjects(roulette);
	addEventListener(roulette);
	roulette->connect([this]() { gameChanger(new rouletteChoose(getGame(), eco)); });

	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2 - (Game::WIN_WIDTH / 10) / 2, Game::WIN_HEIGHT / 2 }, game->getTexture(GHOST), this);
		addObjects(ghost);
		addEventListener(ghost);
	}

	//Boundries
	SDL_Rect boundry1;
	boundry1.h = Game::WIN_HEIGHT;
	boundry1.w = (85.0f / 1920.0f) * Game::WIN_WIDTH;
	boundry1.x = 0;
	boundry1.y = 0;
	obstaculos.push_back(boundry1);

	SDL_Rect boundry2;
	boundry2.h = (180.0f / 1080.0f) * Game::WIN_HEIGHT;
	boundry2.w = Game::WIN_WIDTH;
	boundry2.x = 0;
	boundry2.y = 0;
	obstaculos.push_back(boundry2);

	SDL_Rect boundry3;
	boundry3.h = Game::WIN_HEIGHT;
	boundry3.w = (85.0f / 1920.0f) * Game::WIN_WIDTH;
	boundry3.x = Game::WIN_WIDTH - boundry3.w;
	boundry3.y = 0;
	obstaculos.push_back(boundry3);

	SDL_Rect boundry4;
	boundry4.h = 100.0f;
	boundry4.w = Game::WIN_WIDTH;
	boundry4.x = 0;
	boundry4.y = Game::WIN_HEIGHT;
	obstaculos.push_back(boundry4);

	hud = new HUDLobby(this);

}
Menu::~Menu() {
	delete eco;

}

void Menu::gameChanger(GameState* juego) {
	if (eco->getInsanity() > 0)
	{
		if (typeid(*juego) == typeid(Baccarat)) {
			juego = new BaccaratInsanityManager(getGame());
		}
		else if (typeid(*juego) == typeid(Marbles)) {
			juego = new MarblesInsanity(getGame());

		}
		else if (typeid(*juego) == typeid(SlotsNormal)) {
			juego = new SlotsInsanity(getGame());
		}
		/*else if (typeid(*juego) == typeid(PeleasReanimadas)) {

		}*/
	}
	game->push(juego);

}

void Menu::render() const {
	texture->render();
	GameState::render();

}

void Menu::update() {//detecto interseciones player/button
	GameState::update();

	ghost->collision(obstaculos);

	SDL_Rect playerRect = ghost->getRect(); //cojo el rect del player

	SDL_Rect _slot = slots->getCollisionRect();
	bool intersectSlots = SDL_HasIntersection(&playerRect, &_slot);
	slots->setHover(intersectSlots);

	SDL_Rect _baccarat = baccarat->getCollisionRect();
	bool intersectBaccarat = SDL_HasIntersection(&playerRect, &_baccarat);
	baccarat->setHover(intersectBaccarat);

	SDL_Rect _marbles = marbles->getCollisionRect();
	bool intersectMarbles = SDL_HasIntersection(&playerRect, &_marbles);
	marbles->setHover(intersectMarbles);

	SDL_Rect _fights = fights->getCollisionRect();
	bool intersectFights = SDL_HasIntersection(&playerRect, &_fights);
	fights->setHover(intersectFights);

}

//para que cuando intersecten player y button de a entre y entre en el boton
void Menu::handleEvent(const SDL_Event& event) {
	GameState::handleEvent(event); //en principio evita repeticiones de codigo pero funciona igual sin esto
}
SDL_Rect Menu::cambiarColisiones(SDL_Rect colJuego) {
	SDL_Rect aux = colJuego;
	int fix = 50;
	aux.w -= fix;
	aux.h -= fix;
	aux.x += fix / 2;
	aux.y += fix / 2;
	return aux;
}
