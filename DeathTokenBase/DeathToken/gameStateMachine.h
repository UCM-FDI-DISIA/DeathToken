
#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <memory>
#include <stack>

#include "gameState.h"

/**
 * Máquina de estados del juego.
 *
 * Se comporta como una pila y proporciona métodos update, render y
 * handleEvent para aplicarlos sobre el estado actual.
 */
class GameStateMachine
{
protected:
	std::stack<std::shared_ptr<GameState>> gameStates;

public:


	virtual ~GameStateMachine();

	// Apila un nuevo estado, que se convierte en el estado actual,
	// manteniendo el anterior en la pila
	void pushState(std::shared_ptr<GameState> state);
	// Reemplaza el estado actual por el nuevo estado
	void replaceState(std::shared_ptr<GameState> state);
	// Desapila el estado actual y pasa al siguiente en la pila
	// (no hace nada si no la pila es vacía)
	void popState();

	// Sobrecargas que reciben un puntero normal
	void pushState(GameState* state);
	void replaceState(GameState* state);

	bool empty() const;
	operator bool() const;

	// Métodos que delegan en los métodos homónimos de GameState
	// sobre el estado actual (no hacen nada si la pila es vacía)
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

inline void
GameStateMachine::pushState(GameState* state)
{
	pushState(std::shared_ptr<GameState>(state));
}

inline void
GameStateMachine::replaceState(GameState* state)
{
	replaceState(std::shared_ptr<GameState>(state));
}

#endif // GAME_STATE_MACHINE_H
