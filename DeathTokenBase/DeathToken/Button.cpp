#include "Button.h"
#include "UI.h"

Button::Button(GameState* g, int x, int y, int w, int h, Texture* t)
	: GameObject(g), text(t), hover(false)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}
void
Button::update()
{
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);

	// Comprueba si el rat�n est� sobre el rect�ngulo
	hover = SDL_PointInRect(&point, &box);
}
void Button::render() const {
	if (!hover) {
		text->render(box);
	}
	else {
		SDL_Rect point(box.x, box.y, box.h, box.h);
		text->render(box, SDL_Color(255, 255, 0));
	}

}
void Button::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point point{ event.button.x, event.button.y };
		if (SDL_PointInRect(&point, &box))
			cb();
	}
}
void Button::connect(Callback callback) {
	cb = callback;
}

ButtonUI::ButtonUI(GameState* g, int x, int y, int w, int h, Texture* t, Texture* tC)
	: Button(g, x, y, w, h, t), textC(tC), clicked(false) {
	boxB.x = (int)(x - (w * 0.05f));
	boxB.y = (int)(y - (h * 0.05f));
	boxB.w = (int)(w * 1.1f);
	boxB.h = (int)(h * 1.1f);
}
void
ButtonUI::update()
{
	Button::update();
	int mouseState = SDL_GetMouseState(NULL, NULL);
	clicked = (hover && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)));
}
void
ButtonUI::render() const
{
	if (clicked)
	{
		textC->render(box);
	}
	else if (!hover)
		text->render(box);
	else {
		SDL_Rect point(box.x - Game::TILE_SIDE, box.y, box.h, box.h);
		text->render(boxB);
	}
}

ButtonBet::ButtonBet(GameState* gS, Game* game, UI* ui, int x, int y, int w, int h, Texture* t, Texture* tC)
	: ButtonUI(gS, x, y, w, h, t, tC), game(game), currentBet(0), betHistory(0), ui(ui)
{
	connect([this]() {});

	chipSpace.x = (int)(x + (w / 2 - 50));
	chipSpace.y = (int)(y + (h / 2 - 50));
	chipSpace.w = (int)(100);
	chipSpace.h = (int)(100);

	currentText = game->getTexture(UICHIP1);
}
TextureName
ButtonBet::showChip()
{
	currentBetSprite = "UICHIP" + std::to_string(currentBet);
	auto aux = stringToTexture.find(currentBetSprite);
	if (aux != stringToTexture.end())
	{
		return aux->second;
	}
	else
	{
		return stringToTexture.find(lastChipSprite)->second;
	}
}
void
ButtonBet::clear()
{
	betHistory = currentBet;
	currentBet = 0;
}
void
ButtonBet::repeat()
{
	currentBet = betHistory;
}
int
ButtonBet::getBet()
{
	return currentBet;
}
void
ButtonBet::update()
{
	Button::update();
	int mouseState = SDL_GetMouseState(NULL, NULL);
	clicked = (hover && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)));
}
void
ButtonBet::render() const
{
	ButtonUI::render();
	if (currentBet > 0)
	{
		currentText->render(chipSpace);
	}
}
void
ButtonBet::handleEvent(const SDL_Event& event)
{
	Button::handleEvent(event);
	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && hover)
	{
		int chip = ui->currentChipValue();
		currentBet += chip;
		lastChipSprite = "UICHIP" + std::to_string(chip);
		currentText = game->getTexture(showChip());
	}
}

ButtonChip::ButtonChip(GameState* g, UI* ui, int x, int y, int w, int h, int id,
	int v0, int v1, int v2, Texture* t0, Texture* t1, Texture* t2)
	: Button(g, x, y, w, h, t0), ui(ui), onUse(false), clicked(false), id(id), slot(false)
{
	value = v0;
	values[0] = v0;
	values[1] = v1;
	values[2] = v2;
	textures[0] = t0;
	textures[1] = t1;
	textures[2] = t2;
	boxB.x = x;
	boxB.y = y - 20;
	boxB.w = w;
	boxB.h = h;
	boxC = boxB;
}
void
ButtonChip::update()
{
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);
	int mouseState = SDL_GetMouseState(NULL, NULL);
	if (clicked)
	{
		hover = SDL_PointInRect(&point, &boxC);
	}
	else
	{
		hover = SDL_PointInRect(&point, &box);
	}
	if (hover && !onUse)
		ui->changeChip(id);
	else if (!clicked && hover && !slot && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
		clicked = true;
	else if (clicked && (!mouseState))
		clicked = false;
	if (clicked)
	{
		boxC.x = point.x - (boxC.w / 2);
		boxC.y = point.y - (boxC.h / 2);
	}
}
void
ButtonChip::render() const
{
	if (clicked)
		text->render(boxC);
	else if (onUse)
		text->render(boxB);
	else
		text->render(box);
}
void
ButtonChip::setOnUse(const bool& val)
{
	onUse = val;
	if (!val) clicked = false;
}
void
ButtonChip::changePage(const int& n)
{
	value = values[n];
	text = textures[n];
}
void
ButtonChip::setSlot()
{
	slot = true;
}
int
ButtonChip::getValue()
{
	return value;
}