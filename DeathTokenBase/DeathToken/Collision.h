#pragma once
#include <SDL.h>


struct Collision
{
	enum Target {
		LIMITES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		JUEGO = 3,	// afecta a juego
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical

	operator bool() const { return result == OBSTACLE; }
};

constexpr Collision NO_COLLISION = Collision{};