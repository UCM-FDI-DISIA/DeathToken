#include "ui.h"
#include "EscenaTutorial.h"
#include "SoundManager.h"
#include "baccarat.h"
#include "game.h"
#include "marbles.h"
#include "marblesInsanity.h"
#include "peleas.h"
#include "rouletteChoose.h"
#include "rouletteScene.h"
#include "slots.h"
#include "tutorial.h"
#include <iostream>

UI::UI(GameState* gS, Game* game)
  : gS(gS)
  , game(game)
  , onBet(false)
  , chipOnUse(0)
  , chipPage(0)
{
  exit = new ButtonUI(gS,
                      relativeX(50.0f),
                      relativeY(49.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIEXIT),
                      game->getTexture(UIEXITCLCK));
  gS->addObjects(exit);
  gS->addEventListener(exit);
  exit->connect([this]() { OnExit(); });

  go = new ButtonUI(gS,
                    relativeX(1697.0f),
                    relativeY(858.0f),
                    relativeX(173.0f),
                    relativeY(173.0f),
                    game->getTexture(UIGO),
                    game->getTexture(UIGOCLCK));
  gS->addObjects(go);
  gS->addEventListener(go);
  go->connect([this]() { OnGo(); });

  arrowL = new ButtonUI(gS,
                        relativeX(230.0f),
                        relativeY(913.5f),
                        relativeX(97.0f),
                        relativeY(109.0f),
                        game->getTexture(UIARROWL),
                        game->getTexture(UIARROWLCLCK));
  gS->addObjects(arrowL);
  gS->addEventListener(arrowL);
  arrowL->connect([this]() { OnArrow(true); });

  arrowR = new ButtonUI(gS,
                        relativeX(897.0f),
                        relativeY(913.5f),
                        relativeX(97.0f),
                        relativeY(109.0f),
                        game->getTexture(UIARROWR),
                        game->getTexture(UIARROWRCLCK));
  gS->addObjects(arrowR);
  gS->addEventListener(arrowR);
  arrowR->connect([this]() { OnArrow(false); });

  chips = std::vector<ButtonChip*>(4);
  chips[0] = new ButtonChip(gS,
                            this,
                            relativeX(367.0f),
                            relativeY(918.0f),
                            relativeX(100.0f),
                            relativeY(104.0f),
                            0,
                            1,
                            25,
                            500,
                            game->getTexture(UICHIP1),
                            game->getTexture(UICHIP25),
                            game->getTexture(UICHIP500));
  chips[0]->setOnUse(true);
  gS->addObjects(chips[0]);
  gS->addEventListener(chips[0]);
  chips[0]->connect([this]() {});

  chips[1] = new ButtonChip(gS,
                            this,
                            relativeX(497.0f),
                            relativeY(918.0f),
                            relativeX(100.0f),
                            relativeY(104.0f),
                            1,
                            2,
                            50,
                            1000,
                            game->getTexture(UICHIP2),
                            game->getTexture(UICHIP50),
                            game->getTexture(UICHIP1000));
  gS->addObjects(chips[1]);
  gS->addEventListener(chips[1]);
  chips[1]->connect([this]() {});

  chips[2] = new ButtonChip(gS,
                            this,
                            relativeX(627.0f),
                            relativeY(918.0f),
                            relativeX(100.0f),
                            relativeY(104.0f),
                            2,
                            5,
                            100,
                            2000,
                            game->getTexture(UICHIP5),
                            game->getTexture(UICHIP100),
                            game->getTexture(UICHIP2000));
  gS->addObjects(chips[2]);
  gS->addEventListener(chips[2]);
  chips[2]->connect([this]() {});

  chips[3] = new ButtonChip(gS,
                            this,
                            relativeX(757.0f),
                            relativeY(918.0f),
                            relativeX(100.0f),
                            relativeY(104.0f),
                            3,
                            10,
                            200,
                            5000,
                            game->getTexture(UICHIP10),
                            game->getTexture(UICHIP200),
                            game->getTexture(UICHIP5000));
  gS->addObjects(chips[3]);
  gS->addEventListener(chips[3]);
  chips[3]->connect([this]() {});
}

inline int UI::relativeX(const float& n)
{
  return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int UI::relativeY(const float& n)
{
  return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

void UI::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  if (!onBet)
    game->pop();
}

void UI::changeChip(const int& id)
{
  chips[chipOnUse]->setOnUse(false);
  chipOnUse = id;
  chips[chipOnUse]->setOnUse(true);
}

int UI::currentChipValue()
{
  return chips[chipOnUse]->getValue();
}

void UI::OnArrow(const bool& left)
{
  int aux = chipPage;
  if (left && chipPage > 0)
    chipPage--;
  else if (!left && chipPage < 2)
    chipPage++;

  if (chipPage != aux) {
    for (ButtonChip* i : chips) {
      i->changePage(chipPage);
    }
  }
}

UIChips::UIChips(GameState* gS, Game* game)
  : UI(gS, game)
{
  erase = new ButtonUI(gS,
                       relativeX(50.0f),
                       relativeY(905.0f),
                       relativeX(126.0f),
                       relativeY(126.0f),
                       game->getTexture(UIERASE),
                       game->getTexture(UIERASECLCK));
  gS->addObjects(erase);
  gS->addEventListener(erase);
  erase->connect([this]() { OnErase(); });

  info = new ButtonUI(gS,
                      relativeX(1377.0f),
                      relativeY(905.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIINFO),
                      game->getTexture(UIINFOCLCK));
  gS->addObjects(info);
  gS->addEventListener(info);
  info->connect([this]() { OnInfo(); });

  repeat = new ButtonUI(gS,
                        relativeX(1537.0f),
                        relativeY(905.0f),
                        relativeX(126.0f),
                        relativeY(126.0f),
                        game->getTexture(UIREPEAT),
                        game->getTexture(UIREPEATCLCK));
  gS->addObjects(repeat);
  gS->addEventListener(repeat);
  repeat->connect([this]() { OnRepeat(); });
}

UISlots::UISlots(GameState* gS, Game* game, Slots* slot)
  : UI(gS, game)
  , slots(slot)
  , locura(false)
{
  erase = new ButtonUI(gS,
                       relativeX(50.0f),
                       relativeY(905.0f),
                       relativeX(126.0f),
                       relativeY(126.0f),
                       game->getTexture(UIERASE),
                       game->getTexture(UIERASECLCK));
  gS->addObjects(erase);
  gS->addEventListener(erase);
  erase->connect([this]() { OnErase(); });

  info = new ButtonUI(gS,
                      relativeX(1550.0f),
                      relativeY(905.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIINFO),
                      game->getTexture(UIINFOCLCK));
  gS->addObjects(info);
  gS->addEventListener(info);
  info->connect([this]() { OnInfo(); });
}

void UISlots::OnGo()
{
  if (PlayerEconomy::getBet() != 0) {
    auto& soundManager = SoundManager::obtenerInstancia();
    soundManager.reproducirEfecto("PresionaBotonSlots");
    slots->setBetTurno(PlayerEconomy::getBet());
    slots->clear();
    slots->iniciarGiro();
  }
}

void UISlots::OnInfo()
{
  std::vector<Texture*> tut;
  if (locura) {
    tut.push_back(game->getTexture(TUTORIALSLOTSLOC));
  }
  else {
    tut.push_back(game->getTexture(TUTORIALSLOTS));
  }
  game->push(new Tutorial(game, gS, tut));
}

void UISlots::OnErase()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  HUDManager::resetBet();
  slots->clear();
}

UIMarbles::UIMarbles(GameState* gS, Game* game, Marbles* marbles)
  : UIChips(gS, game)
  , marbles(marbles)
{
}

void UIMarbles::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBotonCanicas");
  marbles->startRound();
}

void UIMarbles::OnErase()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  HUDManager::resetBet();
  marbles->clearBets();
}

void UIMarbles::OnRepeat()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  marbles->repeat();
}

void UIMarbles::OnInfo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  std::vector<Texture*> baccaratTutorial = { game->getTexture(
    TUTORIALMARBLES) };
  game->push(new Tutorial(game, gS, baccaratTutorial));
}

UIMarblesInsanity::UIMarblesInsanity(GameState* gS,
                                     Game* game,
                                     MarblesInsanity* marblesI)
  : UIChips(gS, game)
  , marblesI(marblesI)
{
}

void UIMarblesInsanity::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBotonCanicas");
  marblesI->StartRoundTrickster();
}

void UIMarblesInsanity::OnInfo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  std::vector<Texture*> baccaratTutorial = { game->getTexture(
    TUTORIALMARBLESINSANITY) };
  game->push(new Tutorial(game, gS, baccaratTutorial));
}

void UIMarblesInsanity::render() const
{
  info->render();
  go->render();
}

void UIMarblesInsanity::update()
{
  info->update();
  go->update();
}

UIBaccarat::UIBaccarat(GameState* gS, Game* game, Baccarat* baccarat)
  : UIChips(gS, game)
  , baccarat(baccarat)
{
}

void UIBaccarat::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBotonBaccarat");
  baccarat->startRound();
}

void UIBaccarat::OnErase()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  HUDManager::resetBet();
  baccarat->clearBets();
}

void UIBaccarat::OnRepeat()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  baccarat->repeat();
}

void UIBaccarat::OnInfo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  std::vector<Texture*> baccaratTutorial = { game->getTexture(TUTORIAL1),
                                             game->getTexture(TUTORIAL2),
                                             game->getTexture(TUTORIAL3) };
  game->push(new Tutorial(game, gS, baccaratTutorial));
}

UITutorial::UITutorial(GameState* gS, Game* game, size_t tam)
  : gS(gS)
  , game(game)
  , totalPages(tam)
{
  exit = new ButtonUI(gS,
                      relativeX(50.0f),
                      relativeY(49.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIEXIT),
                      game->getTexture(UIEXITCLCK));
  gS->addObjects(exit);
  gS->addEventListener(exit);
  exit->connect([this]() {
    auto& soundManager = SoundManager::obtenerInstancia();
    soundManager.reproducirEfecto("PresionaBoton");
    OnExit();
  });
}

inline int UITutorial::relativeX(const float& n)
{
  return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int UITutorial::relativeY(const float& n)
{
  return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

void UITutorial::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}

ButtonUI* UITutorial::downArrow()
{
  arrowNext = new ButtonUI(gS,
                           relativeX(897.0f),
                           relativeY(963.5f),
                           relativeX(97.0f),
                           relativeY(80.0f),
                           game->getTexture(UIARROWD),
                           game->getTexture(UIARROWDCLCK));
  gS->addObjects(arrowNext);
  gS->addEventListener(arrowNext);

  arrowNext->connect([this]() {
    Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
    if (tutorial) {
      tutorial->nextPage();
    }
  });
  return arrowNext;
}

ButtonUI* UITutorial::upArrow()
{
  arrowBack = new ButtonUI(gS,
                           relativeX(897.0f),
                           relativeY(880.5f),
                           relativeX(97.0f),
                           relativeY(80.0f),
                           game->getTexture(UIARROWU),
                           game->getTexture(UIARROWUCLCK));
  gS->addObjects(arrowBack);
  gS->addEventListener(arrowBack);

  arrowBack->connect([this]() {
    Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
    if (tutorial) {
      tutorial->previousPage();
    }
  });
  return arrowBack;
}

void UIPeleas::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBotonPeleas");
  _peleas->StartBattle();
}

UIRoulette::UIRoulette(GameState* gS, Game* game, RouletteScene* rouletteS)
  : gS(gS)
  , game(game)
  , rouletteS(rouletteS)
{
  exit = new ButtonUI(gS,
                      relativeX(50.0f),
                      relativeY(49.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIEXIT),
                      game->getTexture(UIEXITCLCK));
  gS->addObjects(exit);
  gS->addEventListener(exit);
  exit->connect([this]() { OnExit(); });

  go = new ButtonUI(gS,
                    relativeX(1697.0f),
                    relativeY(858.0f),
                    relativeX(173.0f),
                    relativeY(173.0f),
                    game->getTexture(UIGO),
                    game->getTexture(UIGOCLCK));
  gS->addObjects(go);
  gS->addEventListener(go);
  go->connect([this]() { OnGo(); });
}

void UIRoulette::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}

void UIRoulette::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("RuletaSonido");
  rouletteS->throwRoulette();
}

UIEscenaTutorial::UIEscenaTutorial(GameState* gS, Game* g, EscenaTutorial* tut)
  : UI(gS, g)
  , escenaTutorial(tut)
{
}

void UIEscenaTutorial::OnGo()
{
  if (PlayerEconomy::getBet() != 0 && escenaTutorial->getFase() == 2 &&
      !escenaTutorial->itIsInDIalog()) {
    auto& soundManager = SoundManager::obtenerInstancia();
    soundManager.reproducirEfecto("PresionaBoton");
    escenaTutorial->setBetTurno(PlayerEconomy::getBet());
    escenaTutorial->clear();
    escenaTutorial->iniciaJuego();
  }
}

void UIEscenaTutorial::OnExit()
{
  PlayerEconomy::setBlueSouls(escenaTutorial->getSaldo());
  game->pop();
}

UIRouletteChoose::UIRouletteChoose(GameState* gS,
                                   Game* game,
                                   rouletteChoose* rouletteC)
  : gS(gS)
  , game(game)
  , rouletteC(rouletteC)
{
  exit = new ButtonUI(gS,
                      relativeX(50.0f),
                      relativeY(49.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIEXIT),
                      game->getTexture(UIEXITCLCK));
  gS->addObjects(exit);
  gS->addEventListener(exit);
  exit->connect([this]() { OnExit(); });
}

void UIRouletteChoose::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}

UIScythe::UIScythe(GameState* gS, Game* game, scythe* scytheObj)
  : gS(gS)
  , game(game)
  , s(scytheObj)
{
  exit = new ButtonUI(gS,
                      relativeX(50.0f),
                      relativeY(49.0f),
                      relativeX(126.0f),
                      relativeY(126.0f),
                      game->getTexture(UIEXIT),
                      game->getTexture(UIEXITCLCK));
  gS->addObjects(exit);
  gS->addEventListener(exit);
  exit->connect([this]() { OnExit(); });
}

void UIScythe::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}