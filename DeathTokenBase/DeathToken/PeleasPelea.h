#pragma once
#include "gameState.h"
#include "BattleManager.h"
#include "Game.h"


class PeleasPelea : public GameState
{
    PeleasPelea(Game* game);
    ~PeleasPelea() {
        delete _battleM;
        _battleM = nullptr;
        delete dialog;
        dialog = nullptr;
    }
   /* void render() const override;
    void update() override;*/
private:
    BattleManager* _battleM;
    DialogueBox* dialog;

};

