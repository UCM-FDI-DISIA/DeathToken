#pragma once

#include "sceneObject.h"
#include "EventHandler.h"
class Menu;
class Player : public sceneObject, public EventHandler {
private:
	static constexpr int SPEED_MAG = 8;
	Menu* menu;
	Texture* texture;
	bool colisionando;
	bool isColliding;

public:
	Player(GameState* g, Point2D<> pos, Texture* texture,Menu*);
	~Player() { texture = nullptr; }
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
	void handleEvent(const SDL_Event& evento) override;
	SDL_Rect getRect() const;//rect player
	Collision tryToMove(const Vector2D<>&, Collision::Target);
};