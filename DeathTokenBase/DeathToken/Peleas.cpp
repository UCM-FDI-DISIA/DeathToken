#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"
#include <thread>
#include <string>

Peleas::Peleas(Game* game) : GameState(game), _battleM(new BattleManager()), dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", 24))) {
    
    TTF_Font* font = nullptr;

    if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json"))
    {
        _battleM->StartBattle();
        font = TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", 32);
        //std::thread BattleThread([this]() {_battleM->StartBattle();});
        //BattleThread.detach();
    }

    nombre1 = DialogueBox(game->getRenderer(), font);
    nombre2 = DialogueBox(game->getRenderer(), font);
    Cuota1 = DialogueBox(game->getRenderer(), font);
    Cuota2 = DialogueBox(game->getRenderer(), font);
    Animo1 = DialogueBox(game->getRenderer(), font);
    Animo2 = DialogueBox(game->getRenderer(), font);
    Apuesta1 = DialogueBox(game->getRenderer(), font);
    Apuesta2 = DialogueBox(game->getRenderer(), font);

    nombre1.showMessage(_battleM->getFigther1().getName());
    nombre2.showMessage(_battleM->getFigther2().getName());
    //Cuota1.showMessage(_battleM->getFigther1().get());
    //Cuota2.showMessage(_battleM->getFigther2().getName());
    Animo1.showMessage("Animo: " + std::to_string(_battleM->getFigther1().getMindset()));
    Animo2.showMessage("Animo: " + std::to_string(_battleM->getFigther2().getMindset()));
    Apuesta1.showMessage("Apuesta: ");
    Apuesta2.showMessage("Apuesta: ");

}
const int;
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

    nombre1.render(325, 160);
    nombre2.render(865, 160);
    //Cuota1.showMessage(_battleM->getFigther1().get());
    //Cuota2.showMessage(_battleM->getFigther2().getName());
    Animo1.render(325, 560);
    Animo2.render(865, 560);
    Apuesta1.render(325, 620);
    Apuesta2.render(865, 620);

    GameState::render();
}