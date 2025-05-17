#pragma once
#include "sceneObject.h"
#include "eventHandler.h"
#include <functional>

using Callback = std::function<void()>;

class Game;
class Menu;
class Mesa : public SceneObject, public EventHandler {
private:
	bool hover;
	Texture* texture;
	Player* player;
	Callback cb;

public:
	Mesa(GameState*, Vector2D<>, Texture*, int, int);
	~Mesa() { texture = nullptr; };
	void render() const;
	void update() override;
	void handleEvent(const SDL_Event& evento) override;
	bool getHover() const { return hover; }
	void setHover(bool hov) { hover = hov; };
	Callback getCallback() { return cb; };
	SDL_Rect getRect() const;
	void connect(Callback);
};