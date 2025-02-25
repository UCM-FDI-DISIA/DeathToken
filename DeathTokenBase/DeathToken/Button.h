#pragma once
#include "gameState.h"
#include "EventHandler.h"
#include "Texture.h"
#include <functional>

using Callback = std::function<void()>;

class Button : public GameObject, public EventHandler{
protected:
	Texture* text;
	SDL_Rect box;
	bool hover;
	Callback cb;
public:
	Button(GameState*,int x,int y,int w,int h,Texture*);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;
	void connect(Callback);
};

class ButtonUI : public Button
{
protected:
	SDL_Rect boxB;
	bool clicked;
	Texture* textC;
public:
	ButtonUI(GameState*, int x, int y, int w, int h, Texture*, Texture*);
	void update() override;
	void render() const override;
};

class ButtonBet : public ButtonUI
{
public:
	ButtonBet(GameState*, int x, int y, int w, int h, Texture*, Texture*);
};

class ButtonChip : public ButtonUI
{
public:
	ButtonChip(GameState*, int x, int y, int w, int h, Texture*, Texture*);
};