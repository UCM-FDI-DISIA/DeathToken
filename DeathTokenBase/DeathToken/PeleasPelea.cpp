#include "PeleasPelea.h"
#include "Game.h"
PeleasPelea::PeleasPelea(Game* game)
    : GameState(game)
    , _battleM(new BattleManager())
    , dialog(new DialogueBox(game->getRenderer(), TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", Game::FONTSMALLSIZE), 800, 200, true, false))
{

}
