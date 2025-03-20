#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"
#include <thread>
#include <string>
#include <iomanip>
#include <sstream>

const int APUESTA1X = 330 + 250;
const int APUESTA2X = 870 + 250;
const int NOMBRESY = 140;
const int CUOTAY = 445;
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

Peleas::Peleas(Game* game) 
    : GameState(game)
    , _battleM(new BattleManager())
    , dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", Game::FONTBIGSIZE), 800, 200, true, false)) 
    , nombre1(nullptr)
    , nombre2(nullptr)
    , Cuota1(nullptr)
    , Cuota2(nullptr)
    , Animo1(nullptr)
    , Animo2(nullptr)
    , Apuesta1(nullptr)
    , Apuesta2(nullptr)
    , autoEnable(nullptr)
{

    if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json"))
    {
        _battleM->StartBattle();
        //std::thread BattleThread([this]() {_battleM->StartBattle();});
        //BattleThread.detach();

        nombre1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X, NOMBRESY);
        nombre2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X, NOMBRESY);
        Cuota1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X, CUOTAY);
        Cuota2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X, CUOTAY);
        Animo1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X, CUOTAY + ESPACIO);
        Animo2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X, CUOTAY + ESPACIO);
        Apuesta1 = new DialogueBox(game->getRenderer(), Game::font, APUESTA1X, CUOTAY + ESPACIO * 2);
        Apuesta2 = new DialogueBox(game->getRenderer(), Game::font, APUESTA2X, CUOTAY + ESPACIO * 2);

        nombre1->showMessage(_battleM->getFigther1().getName());
        nombre2->showMessage(_battleM->getFigther2().getName());

        // Mostrar los valores formateados
        Cuota1->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther1().getOdds(_battleM->getFigther2().getAbility())));
        Cuota2->showMessage("Cuota: 1 : " + formatOdds(_battleM->getFigther2().getOdds(_battleM->getFigther2().getAbility())));
        Animo1->showMessage("Animo: " + _battleM->getFigther1().getStringMindset());
        Animo2->showMessage("Animo: " + _battleM->getFigther2().getStringMindset());
        Apuesta1->showMessage("Apuesta: ");
        Apuesta2->showMessage("Apuesta: ");

        dialog->showMessage("¿Qué Mejoramos ? ✅ Separación clara entre lógica(updateDialog()) y renderizado(renderDialog()) ✅ Sistema más modular y fácil de mantener ✅ Posibilidad de agregar más mejoras fácilmente Este sistema es mucho más eficiente y escalable.🚀 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
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
    GameState::render();
}

int lastUpdate = 0;
SDL_Event event;

void
Peleas::update() {
    SDL_PollEvent(&event);
    dialog->handleEvent(event);

    uint currentTime = SDL_GetTicks();
    dialog->update(currentTime - lastUpdate);
    lastUpdate = currentTime;
    GameState::update();
    
}