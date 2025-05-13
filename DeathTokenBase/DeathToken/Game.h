#pragma once
#include "gameStateMachine.h"
#include "fighter.h"
#include "HUD.h"
#include "texture.h"
#include <cassert>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>

class Player;


using uint = unsigned int;

enum TextureName {
	CELDA,
	BETSLOTS,
	ICONOS,
	BTNSLOT,
	BTNSLOTCLICK,
	SLOTSFONDO,
	TICK,
	CROSS,
	BACKGROUND,
	/// <summary>
	/// 
	/// </summary>
	BACMAT,
	BLACKMAT,
	FLIPCARD,
	CARDS,
	BACCARATBUT,
	FLIP,
	JACK,
	BET,
	/// <summary>

	SLOTSBUT,
	CANICASBUT,
	PELEASBUT,
	ROULETTEBUT,
	UIEXIT,
	UIEXITHV,
	/// <summary>
	/// 
	/// </summary>
	UIEXITCLCK,
	UIERASE,
	UIERASEHV,
	UIERASECLCK,
	UIARROWL,
	//
	UIARROWLHV,
	UIARROWLCLCK,
	UIARROWR,
	UIARROWRHV,
	UIARROWRCLCK,
	//
	UIARROWU,
	UIARROWUCLCK,
	UIARROWD,
	UIARROWDCLCK,
	UIINFO,
	//
	UIINFOHV,
	UIINFOCLCK,
	UIREPEAT,
	UIREPEATHV,
	UIREPEATCLCK,
	//
	UIGO,
	UIGOHV,
	UIGOCLCK,
	UIX2,
	UIX2HV,
	//
	UIX2CLCK,
	UIX3,
	UIX3HV,
	UIX3CLCK,
	UIX5,
	//
	UIX5HV,
	UIX5CLCK,
	UICHIP1,
	UICHIP2,
	UICHIP5,
	//
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
	//
	MARBLESBACK,
	BUTTONMARBLES1,
	BUTTONMARBLES1CLCK,
	BUTTONMARBLES2,
	BUTTONMARBLES2CLCK,
	//
	BUTTONMARBLES3,
	BUTTONMARBLES3CLCK,
	BUTTONMARBLES4,
	BUTTONMARBLES4CLCK,
	REDMARBLE,
	//
	REDMARBLESM,
	GREENMARBLE,
	GREENMARBLESM,
	BLUEMARBLE,
	BLUEMARBLESM,
	//
	YELLOWMARBLE,
	YELLOWMARBLESM,
	CUP,
	BLACKFOND,
	ROULETTEBG,
	//
	ROULETTEFRAME,
	ROULETTE,
	ROULETTEINSANITY,
	ROULETTEARROW,
	TUTORIAL1,
	TUTORIAL2,
	//
	TUTORIAL3,
	TUTORIALMARBLES,
	TUTORIALMARBLESINSANITY,
	PELEASFONDO,
	PELEASTARJETAFONDO,
	//
	PELEASTARJETAS,
	PELEASRING,
	//
	ROULETTEANIM0,
	ROULETTEANIM1,
	ROULETTEANIM2,
	//
	ROULETTEANIM3,
	ROULETTEANIM4,
	ROULETTEANIM5,
	ROULETTEANIM6,
	ROULETTEANIM7,
	//
	ROULETTEANIM8,
	ROULETTEANIM9,
	ROULETTEANIM10,
	ROULETTEANIM11,
	ROULETTEANIM12,
	//
	ROULETTEANIM13,
	ROULETTEANIM14,
	ROULETTEANIM15,
	ROULETTEANIM16,
	ROULETTEANIM17,
	//
	ROULETTEANIM18,
	ROULETTEANIM19,
	ROULETTEANIM20,
	ROULETTEANIM21,
	ROULETTEANIM22,
	//
	ROULETTEANIM23,
	ROULETTEANIM24,
	ROULETTEANIM25,
	ROULETTEANIM26,
	ROULETTEANIM27,
	//
	ROULETTEANIM28,
	ROULETTEANIM29,
	ROULETTEANIM30,
	ROULETTEANIM31,
	ROULETTEANIM32,
	//
	ROULETTEANIM33,
	ROULETTEANIM34,
	ROULETTEANIM35,
	ROULETTEANIM36,
	ROULETTEANIM37,
	//
	ROULETTEANIM38,
	ROULETTEANIM39,
	ROULETTEANIM40,
	ROULETTEANIM41,
	ROULETTEANIM42,
	//
	ROULETTEANIM43,
	ROULETTEANIM44,
	ROULETTEANIM45,
	ROULETTEANIM46,
	ROULETTEANIM47,
	//
	ROULETTEANIM48,
	ROULETTERECOMPENSAS,
	ROULETTERECOMPENSASINSANITY,
	CHOOSEDEMON,
	SMOKE,
	//
	PAUSE,
	BACK,
	MENU,
	RANK,
	//
	MANOS,
	ICONOPPT,
	//
	NUM_TEXTURES  // Truco C++: n�mero de texturas definidas
};
enum TypoName {
	GRAND_CASINO,
	AWARD,
	FIGHTS_BIG,
	FIGHTS_SMALL,
	NUM_TYPO
};

struct Matchup {
	Fighter fighter1;
	Fighter fighter2;
	int advantageFighterIndex = 0;
	string battleDescription;
};


class Game : public GameStateMachine {

private:
	// Ventana de la SDL (se destruir� en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::vector<Texture*> textures;

	std::vector<Fighter> fighters;
	std::vector<Matchup> battleQueue;  // Cola de enfrentamientos

	// Carga de objetos del json
	bool loadFightersFromJSON(const string& filename);
	bool loadMatchupsFromJSON(const string& filename);
	// Formato de la especificaci�n de una textura
	struct TextureSpec
	{
		const char* name;	// Ruta del archivo
		uint numColumns;	// Número de frames por fila
		uint numRows;		// Número de frames por columna
	};
	std::vector<TextureSpec> loadTextures();
	std::vector<TTF_Font*> loadFonts();
	std::vector<TTF_Font*> fonts;
	bool pause = false;
public:
	void setPause(bool p) {
		pause = p;
	}
	static int WIN_WIDTH;
	static int WIN_HEIGHT;
	static void inicializa(SDL_Window* window) { SDL_GetWindowSize(window, &WIN_WIDTH, &WIN_HEIGHT); }
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint FONTSMALLSIZE = 28;
	static constexpr uint FONTBIGSIZE = 32;
	Game();
	~Game();
	void run();
	Texture* getTexture(TextureName name) const;
	TTF_Font* getTypo(TypoName name) const;
	SDL_Renderer* getRenderer() const;
	void push(GameState*);
	void replace(GameState*);
	void pop();
	void stop();
	void startDatabase();


	inline const Matchup& GetMatchUp(int i) const { assert(i < battleQueue.size()); return battleQueue[i]; }

	std::mt19937 gen;
	std::mt19937& getGen() { return gen; }; // Devolver referencia
};
