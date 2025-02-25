#pragma once
#include <SDL.h>


struct Collision
{
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical

	operator bool() const { return result == OBSTACLE; }
};

constexpr Collision NO_COLLISION = Collision{};