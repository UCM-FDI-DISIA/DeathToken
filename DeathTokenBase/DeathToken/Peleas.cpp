#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"

Peleas::Peleas(Game* game) : GameState(game) , _battleM(new BattleManager()) {
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

		addEventListener((EventHandler*) dialog);
	}
}

void Peleas::StartBattle()
{
	if (state == FSState::FIGHT) {
		return;
	}
	state = FSState::FIGHT;
	SDL_RenderClear(game->getRenderer());
	dialog->SetX(Game::WIN_WIDTH / 3);
	dialog->SetY(3 * Game::WIN_HEIGHT / 4);
	dialog->SetW(Game::WIN_WIDTH / 3);
	dialog->ResetHistory();
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
                            _battleM->getFigther1().getMaxHealth(),
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
		dialog->render();
        fighter1bar->render();
    fighter2bar->render();
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
                fighter1bar->establecerValor(_battleM->getFigther1().getHealth());
                fighter2bar->establecerValor(_battleM->getFigther2().getHealth());
                 fighter1bar->updateColorBasedOnHealth(_battleM->getFigther1().getHealth(), _battleM->getFigther1().getMaxHealth());
                 fighter2bar->updateColorBasedOnHealth(_battleM->getFigther2().getHealth(), _battleM->getFigther2().getMaxHealth());
		}
		break;
	default:
		break;
	}
	dialog->update(currentTime - lastUpdate);
	lastUpdate = currentTime;
	GameState::update();

}