#pragma once
#include "sceneObject.h"
#include "EventHandler.h"
#include <functional>

using Callback = std::function<void()>;

class Game;

class Mesa : public sceneObject, public EventHandler {
private:
	bool hover;
	Texture* texture;
	Game* _game;
	int indexGame;
	Callback cb;

public:
	Mesa(GameState*, Vector2D<>, Texture*, int, int, int, Game*);
	~Mesa() { texture = nullptr; };
	void render() const;
	void update() override;
	void handleEvent(const SDL_Event& evento) override;
	bool getHover() const { return hover; }
	void inGame(bool in) { hover = in; }
	SDL_Rect getRect() const;
	void connect(Callback);
};