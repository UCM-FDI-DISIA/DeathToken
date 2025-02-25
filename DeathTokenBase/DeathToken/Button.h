#pragma once
#include "gameState.h"
#include "EventHandler.h"
#include "Texture.h"
#include <functional>

using Callback = std::function<void()>;

class Button : public GameObject, public EventHandler{
private:
	Texture* text;
	SDL_Rect box;
	bool hover;
	Callback cb;
	int stop;
	int type;
	std::vector<Texture*> CMarbles;
	std::vector<int> NCMarbles;
public:
	Button(GameState*, int x, int y, int w, int h, Texture*,int type, std::vector<int>);
	Button(GameState*,int x,int y,int w,int h,Texture*);
	~Button();
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;
	void connect(Callback);
};
