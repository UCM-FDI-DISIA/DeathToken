#include <string>
#include "checkML.h"
#include "Game.h"
#include "Menu.h"

int Game::WIN_WIDTH = 1920;
int Game::WIN_HEIGHT = 1080;

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
	TextureSpec{"map/Casino_bg.png", 1, 1},
	TextureSpec{"baccarat/Baccarat_bg2.png", 1, 1},
	TextureSpec{"baccarat/barajaBaccarat.png", 14, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"ui/Exit.png", 1, 1},
	TextureSpec{"ui/Exit_Clicked.png", 1, 1},
	TextureSpec{"ui/Erase.png", 1, 1},
	TextureSpec{"ui/Erase_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowL.png", 1, 1},
	TextureSpec{"ui/ArrowL_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowR.png", 1, 1},
	TextureSpec{"ui/ArrowR_Clicked.png", 1, 1},
	TextureSpec{"ui/Info.png", 1, 1},
	TextureSpec{"ui/Info_Clicked.png", 1, 1},
	TextureSpec{"ui/Repeat.png", 1, 1},
	TextureSpec{"ui/Repeat_Clicked.png", 1, 1},
	TextureSpec{"ui/Go.png", 1, 1},
	TextureSpec{"ui/Go_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x2.png", 1, 1},
	TextureSpec{"ui/slots/x2_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x3.png", 1, 1},
	TextureSpec{"ui/slots/x3_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x5.png", 1, 1},
	TextureSpec{"ui/slots/x5_Clicked.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_1.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_2.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_5.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_10.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_25.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_50.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_100.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_200.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_500.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_1K.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_2K.png", 1, 1},
	TextureSpec{"ui/chips/chipRef_5K.png", 1, 1},
	TextureSpec{"player.png", 1, 1},
	TextureSpec{"marbles/Marbles_bg.png",1,1},
	TextureSpec{"ui/marbles/1_1_NoFill_MRB.png",1,1},
	TextureSpec{"ui/marbles/1_1_NoFill_Clicked_MRB.png",1,1},
	TextureSpec{"ui/marbles/2_1_NoFill_MRB.png",1,1},
	TextureSpec{"ui/marbles/2_1_NoFill_Clicked_MRB.png",1,1},
	TextureSpec{"ui/marbles/3_1_NoFill_MRB.png",1,1},
	TextureSpec{"ui/marbles/3_1_NoFill_Clicked_MRB.png",1,1},
	TextureSpec{"ui/marbles/4_3_NoFill_MRB.png",1,1},
	TextureSpec{"ui/marbles/4_3_NoFill_Clicked_MRB.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/RedMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/GreenMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/CyanMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/YellowMarbleIcon.png",1,1},


	
};

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Death Token 1x01",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH * TILE_SIDE,
		WIN_HEIGHT * TILE_SIDE,
		SDL_WINDOW_SHOWN);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL";
	inicializa(window);
	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);


	Menu* menu = new Menu(this);
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