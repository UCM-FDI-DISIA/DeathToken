#pragma once
#include "gameStateMachine.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include "Texture.h"
#include <random>

class Player;


using uint = unsigned int;

enum TextureName {
	CELDA,
	ICONOS,
	BACKGROUND,
	BACMAT,
	CARDS,
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
	GHOST,
	MARBLESBACK,
	BUTTONMARBLES1,
	BUTTONMARBLES1CLCK,
	BUTTONMARBLES2,
	BUTTONMARBLES2CLCK,
	BUTTONMARBLES3,
	BUTTONMARBLES3CLCK,
	BUTTONMARBLES4,
	BUTTONMARBLES4CLCK,
	REDMARBLE,
	REDMARBLESM,
	GREENMARBLE,
	GREENMARBLESM,
	BLUEMARBLE,
	BLUEMARBLESM,
	YELLOWMARBLE,
	YELLOWMARBLESM,
	BLACKFOND,
	NUM_TEXTURES,  // Truco C++: n�mero de texturas definidas
};
enum TypoName {
	GRAND_CASINO,
	NUM_TYPO,
};
class Game : private GameStateMachine {
public:
	static int WIN_WIDTH;
	static int WIN_HEIGHT;
	static void inicializa(SDL_Window* window) { SDL_GetWindowSize(window, &WIN_WIDTH, &WIN_HEIGHT); }
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint TILE_SIDE = 1;
private:
	// Ventana de la SDL (se destruir� en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	std::array<const char*, NUM_TYPO> typo;

public:
	Game();
	~Game();
	void run();
	Texture* getTexture(TextureName name) const;
	const char* getTypo(TypoName name) const;
	SDL_Renderer* getRenderer() const;
	void push(GameState*);
	void replace(GameState*);
	void pop();
	void stop();

	std::mt19937 gen;
	std::mt19937& getGen() { return gen; }; // Devolver referencia
};
