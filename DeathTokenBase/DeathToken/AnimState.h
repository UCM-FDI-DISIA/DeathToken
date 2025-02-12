#pragma once
#include <functional>
#include "playState.h"

using Callback = std::function<bool()>;

class AnimState : public GameState{
private:
	PlayState* stateAnim;
	Callback cb;
public:
	AnimState(Game*, PlayState*);
	void update() override;
	void render() const override;
	void connect(Callback);
};