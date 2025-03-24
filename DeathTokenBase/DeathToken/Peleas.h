#pragma once
#include "gameState.h"
#include <SDL_ttf.h>
#include "DialogueBox.h"
#include "BattleManager.h"
#include "UI.h"
class Peleas : public GameState
{
public:
    Peleas(Game* game);
   ~Peleas() { 
       delete _battleM;
       _battleM = nullptr;
       delete dialog;
       dialog = nullptr;
       delete nombre1;
       nombre1 = nullptr;
       delete nombre2;
       nombre2 = nullptr;
       delete Cuota1;
       Cuota1 = nullptr;
       delete Cuota2;
       Cuota2 = nullptr;
       delete Animo1;
       Animo1 = nullptr;
       delete Animo2;
       Animo2 = nullptr;
       delete Apuesta1;
       Apuesta1 = nullptr;
       delete Apuesta2;
       Apuesta2 = nullptr;
       delete ui;
       ui = nullptr;
   }
    void render() const override;
    void update() override;
private:
    BattleManager* _battleM;
    DialogueBox* dialog;
    DialogueBox* nombre1;
    DialogueBox* nombre2;
    DialogueBox* Cuota1;
    DialogueBox* Cuota2;
    DialogueBox* Animo1;
    DialogueBox* Animo2;
    DialogueBox* Apuesta1;
    DialogueBox* Apuesta2;
    UIPeleas* ui;

};

