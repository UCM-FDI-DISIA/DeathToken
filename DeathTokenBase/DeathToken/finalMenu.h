#pragma once
#include "gameState.h"
#include "button.h"
#include "vector2D.h"

class FinalMenu : public GameState {
private:
	Texture* text;
	SDL_Rect rectT;
	Texture* image;
	SDL_Rect rectI;
	Vector2D<> posT;
	Vector2D<> posI;
	bool show;
	
	Vector2D<float> lerp(Vector2D<> origen, Vector2D<> destino);
public:
	FinalMenu(Game* g, bool victory);
	void update() override;
	void render() const override;
};