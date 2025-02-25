#include "UI.h"
#include "Game.h"

UI::UI(GameState* gS, Game* game) : gS(gS), game(game), onBet(false)
{
	exit = new ButtonUI(gS, relativePosX(50.0f), relativePosY(49.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIEXIT), game->getTexture(UIEXITCLCK));
	gS->addObjects(exit);
	gS->addEventListener(exit);
	exit->connect([this]() { OnExit(); });

	go = new ButtonUI(gS, relativePosX(1697.0f), relativePosY(858.0f), relativePosX(173.0f), relativePosY(173.0f), game->getTexture(UIGO), game->getTexture(UIGOCLCK));
	gS->addObjects(go);
	gS->addEventListener(go);
	go->connect([this]() { OnGo(); });
}
inline int
UI::relativePosX(const float& n)
{
	return (n / 1920.0f) * Game::WIN_WIDTH;
}
inline int
UI::relativePosY(const float& n)
{
	return (n / 1080.0f) * Game::WIN_HEIGHT;
}
void
UI::OnExit()
{
	if (!onBet) game->pop();
}

UIChips::UIChips(GameState* gS, Game* game) : UI(gS, game)
{
	erase = new ButtonUI(gS, relativePosX(50.0f), relativePosY(905.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIERASE), game->getTexture(UIERASECLCK));
	gS->addObjects(erase);
	gS->addEventListener(erase);
	erase->connect([this]() { OnErase(); });

	arrowL = new ButtonUI(gS, relativePosX(210.0f), relativePosY(905.0f), relativePosX(97.0f), relativePosY(109.0f), game->getTexture(UIARROWL), game->getTexture(UIARROWLCLCK));
	gS->addObjects(arrowL);
	gS->addEventListener(arrowL);
	arrowL->connect([this]() {});

	arrowR = new ButtonUI(gS, relativePosX(819.0f), relativePosY(905.0f), relativePosX(97.0f), relativePosY(109.0f), game->getTexture(UIARROWR), game->getTexture(UIARROWRCLCK));
	gS->addObjects(arrowR);
	gS->addEventListener(arrowR);
	arrowR->connect([this]() {});

	info = new ButtonUI(gS, relativePosX(1377.0f), relativePosY(905.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjects(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });

	repeat = new ButtonUI(gS, relativePosX(1537.0f), relativePosY(905.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIREPEAT), game->getTexture(UIREPEATCLCK));
	gS->addObjects(repeat);
	gS->addEventListener(repeat);
	repeat->connect([this]() { OnRepeat(); });
}

UISlots::UISlots(GameState* gS, Game* game) : UI(gS, game)
{
	x2 = new ButtonUI(gS, relativePosX(50.0f), relativePosY(209.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIX2), game->getTexture(UIX2CLCK));
	gS->addObjects(x2);
	gS->addEventListener(x2);
	x2->connect([this]() { Onx2(); });

	x3 = new ButtonUI(gS, relativePosX(50.0f), relativePosY(369.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIX3), game->getTexture(UIX3CLCK));
	gS->addObjects(x3);
	gS->addEventListener(x3);
	x3->connect([this]() { Onx3(); });

	x5 = new ButtonUI(gS, relativePosX(50.0f), relativePosY(529.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIX5), game->getTexture(UIX5CLCK));
	gS->addObjects(x5);
	gS->addEventListener(x5);
	x5->connect([this]() { Onx5(); });

	info = new ButtonUI(gS, relativePosX(1537.0f), relativePosY(905.0f), relativePosX(126.0f), relativePosY(126.0f), game->getTexture(UIINFO), game->getTexture(UIINFOCLCK));
	gS->addObjects(info);
	gS->addEventListener(info);
	info->connect([this]() { OnInfo(); });
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

}
