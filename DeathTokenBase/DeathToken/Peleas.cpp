#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"
#include <thread>
#include <string>
#include <iomanip>
#include <sstream>

const int APUESTA1X = 325;
const int APUESTA2X = 865;
const int NOMBRESY = 160;
const int CUOTAY = 500;
const int ESPACIO = 60;

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

Peleas::Peleas(Game* game) : GameState(game), _battleM(new BattleManager()), dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", 24), true)) {

    if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json"))
    {
        _battleM->StartBattle();
        //std::thread BattleThread([this]() {_battleM->StartBattle();});
        //BattleThread.detach();

        nombre1 = new DialogueBox(game->getRenderer(), Game::font);
        nombre2 = new DialogueBox(game->getRenderer(), Game::font);
        Cuota1 = new DialogueBox(game->getRenderer(), Game::font);
        Cuota2 = new DialogueBox(game->getRenderer(), Game::font);
        Animo1 = new DialogueBox(game->getRenderer(), Game::font);
        Animo2 = new DialogueBox(game->getRenderer(), Game::font);
        Apuesta1 = new DialogueBox(game->getRenderer(), Game::font);
        Apuesta2 = new DialogueBox(game->getRenderer(), Game::font);

        nombre1->showMessage(_battleM->getFigther1().getName());
        nombre2->showMessage(_battleM->getFigther2().getName());

        // Mostrar los valores formateados
        Cuota1->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility())));
        Cuota2->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther2().getOdds(_battleM->getFigther2().getAbility())));
        Animo1->showMessage("Animo: " + _battleM->getFigther1().getStringMindset());
        Animo2->showMessage("Animo: " + _battleM->getFigther2().getStringMindset());
        Apuesta1->showMessage("Apuesta: ");
        Apuesta2->showMessage("Apuesta: ");

        dialog->showMessage("¿Qué Mejoramos ? \n ✅ Separación clara entre lógica(updateDialog()) y renderizado(renderDialog()) \n ✅ Sistema más modular y fácil de mantener \n✅ Posibilidad de agregar más mejoras fácilmente Este sistema es mucho más eficiente y escalable.🚀");
        dialog->showMessage("Segundo mensaje");
        std::thread battlethread([this]() {_battleM->ExecuteTurns(_battleM->getCurrentMatchUp());});
        battlethread.detach();
    }
}

void
Peleas::render() const {

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

    SDL_Rect tarjetas;
    tarjetas.x = tarjetas.y = 0;
    tarjetas.h = Game::WIN_HEIGHT;
    tarjetas.w = Game::WIN_WIDTH;
    game->getTexture(PELEASTARJETAS)->render(tarjetas);

    nombre1->render(APUESTA1X, NOMBRESY);
    nombre2->render(APUESTA2X, NOMBRESY);
    Cuota1->render(APUESTA1X, CUOTAY);
    Cuota2->render(APUESTA2X, CUOTAY);
    Animo1->render(APUESTA1X, CUOTAY + ESPACIO);
    Animo2->render(APUESTA2X, CUOTAY + ESPACIO);
    Apuesta1->render(APUESTA1X, CUOTAY + ESPACIO * 2);
    Apuesta2->render(APUESTA2X, CUOTAY + ESPACIO * 2);

    dialog->render(Game::WIN_WIDTH/2,0);
    GameState::render();
}

int lastUpdate = 0;
SDL_Event event;

void
Peleas::update() {
    SDL_PollEvent(&event);
    dialog->handleEvent(event);

    uint currentTime = SDL_GetTicks();
    nombre1->updateDialog(currentTime - lastUpdate);
    nombre2->updateDialog(currentTime - lastUpdate);
    Cuota1->updateDialog(currentTime - lastUpdate);
    Cuota2->updateDialog(currentTime - lastUpdate);
    Animo1->updateDialog(currentTime - lastUpdate);
    Animo2->updateDialog(currentTime - lastUpdate);
    Apuesta1->updateDialog(currentTime - lastUpdate);
    Apuesta2->updateDialog(currentTime - lastUpdate);
    dialog->updateDialog(currentTime - lastUpdate);
    lastUpdate = currentTime;
    GameState::update();
    
}