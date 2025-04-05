#pragma once
#include "sceneObject.h"
#include "EventHandler.h"
#include "Behaviour.h"

class Game;

class Mesa : public sceneObject, public EventHandler {
private:
	bool hover;
	Texture* texture;
	Game* _game;
	Behaviour comportamiento;
	int indexGame;

public:
	Mesa(GameState*, Vector2D<>, Texture*, int, int, int,Game*);
	~Mesa() { texture = nullptr;};
	void render() const;
	void update() override;
	void handleEvent(const SDL_Event& evento) override;
	Collision hit(const SDL_Rect&, Collision::Target) override;
	Behaviour getComportamiento() const { return comportamiento; }
	bool getHover() const { return hover; }
	void inGame(bool in) { hover = in; }
	SDL_Rect getRect() const;
};
