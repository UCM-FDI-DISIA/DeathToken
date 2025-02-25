#pragma once

#include "sceneObject.h"
#include "EventHandler.h"

class Player : public sceneObject, public EventHandler {
private:
	static constexpr int SPEED_MAG = 8;

	Texture* texture;

public:
	Player(GameState* g, Point2D<> pos, Texture* texture);
	~Player() { texture = nullptr; }
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
	void handleEvent(const SDL_Event& evento) override;
};
