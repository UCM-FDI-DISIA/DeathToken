#include "baccarat.h"
#include "EscenaTutorial.h"
#include "game.h"
#include "marbles.h"
#include "marblesInsanity.h"
#include "peleas.h"
#include "rouletteChoose.h"
#include "rouletteScene.h"
#include "slots.h"
#include "SoundManager.h"
#include "tutorial.h"
#include "ui.h"
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
  exit->connect([this]() {
    OnExit();
  });

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
  gS->addObjectsUI(chips[1]);
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
  gS->addObjectsUI(chips[2]);
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
  gS->addObjectsUI(chips[3]);
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

<<<<<<< Updated upstream
	erase = new ButtonUI(gS, relativeX(50.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIERASE), game->getTexture(UIERASECLCK));
	gS->addObjectsUI(erase);
	gS->addEventListener(erase);
	erase->connect([this]() { OnErase(); });

	info = new ButtonUI(gS, relativeX(1377.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjectsUI(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });

	repeat = new ButtonUI(gS, relativeX(1537.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIREPEAT), game->getTexture(UIREPEATCLCK));
	gS->addObjectsUI(repeat);
	gS->addEventListener(repeat);
	repeat->connect([this]() { OnRepeat(); });
=======
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
>>>>>>> Stashed changes
}

UISlots::UISlots(GameState* gS, Game* game, Slots* slot)
  : UI(gS, game)
  , slots(slot)
  , locura(false)
{
<<<<<<< Updated upstream
	erase = new ButtonUI(gS, relativeX(50.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIERASE), game->getTexture(UIERASECLCK));
	gS->addObjectsUI(erase);
	gS->addEventListener(erase);
	erase->connect([this]() { OnErase(); });

	info = new ButtonUI(gS, relativeX(1550.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjectsUI(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });
=======
  erase = new ButtonUI(gS,
                       relativeX(50.0f),
                       relativeY(905.0f),
                       relativeX(126.0f),
                       relativeY(126.0f),
                       game->getTexture(UIERASE),
                       game->getTexture(UIERASECLCK));
  gS->addObjects(erase);
  gS->addEventListener(erase);
  erase->connect([this]() {
    OnErase();
  });

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
>>>>>>> Stashed changes
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

//MarblesInsanityUI
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



//RankingUI
UIRanking::UIRanking(GameState* gS, Game* game) : gS(gS), game(game)
{
	exit = new ButtonUI(gS, (int)((50.0f / 1920.0f) * Game::WIN_WIDTH), (int)((49.0f / 1080.0f) * Game::WIN_HEIGHT), (int)((126.0f / 1920.0f) * Game::WIN_WIDTH), (int)((126.0f / 1080.0f) * Game::WIN_HEIGHT), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjectsUI(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });
}
void UIRanking::OnExit()
{
	game->pop();
}

void UIRanking::render() const
{

	exit->render();
}
void UIRanking::update() {

	exit->update();
}

//BACCARAT UI
<<<<<<< Updated upstream
UIBaccarat::UIBaccarat(GameState* gS, Game* game, Baccarat* baccarat) : UIChips(gS, game), baccarat(baccarat) {}

void UIBaccarat::OnExit()
{
	UI::OnExit();
	isBlackJack = false;
	isBet = false;
	isFlip = false;
}

void UIBaccarat::OnGo() {
	baccarat->startRound();
=======
UIBaccarat::UIBaccarat(GameState* gS, Game* game, Baccarat* baccarat)
  : UIChips(gS, game)
  , baccarat(baccarat)
{
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	//EJEMPLO USO TUTORIAL, METER LAS IMAGENES QUE OCUPE EN EL VECTOR
	if (isBlackJack) {
		OnInfoBlackJack();
	}
	else if (isBet) {
		OnInfoBet();
	}
	else if (isFlip) {
		OnInfoFlip();
	}
	else {
		std::vector<Texture*> baccaratTutorial = {
		game->getTexture(TUTORIAL1),
		game->getTexture(TUTORIAL2),
		game->getTexture(TUTORIAL3)

		};
		game->push(new Tutorial(game, gS, baccaratTutorial));
	}
}

void UIBaccarat::OnInfoBlackJack()
{
	std::vector<Texture*> BlackJackTutorial = {
	game->getTexture(TUTORIALJ1),
	game->getTexture(TUTORIALJ2),
	game->getTexture(TUTORIALJ3)

	};
	game->push(new Tutorial(game, gS, BlackJackTutorial));
}

void UIBaccarat::OnInfoBet()
{
	std::vector<Texture*> baccaratBetTutorial = {
		game->getTexture(TUTORIALB1),
		game->getTexture(TUTORIAL2),
		game->getTexture(TUTORIAL3)

	};
	game->push(new Tutorial(game, gS, baccaratBetTutorial));
}

void UIBaccarat::OnInfoFlip()
{
	std::vector<Texture*> baccaratFlipTutorial = {
		game->getTexture(TUTORIALF1),
		game->getTexture(TUTORIAL2),
		game->getTexture(TUTORIAL3)

	};
	game->push(new Tutorial(game, gS, baccaratFlipTutorial));
=======
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  //EJEMPLO USO TUTORIAL, METER LAS IMAGENES QUE OCUPE EN EL VECTOR
  std::vector<Texture*> baccaratTutorial = { game->getTexture(TUTORIAL1),
                                             game->getTexture(TUTORIAL2),
                                             game->getTexture(TUTORIAL3)

  };
  game->push(new Tutorial(game, gS, baccaratTutorial));
>>>>>>> Stashed changes
}

//Tutorial

<<<<<<< Updated upstream
UITutorial::UITutorial(GameState* gS, Game* game, size_t tam) : gS(gS), game(game), totalPages(tam) {
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjectsUI(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });
	arrowNext = new ButtonUI(gS, relativeX(897.0f), relativeY(963.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWD), game->getTexture(UIARROWDCLCK));
	arrowBack = new ButtonUI(gS, relativeX(897.0f), relativeY(880.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWU), game->getTexture(UIARROWUCLCK));
}

inline int
UITutorial::relativeX(const float& n)
=======
UITutorial::UITutorial(GameState* gS, Game* game, size_t tam)
  : gS(gS)
  , game(game)
  , totalPages(tam)
>>>>>>> Stashed changes
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

  //falta la flecha de volver atras
  //if (totalPages > 0) {
  //	/*Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
  //	if (tutorial->getPage() < totalPages)
  //	{*/
  //	arrowNext = new ButtonUI(gS, relativeX(897.0f), relativeY(963.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWD), game->getTexture(UIARROWDCLCK));
  //	gS->addObjects(arrowNext);
  //	gS->addEventListener(arrowNext);
  //	//}
  //	arrowNext->connect([this, gS, game]() {
  //		Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
  //		if (tutorial) {
  //			tutorial->nextPage();
  //			if (tutorial->getPage() > 0 && !arrow)
  //			{
  //				/*if (tutorial->getPage() == totalPages) {

  //				}*/
  //				arrow = true;
  //				arrowBack = new ButtonUI(gS, relativeX(897.0f), relativeY(880.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWU), game->getTexture(UIARROWUCLCK));
  //				gS->addObjects(arrowBack);
  //				gS->addEventListener(arrowBack);
  //				//ESTE SALE SEGUN EL CURRENT PAGE AHORA NO SE ME OCURRE COMO PASARLO
  //				arrowBack->connect([this, gS]() {
  //					Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
  //					if (tutorial) {
  //						tutorial->previousPage();
  //						/*if (tutorial->getPage() == 0) {

  //						}*/
  //					}
  //					});
  //			}
  //		}
  //		});
  //}
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
<<<<<<< Updated upstream
	arrowNext = new ButtonUI(gS, relativeX(897.0f), relativeY(963.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWD), game->getTexture(UIARROWDCLCK));
	gS->addObjectsUI(arrowNext);
	gS->addEventListener(arrowNext);
=======
  arrowNext = new ButtonUI(gS,
                           relativeX(897.0f),
                           relativeY(963.5f),
                           relativeX(97.0f),
                           relativeY(80.0f),
                           game->getTexture(UIARROWD),
                           game->getTexture(UIARROWDCLCK));
  gS->addObjects(arrowNext);
  gS->addEventListener(arrowNext);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	arrowBack = new ButtonUI(gS, relativeX(897.0f), relativeY(880.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWU), game->getTexture(UIARROWUCLCK));
	gS->addObjectsUI(arrowBack);
	gS->addEventListener(arrowBack);
=======
  arrowBack = new ButtonUI(gS,
                           relativeX(897.0f),
                           relativeY(880.5f),
                           relativeX(97.0f),
                           relativeY(80.0f),
                           game->getTexture(UIARROWU),
                           game->getTexture(UIARROWUCLCK));
  gS->addObjects(arrowBack);
  gS->addEventListener(arrowBack);
>>>>>>> Stashed changes

  arrowBack->connect([this]() {
    Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
    if (tutorial) {
      tutorial->previousPage();
    }
  });
  return arrowBack;
}
// UI PELEAS
void UIPeleas::OnGo()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBotonPeleas");
  _peleas->StartBattle();
}

inline int UIRoulette::relativeX(const float& n)
{
  return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int UIRoulette::relativeY(const float& n)
{
  return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

UIRoulette::UIRoulette(GameState* gS, Game* game, RouletteScene* rouletteS)
  : gS(gS)
  , game(game)
  , rouletteS(rouletteS)
{
<<<<<<< Updated upstream
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjectsUI(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });

	go = new ButtonUI(gS, relativeX(1697.0f), relativeY(858.0f), relativeX(173.0f), relativeY(173.0f), game->getTexture(UIGO), game->getTexture(UIGOCLCK));
	gS->addObjectsUI(go);
	gS->addEventListener(go);
	go->connect([this]() { OnGo(); });
=======
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
  go->connect([this]() {
    OnGo();
  });
>>>>>>> Stashed changes
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

inline int UIRouletteChoose::relativeX(const float& n)
{
  return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int UIRouletteChoose::relativeY(const float& n)
{
  return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

UIRouletteChoose::UIRouletteChoose(GameState* gS,
                                   Game* game,
                                   rouletteChoose* rouletteC)
  : gS(gS)
  , game(game)
  , rouletteC(rouletteC)
{
<<<<<<< Updated upstream
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjectsUI(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });
=======
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
>>>>>>> Stashed changes
}

void UIRouletteChoose::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}

inline int UIScythe::relativeX(const float& n)
{
  return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int UIScythe::relativeY(const float& n)
{
  return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

UIScythe::UIScythe(GameState* gS, Game* game, scythe* rouletteC)
  : gS(gS)
  , game(game)
  , s(s)
{
<<<<<<< Updated upstream
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjectsUI(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });
=======
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
>>>>>>> Stashed changes
}

void UIScythe::OnExit()
{
  auto& soundManager = SoundManager::obtenerInstancia();
  soundManager.reproducirEfecto("PresionaBoton");
  game->pop();
}


