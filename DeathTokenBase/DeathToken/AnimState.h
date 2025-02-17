#pragma once
#include <functional>
#include "gameState.h"


using Callback = std::function<bool()>;

class AnimState : public GameState {
private:

	Callback cb;
public:
	AnimState(Game*);
	void update() override;
	void render() const override;
	void connect(Callback);
};