#include "UI.h"
#include "Game.h"
#include "Marbles.h"
#include "Slots.h"
#include "Baccarat.h"
#include "RouletteScene.h"
#include "marblesInsanity.h"
#include "Tutorial.h"
#include "Peleas.h"
#include <iostream>

UI::UI(GameState* gS, Game* game) : gS(gS), game(game), onBet(false), chipOnUse(0), chipPage(0)
{
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjects(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });

	go = new ButtonUI(gS, relativeX(1697.0f), relativeY(858.0f), relativeX(173.0f), relativeY(173.0f), game->getTexture(UIGO), game->getTexture(UIGOCLCK));
	gS->addObjects(go);
	gS->addEventListener(go);
	go->connect([this]() { OnGo(); });

	arrowL = new ButtonUI(gS, relativeX(230.0f), relativeY(913.5f), relativeX(97.0f), relativeY(109.0f), game->getTexture(UIARROWL), game->getTexture(UIARROWLCLCK));
	gS->addObjects(arrowL);
	gS->addEventListener(arrowL);
	arrowL->connect([this]() { OnArrow(true); });

	arrowR = new ButtonUI(gS, relativeX(897.0f), relativeY(913.5f), relativeX(97.0f), relativeY(109.0f), game->getTexture(UIARROWR), game->getTexture(UIARROWRCLCK));
	gS->addObjects(arrowR);
	gS->addEventListener(arrowR);
	arrowR->connect([this]() { OnArrow(false); });

	chips = std::vector<ButtonChip*>(4);
	chips[0] = new ButtonChip(gS, this, relativeX(367.0f), relativeY(918.0f), relativeX(100.0f), relativeY(104.0f), 0,
		1, 25, 500, game->getTexture(UICHIP1), game->getTexture(UICHIP25), game->getTexture(UICHIP500));
	chips[0]->setOnUse(true);
	gS->addObjects(chips[0]);
	gS->addEventListener(chips[0]);
	chips[0]->connect([this]() {});

	chips[1] = new ButtonChip(gS, this, relativeX(497.0f), relativeY(918.0f), relativeX(100.0f), relativeY(104.0f), 1,
		2, 50, 1000, game->getTexture(UICHIP2), game->getTexture(UICHIP50), game->getTexture(UICHIP1000));
	gS->addObjectsUI(chips[1]);
	gS->addEventListener(chips[1]);
	chips[1]->connect([this]() {});

	chips[2] = new ButtonChip(gS, this, relativeX(627.0f), relativeY(918.0f), relativeX(100.0f), relativeY(104.0f), 2,
		5, 100, 2000, game->getTexture(UICHIP5), game->getTexture(UICHIP100), game->getTexture(UICHIP2000));
	gS->addObjectsUI(chips[2]);
	gS->addEventListener(chips[2]);
	chips[2]->connect([this]() {});

	chips[3] = new ButtonChip(gS, this, relativeX(757.0f), relativeY(918.0f), relativeX(100.0f), relativeY(104.0f), 3,
		10, 200, 5000, game->getTexture(UICHIP10), game->getTexture(UICHIP200), game->getTexture(UICHIP5000));
	gS->addObjectsUI(chips[3]);
	gS->addEventListener(chips[3]);
	chips[3]->connect([this]() {});
}
inline int
UI::relativeX(const float& n)
{
	return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}
inline int
UI::relativeY(const float& n)
{
	return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}
void
UI::OnExit()
{
	if (!onBet) game->pop();
}
void
UI::changeChip(const int& id)
{
	chips[chipOnUse]->setOnUse(false);
	chipOnUse = id;
	chips[chipOnUse]->setOnUse(true);
}
int
UI::currentChipValue()
{
	return chips[chipOnUse]->getValue();
}
void
UI::OnArrow(const bool& left)
{
	int aux = chipPage;
	if (left && chipPage > 0) chipPage--;
	else if (!left && chipPage < 2) chipPage++;

	if (chipPage != aux)
	{
		for (ButtonChip* i : chips)
		{
			i->changePage(chipPage);
		}
	}
}


UIChips::UIChips(GameState* gS, Game* game) : UI(gS, game)
{

	erase = new ButtonUI(gS, relativeX(50.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIERASE), game->getTexture(UIERASECLCK));
	gS->addObjects(erase);
	gS->addEventListener(erase);
	erase->connect([this]() { OnErase(); });

	info = new ButtonUI(gS, relativeX(1377.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjects(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });

	repeat = new ButtonUI(gS, relativeX(1537.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIREPEAT), game->getTexture(UIREPEATCLCK));
	gS->addObjects(repeat);
	gS->addEventListener(repeat);
	repeat->connect([this]() { OnRepeat(); });
}


UISlots::UISlots(GameState* gS, Game* game, Slots* slot) : UI(gS, game), slots(slot)
{
	for (ButtonChip* i : chips)
	{
		i->setSlot();
	}
	x2 = new ButtonUI(gS, relativeX(50.0f), relativeY(209.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIX2), game->getTexture(UIX2CLCK));
	gS->addObjects(x2);
	gS->addEventListener(x2);
	x2->connect([this]() { Onx2(); });

	x3 = new ButtonUI(gS, relativeX(50.0f), relativeY(369.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIX3), game->getTexture(UIX3CLCK));
	gS->addObjects(x3);
	gS->addEventListener(x3);
	x3->connect([this]() { Onx3(); });

	x5 = new ButtonUI(gS, relativeX(50.0f), relativeY(529.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIX5), game->getTexture(UIX5CLCK));
	gS->addObjects(x5);
	gS->addEventListener(x5);
	x5->connect([this]() { Onx5(); });

	info = new ButtonUI(gS, relativeX(50.0f), relativeY(905.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjects(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });
}
void
UISlots::OnGo() {
	slots->iniciarGiro();
}
void
UISlots::Onx2()
{

}
void
UISlots::Onx3()
{

}
void
UISlots::Onx5()
{

}
void
UISlots::OnInfo()
{
	//EJEMPLO USO TUTORIAL, METER LAS IMAGENES QUE OCUPE EN EL VECTOR
	/*std::vector<Texture*> slotsTutorial = {
	game->getTexture(imagen1),
	game->getTexture(imagen2),
	game->getTexture(imagen3)
	};
	game->push(new Tutorial(game, gS, slotsTutorial));*/
}

UIMarbles::UIMarbles(GameState* gS, Game* game, Marbles* marbles) : UIChips(gS, game), marbles(marbles) {}
void UIMarbles::OnGo() {
	marbles->startRound();
}

void UIMarbles::OnErase() {
	marbles->clearBets();
}

void UIMarbles::OnRepeat()
{
	marbles->repeat();
}

//MarblesInsanityUI
UIMarblesInsanity::UIMarblesInsanity(GameState* gS, Game* game, MarblesInsanity* marblesI) : UIChips(gS, game), marblesI(marblesI) {}
void UIMarblesInsanity::OnGo() {
	marblesI->StartRoundTrickster();
}

void UIMarblesInsanity::render() const
{
	go->render();
}
void UIMarblesInsanity::update() {
	go->update();
}

//BACCARAT UI
UIBaccarat::UIBaccarat(GameState* gS, Game* game, Baccarat* baccarat) : UIChips(gS, game), baccarat(baccarat) {}

void UIBaccarat::OnGo() {
	baccarat->startRound();
}

void UIBaccarat::OnErase() {
	baccarat->clearBets();
}

void UIBaccarat::OnRepeat()
{
	baccarat->repeat();
}

UIRoulette::UIRoulette(GameState* gS, Game* game, RouletteScene* rouletteS) : UIChips(gS, game), rouletteS(rouletteS) {}

void UIRoulette::OnGo() {
	rouletteS->throwRoulette();
}

void UIRoulette::render() const
{
	go->render();
	exit->render();
}

void UIRoulette::update()
{
	go->update();
	exit->update();
}

void
UIBaccarat::OnInfo()
{
	//EJEMPLO USO TUTORIAL, METER LAS IMAGENES QUE OCUPE EN EL VECTOR
	std::vector<Texture*> baccaratTutorial = {
	game->getTexture(TUTORIAL1),
	game->getTexture(TUTORIAL2),
	game->getTexture(TUTORIAL3)

	};
	game->push(new Tutorial(game, gS, baccaratTutorial));
}

//Tutorial

UITutorial::UITutorial(GameState* gS, Game* game, size_t tam) : gS(gS), game(game), totalPages(tam) {
	exit = new ButtonUI(gS, relativeX(50.0f), relativeY(49.0f), relativeX(126.0f), relativeY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjects(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });

	//falta la flecha de volver atras
	if (totalPages > 0) {
		/*Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
		if (tutorial->getPage() < totalPages)
		{*/
		arrowNext = new ButtonUI(gS, relativeX(897.0f), relativeY(963.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWD), game->getTexture(UIARROWDCLCK));
		gS->addObjects(arrowNext);
		gS->addEventListener(arrowNext);
		//}
		arrowNext->connect([this, gS, game]() {
			Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
			if (tutorial) {
				tutorial->nextPage();
				if (tutorial->getPage() > 0 && !arrow)
				{
					/*if (tutorial->getPage() == totalPages) {

					}*/
					arrow = true;
					arrowBack = new ButtonUI(gS, relativeX(897.0f), relativeY(880.5f), relativeX(97.0f), relativeY(80.0f), game->getTexture(UIARROWU), game->getTexture(UIARROWUCLCK));
					gS->addObjects(arrowBack);
					gS->addEventListener(arrowBack);
					//ESTE SALE SEGUN EL CURRENT PAGE AHORA NO SE ME OCURRE COMO PASARLO
					arrowBack->connect([this, gS]() {
						Tutorial* tutorial = dynamic_cast<Tutorial*>(gS);
						if (tutorial) {
							tutorial->previousPage();
							/*if (tutorial->getPage() == 0) {

							}*/
						}
						});
				}
			}
			});
	}
}

inline int
UITutorial::relativeX(const float& n)
{
	return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}
inline int
UITutorial::relativeY(const float& n)
{
	return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}

void UITutorial::OnExit() {
	game->pop();
}

// UI PELEAS
void UIPeleas::OnGo() {
	_peleas->StartBattle();
}