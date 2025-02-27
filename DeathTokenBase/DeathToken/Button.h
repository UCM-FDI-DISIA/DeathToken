#pragma once
#include "gameState.h"
#include "EventHandler.h"
#include "Texture.h"
#include <functional>

using Callback = std::function<void()>;

class UI;

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

class ButtonChip : public Button
{
protected:
	Texture* textures[3];
	SDL_Rect boxB;
	SDL_Rect boxC;
	bool onUse;
	bool clicked;
	UI* ui;
	int id;
	int value;
	int values[3];
	bool slot;
public:
	ButtonChip(GameState*, UI* ui, int x, int y, int w, int h, int id,
			   int v0, int v1, int v2, Texture*, Texture*, Texture*);
	void setOnUse(const bool& val);
	void changePage(const int& n);
	void update() override;
	void render() const override;
	void setSlot();
	int getValue();
};

class ButtonMarbles : public Button
{
protected:
	int stop;
	int type;
	std::vector<Texture*> CMarbles;
	std::vector<int> NCMarbles;
public:
	ButtonMarbles(GameState*, int x, int y, int w, int h, Texture*, int type, std::vector<int>);
	void render() const override;
};