#pragma once
#include "vector2D.h"
#include "sceneObject.h"
#include "award.h"

class Roulette : public SceneObject
{
	Game* game;
	GameState* gS;
	Texture* texture;
	double rot = 0;
	double speed = 0;
	float decelerate = 0.95f;
	bool started = false;
	PlayerEconomy* eco;
	float animTime = 0.0f;
	Texture* recompensas;
	SDL_Rect recompensasR{ int(Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 4.5 + Game::WIN_WIDTH / 16.5), Game::WIN_HEIGHT / 2 - Game::WIN_WIDTH / 16, Game::WIN_WIDTH / 5, Game::WIN_WIDTH / 8 };
	int i = 0;
public:
	Roulette(GameState* gS, Game* game, Point2D<> pos, Texture* text, PlayerEconomy* eco);
	virtual ~Roulette() {};
	void addSpeed(int s);

	void render() const override;
	void update() override;
};

