#pragma once
#include <SDL.h>
#include <array>
#include "Texture.h"
#include "gameStateMachine.h";

class Player;

using uint = unsigned int;

enum TextureName {
	BACKGROUND,
	BACCARATBUT,
	SLOTSBUT,
	CANICASBUT,
	PELEASBUT,
	UIEXIT,
	UIEXITHV,
	UIEXITCLCK,
	UIERASE,
	UIERASEHV,
	UIERASECLCK,
	UIARROWL,
	UIARROWLHV,
	UIARROWLCLCK,
	UIARROWR,
	UIARROWRHV,
	UIARROWRCLCK,
	UIINFO,
	UIINFOHV,
	UIINFOCLCK,
	UIREPEAT,
	UIREPEATHV,
	UIREPEATCLCK,
	UIGO,
	UIGOHV,
	UIGOCLCK,
	UIX2,
	UIX2HV,
	UIX2CLCK,
	UIX3,
	UIX3HV,
	UIX3CLCK,
	UIX5,
	UIX5HV,
	UIX5CLCK,
	UICHIP1,
	UICHIP2,
	UICHIP5,
	UICHIP10,
	UICHIP25,
	UICHIP50,
	UICHIP100,
	UICHIP200,
	UICHIP500,
	UICHIP1000,
	UICHIP2000,
	UICHIP5000,
	MARIO,
	NUM_TEXTURES,  // Truco C++: número de texturas definidas
};
class Game : private GameStateMachine {
public:
	static int WIN_WIDTH;
	static int WIN_HEIGHT;
	static void inicializa(SDL_Window* window) { SDL_GetWindowSize(window, &WIN_WIDTH, &WIN_HEIGHT); }
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint TILE_SIDE = 1;
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
