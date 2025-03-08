#pragma once
#include "gameState.h"
#include <SDL_ttf.h>
#include "DialogueBox.h"
#include "BattleManager.h"
class Peleas : public GameState
{
public:
    Peleas(Game* game);
    ~Peleas() { delete _battleM; delete dialog; }
    void render() const override;
private:
    BattleManager* _battleM;
    DialogueBox* dialog;
};

