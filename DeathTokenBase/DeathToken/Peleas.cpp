#include "BattleManager.h"
#include "Button.h"
#include "Game.h"
#include "Peleas.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>

const float APUESTA1X = 400.0f / 1920.0f;
const float APUESTA2X = 1080.0f / 1920.0f;
const float NOMBRESY = 160.0f / 1080.0f;
const float CUOTAY = 545.0f / 1080.0f;
const float ESPACIO = 60.0f / 1080.0f;

std::string formatOdds(float odds) {
	std::ostringstream stream;
	// Aplica formato solo si hay decimales
	if (odds == static_cast<int>(odds)) {
		stream << static_cast<int>(odds);  // Muestra sin decimales si el número es entero
	}
	else {
		stream << std::fixed << std::setprecision(2) << odds;  // Si tiene decimales, muestra 2 decimales
	}
	return stream.str();
}

Peleas::Peleas(Game* game)
	: GameState(game)
	, dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/typo/Ravishing Free.ttf", Game::FONTSMALLSIZE), (25.0f / 1920.0f)* Game::WIN_WIDTH, (870.0f / 1080.0f)* Game::WIN_HEIGHT, true, false, 400, 180))
	, _battleM(nullptr)
	, nombre1(nullptr)
	, nombre2(nullptr)
	, Cuota1(nullptr)
	, Cuota2(nullptr)
	, Animo1(nullptr)
	, Animo2(nullptr)
	, Apuesta1(nullptr)
	, Apuesta2(nullptr)
	, ui(new UIPeleas(game, this))
	, state(FSState::CARDS)
{
	_battleM = new BattleManager(dialog);
	if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json"))
	{
		_battleM->StartBattle();

		nombre1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X * Game::WIN_WIDTH, NOMBRESY * Game::WIN_HEIGHT);
		nombre2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X * Game::WIN_WIDTH, NOMBRESY * Game::WIN_HEIGHT);
		Cuota1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X * Game::WIN_WIDTH, CUOTAY * Game::WIN_HEIGHT);
		Cuota2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X * Game::WIN_WIDTH, CUOTAY * Game::WIN_HEIGHT);
		Animo1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X * Game::WIN_WIDTH, (CUOTAY + ESPACIO) * Game::WIN_HEIGHT);
		Animo2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X * Game::WIN_WIDTH, (CUOTAY + ESPACIO) * Game::WIN_HEIGHT);
		Apuesta1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X * Game::WIN_WIDTH, (CUOTAY + ESPACIO * 2) * Game::WIN_HEIGHT);
		Apuesta2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X * Game::WIN_WIDTH, (CUOTAY + ESPACIO * 2) * Game::WIN_HEIGHT);

		nombre1->showMessage(_battleM->getFigther1().getName());
		nombre2->showMessage(_battleM->getFigther2().getName());

		// Mostrar los valores formateados
		Cuota1->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility())));
		Cuota2->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther2().getOdds(_battleM->getFigther2().getAbility())));
		Animo1->showMessage("Animo: " + _battleM->getFigther1().getStringMindset());
		Animo2->showMessage("Animo: " + _battleM->getFigther2().getStringMindset());
		Apuesta1->showMessage("Apuesta: ");
		Apuesta2->showMessage("Apuesta: ");

	}
}

void Peleas::StartBattle()
{
	if (state == FSState::FIGHT) {
		return;
	}
	state = FSState::FIGHT;
	SDL_RenderClear(game->getRenderer());
	dialog->SetX(Game::WIN_WIDTH / 2);
	dialog->SetY(Game::WIN_HEIGHT / 2);
	dialog->SetW(Game::WIN_HEIGHT / 2);
	dialog->ResetHistory();
}

void
Peleas::render() const {
	switch (state)
	{
	case FSState::CARDS:
		SDL_Rect fondo;
		fondo.x = fondo.y = 0;
		fondo.h = Game::WIN_HEIGHT;
		fondo.w = Game::WIN_WIDTH;
		game->getTexture(PELEASFONDO)->render(fondo);

		SDL_Rect r;
		r.x = r.y = 0;
		r.h = Game::WIN_HEIGHT;
		r.w = Game::WIN_WIDTH;
		game->getTexture(PELEASTARJETAFONDO)->render(r);

		//Aqui falta el sprite de los personajes

		SDL_Rect tarjetas;
		tarjetas.x = tarjetas.y = 0;
		tarjetas.h = Game::WIN_HEIGHT;
		tarjetas.w = Game::WIN_WIDTH;
		game->getTexture(PELEASTARJETAS)->render(tarjetas);

		nombre1->render();
		nombre2->render();
		Cuota1->render();
		Cuota2->render();
		Animo1->render();
		Animo2->render();
		Apuesta1->render();
		Apuesta2->render();

		dialog->render();
		break;
	case FSState::FIGHT:
		dialog->render();
		break;
	default:
		break;
	}
	GameState::render();
}

int lastUpdate = 0;
SDL_Event event;

void
Peleas::update() {
	// Hay que ver como sacarlo de aqui para que las cajas de dialogo puedan 
	// recibir inputs sin dañar la ejecucíon de otras parte del codigo como la ui
	/*SDL_PollEvent(&event);*/
	/*dialog->handleEvent(event);*/

	uint currentTime = SDL_GetTicks();
	switch (state)
	{
	case FSState::CARDS:
		break;
	case FSState::FIGHT:
		if (_battleM->getBattleState() != BattleState::END) {
			_battleM->Update(currentTime - lastUpdate);
		}
		break;
	default:
		break;
	}
	dialog->update(currentTime - lastUpdate);
	lastUpdate = currentTime;
	GameState::update();

}