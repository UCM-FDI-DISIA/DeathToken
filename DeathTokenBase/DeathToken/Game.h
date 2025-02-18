#pragma once
#include <SDL.h>
#include <array>
#include "Texture.h"
#include "gameStateMachine.h";

using uint = unsigned int;
enum TextureName {
		CELDA,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};
class Game : private GameStateMachine {
public:
	

	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;
	static constexpr uint FRAME_RATE = 50;
private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;

public:
	Game();
	~Game();
	void run();
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() const;
	void push(GameState*);
	void replace(GameState*);
	void pop();
	void stop();
};
