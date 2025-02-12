#include <string>
#include "checkML.h"
#include "Game.h"
#include "playState.h"
#include "MainMenu.h"

// Formato de la especificaci�n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const std::string textureRoot = "../assets/images/";

// Especificación de las texturas del juego
const std::array<TextureSpec, NUM_TEXTURES> textureSpec{
	TextureSpec{"portada.png", 1, 1},
	TextureSpec{"nivel1.png", 1, 1},
	TextureSpec{"nivel2.png", 1, 1},
	TextureSpec{"salir.png", 1, 1},
	TextureSpec{"continuar.png", 1, 1},
	TextureSpec{"volverAlMenu.png", 1, 1},
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"supermario.png", 22, 1},
	TextureSpec{"goomba.png",3,1},
	TextureSpec{"koopa.png",4,1},
	TextureSpec{"blocks.png",6,1},
	TextureSpec{"mushroom.png",1,1},
	TextureSpec{"lift.png",1,1},
	TextureSpec{"coin.png",4,1},
	TextureSpec{"hasGanado.png",1,1},
	TextureSpec{"gameOver.png",1,1}
};

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Mario 1x01",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH * TILE_SIDE,
		WIN_HEIGHT * TILE_SIDE,
		SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL";

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);


	MainMenu* menu = new MainMenu(this);
	pushState(menu);
}
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;
	// Desactiva la SDL
	SDL_Quit();
}
void Game::run() {
	// Bucle principal del juego. Sigue mientras Mario este vivo o no haya llegado al final
	while (!empty()) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego

		SDL_RenderClear(renderer);
		render();       // Dibuja los objetos en la venta
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				stop();
			else
				handleEvent(event);
		}

		//state.handleEvent(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < Game::FRAME_RATE)
			SDL_Delay(Game::FRAME_RATE - elapsed);
	}
}
Texture* Game::getTexture(TextureName name) const {
	return textures[name];
}
SDL_Renderer* Game::getRenderer() const { return renderer; }

void Game::push(GameState* nextState) {
	pushState(nextState);
}
void Game::replace(GameState* nextState) {
	replaceState(nextState);
}
void Game::pop() {
	popState();
}
void Game::stop() { while (!empty()) popState(); }