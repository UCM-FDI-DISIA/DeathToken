#pragma once
#include <SDL.h>


struct Collision
{
	enum Target {
		LIMITES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		JUEGO = 3,	// afecta a juego
	};

	// Tipo de resultado de la colisi�n
	enum Result {
		NONE,		// no ha habido colisi�n
		OBSTACLE,	// la colisi�n impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisi�n horizontal
	int vertical = 0;     // profundidad de la colisi�n vertical

	operator bool() const { return result == OBSTACLE; }
};

constexpr Collision NO_COLLISION = Collision{};