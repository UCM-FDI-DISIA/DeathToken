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
        dialog->showMessage("Buenas a todos y bienvenidos a peleas reanimadas");
        dialog->showMessage("Buenas a todos y bienvenidos a peleas reanimadas");
        dialog->showMessage("Buenas a todos");
    }

}
void
Peleas::render() const {

    dialog->render(); 
}