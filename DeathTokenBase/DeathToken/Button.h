#pragma once
#include "game.h"
#include "gameState.h"
#include "eventHandler.h"
#include "texture.h"
#include "playerEconomy.h"
#include <functional>
#include <string>

using Callback = std::function<void()>;

class UI;

class Button : public GameObject, public EventHandler {
protected:
	Texture* text;
	Texture* textC;
	SDL_Rect box;
	Callback cb;
	bool hover;
	bool clicked;
	bool perma = false;
	int frame;
	bool visible;
public:
	Button(GameState*, int x, int y, int w, int h, Texture*,Texture* = nullptr, int frame = 0);
	virtual ~Button() { text = nullptr; textC = nullptr; };
	void render() const override;
	virtual void update() override;
	void updatePerma();
	void handleEvent(const SDL_Event&) override;
	void connect(Callback);
	bool playerHovered(const SDL_Rect& playerRect);
	bool getPermaState() { return perma; };
	//getters para mantener private los atributos pero poder acceder desde menu
	Callback getCallback() { return cb; };
	bool& getHover() { return hover; };
	inline void setHover(bool b) { hover = b; };
	void Hide() { visible = false; }
	void Show() { visible = true; }
};

class ButtonUI : public Button
{
protected:
	SDL_Rect boxB;
public:
	ButtonUI(GameState*, int x, int y, int w, int h, Texture*, Texture*);
	~ButtonUI() override = default;
	void movePos(int x, int y);
	void render() const;
};

class ButtonBet : public ButtonUI
{
protected:
	Game* game;
	GameState* gS;
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
	~ButtonBet() override {};
	TextureName showChip();
	void clear();
	void repeat();
	int getBet();
	void setBetHistory(int n);
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
public:
	ButtonChip(GameState*, UI* ui, int x, int y, int w, int h, int id,
		int v0, int v1, int v2, Texture*, Texture*, Texture*);
	~ButtonChip() override {};
	void setOnUse(const bool& val);
	void changePage(const int& n);
	void update() override;
	void render() const override;
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
	~ButtonMarbles() override {}
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
};

//MARBLESINSANITY
class ButtonMarblesInsanity : public ButtonUI {
protected:
public:
	ButtonMarblesInsanity(GameState* g, int x, int y, int w, int h, Texture* t, Texture* tC, bool acertado, std::vector<int> discardMarble);
	~ButtonMarblesInsanity() {}
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
};

//BACCARAT
class ButtonBaccarat : public ButtonBet
{
protected:
	int type;
	std::vector<int> NCBaccarat;
public:
	ButtonBaccarat(GameState*, Game* game, UI* ui, int x, int y, int w, int h);
	~ButtonBaccarat() override {};
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void repeatDoubleBet() { currentBet = betHistory * 2; };
	void setPos(int x, int y);
};
//SLOTS
class ButtonSlots : public ButtonBet
{
public:
	ButtonSlots(GameState*, Game* game, UI* ui, int x, int y, int w, int h, Texture* text);
	~ButtonSlots() override {};
	virtual void render() const override;
	virtual void handleEvent(const SDL_Event& event) override;
};
//Peleas
class ButtonPeleas : public ButtonSlots
{
public:
	ButtonPeleas(GameState* st, Game* game, UI* ui, int x, int y, int w, int h, Texture* text) :ButtonSlots(st, game, ui, x, y, w, h, text){}
	void handleEvent(const SDL_Event& event) override;
	void render() const override;
};

//EscenaTutorial
class EscenaTutorial;
class ButtonTutorial:public ButtonBet {
private:
	EscenaTutorial* _tut;
public:
	ButtonTutorial(GameState*, Game* game, UI* ui, int x, int y, int w, int h, Texture* text,EscenaTutorial* tut);
	~ButtonTutorial() override;
	void render() const override;
	virtual void handleEvent(const SDL_Event& event) override;
};