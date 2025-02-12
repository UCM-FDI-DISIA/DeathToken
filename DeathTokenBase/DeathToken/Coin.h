#pragma once
#include <SDL.h>
#include "checkML.h"
#include "Pickable.h"

class Coin : public Pickable {
public:
	static constexpr int POINTS = 200;

	Coin(PlayState* g, istream& is, Texture* text);
	Coin(const Coin&);
	void update() override;
	void render() const override;
	sceneObject* clone() const override;
	void triggerAction() override;
};
