#include "Button.h"
#include "Game.h"
#include "BattleManager.h"
#include "Peleas.h"
#include <thread>

Peleas::Peleas(Game* game) : GameState(game), _battleM(new BattleManager()), dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", 24))) {
    if (_battleM->loadFightersFromJSON("peleadores.json") && _battleM->loadMatchupsFromJSON("../DeathToken/matchups.json"))
    {
        //std::thread BattleThread([this]() {_battleM->StartBattle();});
        //BattleThread.detach();
        
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

    GameState::render();
}