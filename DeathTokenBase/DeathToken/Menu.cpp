#include "checkML.h"
#include "finalMenu.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "soundManager.h"


Menu::Menu(Game* game) : GameState(game), texture(game->getTexture(BACKGROUND)) {

	eco = new PlayerEconomy();
	eco->EconomyInitialize();

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

	double wBut = Game::WIN_WIDTH / 6.8, hBut = Game::WIN_HEIGHT / 4.5,
		xBut = Game::WIN_WIDTH / 4 - Game::WIN_WIDTH / 8, yBut = Game::WIN_HEIGHT / 4 + Game::WIN_HEIGHT / 4.0;
	//Baccarat button
	baccarat = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(BACCARATBUT), (int)wBut, (int)hBut);
	addObjects(baccarat);
	addEventListener(baccarat);
	baccarat->connect([this]() {
		baccaratState = gameSelec(0);
		getGame()->push(baccaratState);
		auto& soundManager = SoundManager::obtenerInstancia();
		soundManager.reproducirEfecto("BaccaratIntro");

		if (tutorialBaccarat)//Entra una vez y cuando se pone en false no vuelve a entrar sin pulsar boton info
		{
			tutorialBaccarat = false;
			baccaratState->showTutorial();
		}
		});
	obstaculos.push_back(cambiarColisiones(baccarat->getCollisionRect()));

	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 3.5;
	xBut = Game::WIN_WIDTH * 3.0 / 4.75; yBut = Game::WIN_HEIGHT / 1.4f + Game::WIN_HEIGHT / 4.0;
	slots = new Mesa(this, { (int)xBut,(int)yBut }, game->getTexture(SLOTSBUT), (int)wBut, (int)hBut);
	addObjects(slots);
	addEventListener(slots);
	slots->connect([this]() {
		slotsState = gameSelec(1);
		getGame()->push(slotsState);
		auto& soundManager = SoundManager::obtenerInstancia();
		soundManager.reproducirEfecto("SlotsIntro");

		if (tutorialSlots)//Entra una vez y cuando se pone en false no vuelve a entrar sin pulsar boton info
		{
			tutorialSlots = false;
			slotsState->showTutorial();
		}
		});
	obstaculos.push_back(cambiarColisiones(slots->getCollisionRect()));

	//Widht, height, position marbles button
	wBut = Game::WIN_WIDTH / 5.2; hBut = Game::WIN_HEIGHT / 4.0;
	xBut = Game::WIN_WIDTH * 3.0 / 4.0 - Game::WIN_WIDTH / 25.0; yBut = Game::WIN_HEIGHT / 4.0 + Game::WIN_HEIGHT / 4.0;
	//Marbles button
	marbles = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(CANICASBUT), (int)wBut, (int)hBut);
	addObjects(marbles);
	addEventListener(marbles);
	marbles->connect([this]() {
		marbleState = gameSelec(2);
		getGame()->push(marbleState);
		auto& soundManager = SoundManager::obtenerInstancia();
		soundManager.reproducirEfecto("MarblesIntro");
		if (tutorialMarbles) {
			tutorialMarbles = false;
			marbleState->showTutorial();
		}
		});
	obstaculos.push_back(cambiarColisiones(marbles->getCollisionRect()));

	wBut = Game::WIN_WIDTH / 5.98; hBut = Game::WIN_HEIGHT / 3.418;
	xBut = Game::WIN_WIDTH * 3.0 / 15.5; yBut = Game::WIN_HEIGHT / 1.4f + Game::WIN_HEIGHT / 4.0;
	fights = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(PELEASBUT), (int)wBut, (int)hBut);
	addObjects(fights);
	addEventListener(fights);
	fights->connect([this]()
		{
			peleasState = gameSelec(3);
			getGame()->push(peleasState);
			auto& soundManager = SoundManager::obtenerInstancia();
			soundManager.reproducirEfecto("FightsIntro");

			if (tutorialFights) //Entra una vez y cuando se pone en false no vuelve a entrar sin pulsar boton info
			{
				tutorialFights = false;
				peleasState->showTutorial();
			}
		});
	obstaculos.push_back(cambiarColisiones(fights->getCollisionRect()));

	//Widht, height, position roulette button
	wBut = Game::WIN_WIDTH / 3.549; hBut = Game::WIN_HEIGHT / 3.967;
	xBut = Game::WIN_WIDTH / 2.0 - wBut / 2; yBut = Game::WIN_HEIGHT * (200.0 / 1080.0);
	roulette = new Mesa(this, { (int)xBut, (int)yBut }, game->getTexture(ROULETTEBUT), (int)wBut, (int)hBut);
	addObjects(roulette);
	addEventListener(roulette);
	roulette->connect([this]() { getGame()->push(new RouletteChoose(getGame())); });
	obstaculos.push_back(cambiarColisiones(roulette->getCollisionRect()));

	if (ghost == nullptr) {
		ghost = new Player(this, { Game::WIN_WIDTH / 2 - (Game::WIN_WIDTH / 10) / 2, Game::WIN_HEIGHT / 2 }, game->getTexture(GHOST), this);
		addObjects(ghost);
		addEventListener(ghost);
	}

	hud = new HUDLobby(this, false);
	HUDManager::getHudLobby()->refresh();
}
Menu::~Menu() {
	delete eco;
}

GameState*
Menu::gameSelec(int id) {
	GameState* game = nullptr;
	if (eco->getInsanity() == 0)
	{
		switch (id)
		{
		case 0:
			game = new Baccarat(getGame());
			break;
		case 1:
			game = new SlotsNormal(getGame());
			break;
		case 2:
			game = new Marbles(getGame(), { 0,0,0,0 }, false);
			break;
		case 3:
			game = new Peleas(getGame());
			break;
		}
	}
	else
	{
		switch (id)
		{
		case 0:
			game = new BaccaratInsanityManager(getGame());
			break;
		case 1:
			game = new SlotsInsanity(getGame());
			if (tutorialSlotsLocura) {
				tutorialSlots = true;
				tutorialSlotsLocura = false;
			}
			break;
		case 2:
			game = new MarblesInsanity(getGame());
			break;
		case 3:
			game = new PeleasInsanity(getGame());
			break;
		}
	}
	return game;
}

void Menu::render() const {
	texture->render();
	GameState::render();

}

void Menu::update() {//detecto interseciones player/button
	if (PlayerEconomy::getBlueSouls() <= 0) {
		game->stop();
		game->pushState(new FinalMenu(game, false));
	}
	else {
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

		SDL_Rect _roulette = roulette->getCollisionRect();
		bool intersectRoulette = SDL_HasIntersection(&playerRect, &_roulette);
		roulette->setHover(intersectRoulette);
	}
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
