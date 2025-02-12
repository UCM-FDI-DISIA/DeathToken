#pragma once
#include "Pickable.h"

class Mushroom : public Pickable{
private:
	static constexpr int SPEED_MAG = 4;
public:
	static constexpr int POINTS = 200;
	Mushroom(PlayState* game, Texture* text, Vector2D<> pos);
	Mushroom(const Mushroom&);
	void update() override;
	void render() const override;
	sceneObject* clone() const override;
	void triggerAction() override;
};