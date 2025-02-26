#include "AnimState.h"
#include "Game.h"

AnimState::AnimState(Game* g) : GameState(g) {

}
void AnimState::update() {
	bool inProgress = cb();
	if (!inProgress) {
		game->pop();

	}
}
void AnimState::render() const {
	
}
void AnimState::connect(Callback callback) {
	cb = callback;
}