#include "Game.h"
#include "json.hpp"
#include "Menu.h"
#include "sdlutils.h"
#include <iostream>
#include <string>

int Game::WIN_WIDTH = 0;
int Game::WIN_HEIGHT = 0;

using json = nlohmann::json;
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
	TextureSpec{"celdaSlots.png",1,1},
	TextureSpec{"baccarat/Tick.png",1,1},
	TextureSpec{"baccarat/Cross.png",1,1},
	TextureSpec{"iconosSlots.png",7,1},
	TextureSpec{"map/Casino_bg.png", 1, 1},
	TextureSpec{"baccarat/Baccarat_bg2.png", 1, 1},
	TextureSpec{"baccarat/Blackjack_bg2.png", 1, 1},
	TextureSpec{"baccarat/barajaBaccarat.png", 14, 1},
	TextureSpec{"map/Casino_baccarat_cut.png", 1, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"map/Casino_marbles_cut.png", 1, 1},
	TextureSpec{"DeathTokenToken.png", 1, 1},
	TextureSpec{"ui/Exit.png", 1, 1},
	TextureSpec{"ui/Exit_HV.png", 1, 1},
	TextureSpec{"ui/Exit_Clicked.png", 1, 1},
	TextureSpec{"ui/Erase.png", 1, 1},
	TextureSpec{"ui/Erase_HV.png", 1, 1},
	TextureSpec{"ui/Erase_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowL.png", 1, 1},
	TextureSpec{"ui/ArrowL_HV.png", 1, 1},
	TextureSpec{"ui/ArrowL_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowR.png", 1, 1},
	TextureSpec{"ui/ArrowR_HV.png", 1, 1},
	TextureSpec{"ui/ArrowR_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowU.png", 1, 1},
	TextureSpec{"ui/ArrowU_Clicked.png", 1, 1},
	TextureSpec{"ui/ArrowD.png", 1, 1},
	TextureSpec{"ui/ArrowD_Clicked.png", 1, 1},
	TextureSpec{"ui/Info.png", 1, 1},
	TextureSpec{"ui/Info_HV.png", 1, 1},
	TextureSpec{"ui/Info_Clicked.png", 1, 1},
	TextureSpec{"ui/Repeat.png", 1, 1},
	TextureSpec{"ui/Repeat_HV.png", 1, 1},
	TextureSpec{"ui/Repeat_Clicked.png", 1, 1},
	TextureSpec{"ui/Go.png", 1, 1},
	TextureSpec{"ui/Go_HV.png", 1, 1},
	TextureSpec{"ui/Go_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x2.png", 1, 1},
	TextureSpec{"ui/slots/x2_HV.png", 1, 1},
	TextureSpec{"ui/slots/x2_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x3.png", 1, 1},
	TextureSpec{"ui/slots/x3_HV.png", 1, 1},
	TextureSpec{"ui/slots/x3_Clicked.png", 1, 1},
	TextureSpec{"ui/slots/x5.png", 1, 1},
	TextureSpec{"ui/slots/x5_HV.png", 1, 1},
	TextureSpec{"ui/slots/x5_Clicked.png", 1, 1},
	TextureSpec{"ui/chips/chip_1.png", 1, 1},
	TextureSpec{"ui/chips/chip_2.png", 1, 1},
	TextureSpec{"ui/chips/chip_5.png", 1, 1},
	TextureSpec{"ui/chips/chip_10.png", 1, 1},
	TextureSpec{"ui/chips/chip_25.png", 1, 1},
	TextureSpec{"ui/chips/chip_50.png", 1, 1},
	TextureSpec{"ui/chips/chip_100.png", 1, 1},
	TextureSpec{"ui/chips/chip_200.png", 1, 1},
	TextureSpec{"ui/chips/chip_500.png", 1, 1},
	TextureSpec{"ui/chips/chip_1K.png", 1, 1},
	TextureSpec{"ui/chips/chip_2K.png", 1, 1},
	TextureSpec{"ui/chips/chip_5K.png", 1, 1},
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
	TextureSpec{"ui/marbles/marble_icons/RedMarbleIcon_sm.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/GreenMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/GreenMarbleIcon_sm.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/CyanMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/CyanMarbleIcon_sm.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/YellowMarbleIcon.png",1,1},
	TextureSpec{"ui/marbles/marble_icons/YellowMarbleIcon_sm.png",1,1},
	TextureSpec{"blackFont.png",1,1},
	TextureSpec{"roulette/rouletteBG.png",1,1},
	TextureSpec{"roulette/roulette.png",1,1},
	TextureSpec{"roulette/rouletteLocura.png",1,1},
	TextureSpec{"roulette/rouletteArrow.png",1,1},
	TextureSpec{"tutorial/Tutorial_bg1_baccarat.png",1,1},
	TextureSpec{"tutorial/Tutorial_bg2_baccarat.png",1,1},
	TextureSpec{"tutorial/Tutorial_bg3_baccarat.png",1,1},
	TextureSpec{"FondoTarjetasConReglas.png", 1, 1},
	TextureSpec{"FondoDeFotoDeTarjeta.png", 1, 1},
	TextureSpec{"TarjetaDePeleadores.png", 1, 1},

};

std::array<std::string, NUM_TYPO> typoList{
	"../assets/typo/Grand_Casino.otf",
	"../assets/typo/Magnificent Serif.ttf",
};

TTF_Font* Game::font = nullptr;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Death Token 1x01",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
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

	TTF_Init();
	font = TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", FONTBIGSIZE);
	for (int i = 0; i < NUM_TYPO; i++)
	{
		typo[i] = typoList[i].c_str();
	}
	if (loadFightersFromJSON("peleadores.json") && loadMatchupsFromJSON("../DeathToken/matchups.json")) {
#ifdef DEBUG
		cerr << "error en la carga de jsons de peleas" << endl;
#endif // DEBUG
	}
	Menu* menu = new Menu(this);
	pushState(menu);

	//SEMILLA DE NUMEROS ALEATORIOS
	random_device rd;
	gen = std::mt19937(rd()); // Inicializar con una semilla aleatoria
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;
	TTF_Quit();
	// Desactiva la SDL
	SDL_Quit();
}
void Game::run() {
	// Bucle principal del juego. Sigue mientras Mario este vivo o no haya llegado al final
	while (!empty()) {
		// Marca de tiempo del inicio de la iteración
		uint32_t frameStart = SDL_GetTicks();
		SDLUtils::updateDeltaTime();
		float dt = SDLUtils::getDeltaTime();


		update();       // Actualiza el estado de los objetos del juego

		SDL_RenderClear(renderer);
		render();       // Dibuja los objetos en la venta
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				stop();
			else
				handleEvent(event);
		}


		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < Game::FRAME_RATE)
			SDL_Delay(Game::FRAME_RATE - frameTime);


	}
}
Texture* Game::getTexture(TextureName name) const {
	return textures[name];
}
const char* Game::getTypo(TypoName name) const {
	return typo[name];
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

bool Game::loadFightersFromJSON(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
#ifdef DEBUG
		std::cout << "No se pudo abrir el archivo de peleadores." << endl;
#endif // DEBUG

		return false;
	}

	json j;
	file >> j;

	for (auto& item : j["peleadores"]) {
		Fighter fighter;
		// Convertir el JSON a string antes de pasarlo
		fighter.loadFromJSON(item.dump());
		fighters.push_back(fighter);
	}

	file.close();
	return true;
}

bool Game::loadMatchupsFromJSON(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
#ifdef DEBUG
		cout << "No se pudo abrir el archivo de enfrentamientos." << endl;
#endif
		return false;
	}

	try {
		json j;
		file >> j;

		// Verificar si "matchups" existe en el JSON
		if (j.find("matchups") == j.end()) {
#ifdef DEBUG
			cout << "No se encuentra el campo 'matchups' en el JSON." << endl;
#endif
			return false;
		}

		// Procesar el JSON y cargar los enfrentamientos
		for (auto& item : j["matchups"]) {
			int id1 = item["F1"];
			int id2 = item["F2"];
			int advantageFighterIndex = item["advantageFighterIndex"];
			string battleDescription = item["battleDescription"];

			if (id1 < 0 || id1 >= fighters.size() || id2 < 0 ||
				id2 >= fighters.size()) {
#ifdef DEBUG
				cout << "Índice de peleador inválido." << endl;
#endif
				continue;
			}

			Matchup matchup;
			matchup.fighter1 = fighters[id1];
			matchup.fighter2 = fighters[id2];
			matchup.advantageFighterIndex = advantageFighterIndex;
			matchup.battleDescription = battleDescription;

			battleQueue.push_back(matchup);
		}
	}
	catch (const json::parse_error& err) {
#ifdef DEBUG
		cout << "Error al procesar el JSON: " << e.what() << endl;
#endif
		return false;
	}

	file.close();
	return true;
}