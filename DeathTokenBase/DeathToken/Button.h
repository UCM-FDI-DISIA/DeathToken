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
	Callback cb;
	bool hover;
public:
	Button(GameState*,int x,int y,int w,int h,Texture*);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;
	void connect(Callback);
	bool playerHovered(const SDL_Rect& playerRect);
	//getters para mantener private los atributos pero poder acceder desde menu
	Callback getCallback() { return cb; };
	bool& getHover() { return hover; };
};
