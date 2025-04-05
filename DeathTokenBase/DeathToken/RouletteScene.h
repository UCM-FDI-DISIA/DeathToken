#pragma once
#include "GameState.h"
#include "Roulette.h"
#include "EventHandler.h"
#include "UI.h"

class RouletteScene : public GameState, public EventHandler
{
	Roulette* roul;
	Texture* rouletteBG;
	Texture* arrowTex;
	int costPerThrow = 500;
	int canThrow = false;
	PlayerEconomy* eco;
	HUDBet* hud;
	UIRoulette* ui;
	sceneObject* arrow;
public:
	RouletteScene(Game* g, PlayerEconomy* eco);
	virtual ~RouletteScene() {};
	void handleEvent(const SDL_Event& event) override;
	void throwRoulette();
	void update() override;
	void render() const override;
};

