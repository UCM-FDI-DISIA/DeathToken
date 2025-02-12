#include "AnimState.h"
#include "Game.h"

AnimState::AnimState(Game* g, PlayState* s) : GameState(g), stateAnim(s) {

}
void AnimState::update() {
	bool inProgress = cb();
	if (!inProgress) {
		game->pop();
		stateAnim->restartLevel();
	}
}
void AnimState::render() const {
	stateAnim->render();
}
void AnimState::connect(Callback callback) {
	cb = callback;
}