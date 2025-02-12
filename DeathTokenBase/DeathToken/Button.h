#pragma once
#include "gameState.h"
#include "EventHandler.h"
#include "Texture.h"
#include <functional>

using Callback = std::function<void()>;

class Button : public GameObject, public EventHandler{
private:
	Texture* text;
	Texture* pointer;
	SDL_Rect box;
	bool hover;
	Callback cb;
public:
	Button(GameState*,int x,int y,int w,int h,Texture*, Texture* pointer);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;
	void connect(Callback);
};
