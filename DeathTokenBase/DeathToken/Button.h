#pragma once
#include "Game.h"
#include "gameState.h"
#include "EventHandler.h"
#include "Texture.h"
#include <functional>
#include <string>

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
protected:
	Game* game;
	int currentBet;
	int betHistory;
	SDL_Rect chipSpace;
	Texture* currentText;
	std::string currentBetSprite;
	std::string lastChipSprite;
	UI* ui;
	const std::unordered_map<std::string, TextureName> stringToTexture = {
	{"UICHIP1", UICHIP1}, {"UICHIP2", UICHIP2}, {"UICHIP5", UICHIP5},
	{"UICHIP10", UICHIP10}, {"UICHIP25", UICHIP25}, {"UICHIP50", UICHIP50},
	{"UICHIP100", UICHIP100}, {"UICHIP200", UICHIP200}, {"UICHIP500", UICHIP500},
	{"UICHIP1000", UICHIP1000}, {"UICHIP2000", UICHIP2000}, {"UICHIP5000", UICHIP5000}
	};
public:
	ButtonBet(GameState*, Game* game, UI* ui, int x, int y, int w, int h, Texture*, Texture*);
	TextureName showChip();
	void clear();
	void repeat();
	int getBet();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event&) override;
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

class ButtonMarbles : public ButtonBet
{
protected:
	int stop;
	int type;
	std::vector<Texture*> CMarbles;
	std::vector<int> NCMarbles;
public:
	ButtonMarbles(GameState*, Game* game, UI* ui, int x, int y, int w, int h, Texture*, Texture*, int type, std::vector<int>);
	void render() const override;
	void handleEvent( const SDL_Event& event) override;
};