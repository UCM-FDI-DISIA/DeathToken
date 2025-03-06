#pragma once
#include "GameState.h"
#include "Button.h"
#include "Roulette.h"
#include "EventHandler.h"

class RouletteScene : public GameState, public EventHandler
{
	Roulette* roul;
	Texture* rouletteBG;
	Button* rouletteThrow;
	int costPerThrow = 10000;
	int canThrow = false;
public:
	RouletteScene(Game* g);
	virtual ~RouletteScene() {};
	void handleEvent(const SDL_Event& event) override;
	void throwRoulette();
	void update() override;
	void render() const override;
};

