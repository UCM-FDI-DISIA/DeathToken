#include "GameState.h"
#include "inputBox.h"
#include <SDL.h>
#include <string>

class PeleasInsanity : public GameState {
public:
  PeleasInsanity(Game* game);
  void render() const override;
  void update() override;

private:
  enum class State { INICIO, INPUT, COMPARACION, FINAL };
  State currentState;
  InputBox* input1;
  int correctPrice;
  int playerGuess;
  Uint32 stateStartTime;
  int lastUpdate;
};