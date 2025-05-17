#pragma once

class GameState;

class GameObject {
protected:
	GameState* state;
public:
	GameObject(GameState* g) : state(g){}
	virtual ~GameObject() = default;
	virtual void render() const = 0;
	virtual void update() = 0;
};