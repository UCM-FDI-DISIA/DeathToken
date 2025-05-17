#pragma once

#include "sceneObject.h"
#include "eventHandler.h"
class Menu;
class Player : public SceneObject, public EventHandler {
private:
	static constexpr int SPEED_MAG = 30;
	Menu* menu;
	Texture* texture;
	bool locura;

public:
	Player(GameState* g, Point2D<> pos, Texture* texture, Menu*);
	~Player() { texture = nullptr; }
	void render() const override;
	void update() override {}
	void handleEvent(const SDL_Event& evento) override;
	SDL_Rect getRect() const;//rect player
	bool getLocura() const { return locura; }
	void collision(vector<SDL_Rect>);
};