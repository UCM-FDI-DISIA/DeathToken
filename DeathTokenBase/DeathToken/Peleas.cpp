#include "award.h"
#include "battleManager.h"
#include "button.h"
#include "game.h"
#include "peleas.h"
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
	, dialog(new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f))* Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f))* Game::WIN_HEIGHT, true, false, 400, 180))
	, _battleM(nullptr)
	, nombre1(nullptr)
	, nombre2(nullptr)
	, Cuota1(nullptr)
	, Cuota2(nullptr)
	, Animo1(nullptr)
	, Animo2(nullptr)
	, Apuesta1(nullptr)
	, Apuesta2(nullptr)
	, fighter1bar(nullptr)
	, fighter2bar(nullptr)
	, ui(new UIPeleas(game, this))
	, bet(new HUDBet(this, false))
	, bet1(new ButtonPeleas(this, game, ui, static_cast<int>(APUESTA1X* Game::WIN_WIDTH), static_cast<int>((CUOTAY + ESPACIO * 2.5f)* Game::WIN_HEIGHT), 200, 200, nullptr))
	, bet2(new ButtonPeleas(this, game, ui, static_cast<int>(APUESTA2X* Game::WIN_WIDTH), static_cast<int>((CUOTAY + ESPACIO * 2.5f)* Game::WIN_HEIGHT), 200, 200, nullptr))
	, state(FSState::CARDS)
	, apuesta1(0)
	, apuesta2(0)
{
	_battleM = new BattleManager(dialog, game);

	_battleM->StartBattle();
	nombre1 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA1X * Game::WIN_WIDTH),
		static_cast<int>(NOMBRESY * Game::WIN_HEIGHT));

	nombre2 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA2X * Game::WIN_WIDTH),
		static_cast<int>(NOMBRESY * Game::WIN_HEIGHT));

	Cuota1 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA1X * Game::WIN_WIDTH),
		static_cast<int>(CUOTAY * Game::WIN_HEIGHT));

	Cuota2 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA2X * Game::WIN_WIDTH),
		static_cast<int>(CUOTAY * Game::WIN_HEIGHT));

	Animo1 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA1X * Game::WIN_WIDTH),
		static_cast<int>((CUOTAY + ESPACIO) * Game::WIN_HEIGHT));

	Animo2 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA2X * Game::WIN_WIDTH),
		static_cast<int>((CUOTAY + ESPACIO) * Game::WIN_HEIGHT));

	Apuesta1 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA1X * Game::WIN_WIDTH),
		static_cast<int>((CUOTAY + ESPACIO * 2) * Game::WIN_HEIGHT));

	Apuesta2 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_BIG),
		static_cast<int>(APUESTA2X * Game::WIN_WIDTH),
		static_cast<int>((CUOTAY + ESPACIO * 2) * Game::WIN_HEIGHT));
	nombre1->showMessage(_battleM->getFigther1().getName());
	nombre2->showMessage(_battleM->getFigther2().getName());

	// Mostrar los valores formateados
	Cuota1->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility())));
	Cuota2->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther2().getOdds(_battleM->getFigther2().getAbility())));
	Animo1->showMessage("Animo: " + _battleM->getFigther1().getStringMindset());
	Animo2->showMessage("Animo: " + _battleM->getFigther2().getStringMindset());
	Apuesta1->showMessage("Apuesta: ");
	Apuesta2->showMessage("Apuesta: ");

	addEventListener((EventHandler*)dialog);
	addEventListener(bet1);
	addEventListener(bet2);
	addObjects(bet1);
	addObjects(bet2);
	bet->refresh();
}

void Peleas::setCards() {
	// Mostrar los valores formateados
	nombre1->showMessage(_battleM->getFigther1().getName(), true);
	nombre2->showMessage(_battleM->getFigther2().getName(), true);
	Cuota1->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility())), true);
	Cuota2->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther2().getOdds(_battleM->getFigther2().getAbility())), true);
	Animo1->showMessage("Animo: " + _battleM->getFigther1().getStringMindset(), true);
	Animo2->showMessage("Animo: " + _battleM->getFigther2().getStringMindset(), true);
	Apuesta1->showMessage("Apuesta: ", true);
	Apuesta2->showMessage("Apuesta: ", true);
}

void Peleas::StartBattle()
{
	if (state == FSState::FIGHT) {
		return;
	}
	state = FSState::FIGHT;
	SDL_RenderClear(game->getRenderer());
	dialog->setX(Game::WIN_WIDTH / 3);
	dialog->setY(3 * Game::WIN_HEIGHT / 4);
	dialog->setWidth(Game::WIN_WIDTH / 3);
	dialog->resetHistory();
	// Configuración de las barras de vida
	SDL_Renderer* renderer = game->getRenderer();

	// Barra de vida del luchador 1 (izquierda)
	int barWidth = Game::WIN_WIDTH / 3;
	int barHeight = 20;
	int margin = 20;

	fighter1bar = new BarraVida(this,
		renderer,
		margin,
		margin,
		barWidth,
		barHeight,
		_battleM->getFigther1().getMaxHealth(),  // Usar vida máxima real
		{ 0, 255, 0, 255 },
		{ 70, 70, 70, 255 },
		false);

	fighter2bar = new BarraVida(this,
		renderer,
		Game::WIN_WIDTH - barWidth - margin,
		margin,
		barWidth,
		barHeight,
		_battleM->getFigther2().getMaxHealth(),
		{ 0, 255, 0, 255 },  // Usar vida máxima real
		{ 70, 70, 70, 255 },
		true);
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
		SDL_Rect fondo2;
		fondo2.x = fondo2.y = 0;
		fondo2.h = Game::WIN_HEIGHT;
		fondo2.w = Game::WIN_WIDTH;
		game->getTexture(PELEASRING)->render(fondo2);
		dialog->render();
		fighter1bar->render();
		fighter2bar->render();
		break;
	default:
		break;
	}
	GameState::render();
}

namespace Variables_Peleas {
	int lastUpdate = 0;
}



void
Peleas::update() {
	uint currentTime = SDL_GetTicks();
	switch (state)
	{
	case FSState::CARDS:
		break;
	case FSState::FIGHT:
		if (_battleM->getBattleState() != BattleState::END) {
			_battleM->Update(static_cast<float>(currentTime - Variables_Peleas::lastUpdate));
			fighter1bar->establecerValor(_battleM->getFigther1().getHealth());
			fighter2bar->establecerValor(_battleM->getFigther2().getHealth());
			fighter1bar->updateColorBasedOnHealth(static_cast<float>(_battleM->getFigther1().getHealth()), (_battleM->getFigther1().getMaxHealth()));
			fighter2bar->updateColorBasedOnHealth(static_cast<float>(_battleM->getFigther2().getHealth()), (_battleM->getFigther2().getMaxHealth()));
		}
		else {
			if (apuesta1 > 0 && _battleM->getFigther1().isAlive()) {
				game->push(new Award(game, this, apuesta1, static_cast<long>(apuesta1 * _battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility()))));
			}
			else if (apuesta2 > 0) {
				game->push(new Award(game, this, apuesta2, static_cast<long>(apuesta2 * _battleM->getFigther2().getOdds(_battleM->getFigther1().getAbility()))));
			}
			state = FSState::CARDS;
			_battleM->StartBattle();
			dialog->resetHistory();
			setCards();
			bet1->clear();
			bet2->clear();
			bet->update();
			bet->refresh();
		}

		break;
	default:
		break;
	}
	apuesta1 = bet1->getBet();
	apuesta2 = bet2->getBet();
	dialog->update(static_cast<float>(currentTime - Variables_Peleas::lastUpdate));
	Variables_Peleas::lastUpdate = currentTime;
	GameState::update();

}