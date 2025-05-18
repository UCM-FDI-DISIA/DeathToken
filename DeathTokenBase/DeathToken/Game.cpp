#include <iostream>
#include "firebaseUtils.h"
#include "game.h"
#include "json.hpp"
#include "mainMenu.h"
#include "pauseState.h"
#include "sdlUtils.h"
#include "soundManager.h"
#include "finalMenu.h"
#include <vector>
#include <string>
using namespace std;

int Game::WIN_WIDTH = 0;
int Game::WIN_HEIGHT = 0;


using json = nlohmann::json;

// Especificación de las texturas del juego
vector<Game::TextureSpec> Game::loadTextures() {
	vector<Game::TextureSpec> v;
	v.push_back(TextureSpec{ "slots/celdaSlots.png",1,1 });
	v.push_back(TextureSpec{ "slots/bet.png",1,1 });
	v.push_back(TextureSpec{ "slots/iconosSlots.png",7,1 });
	v.push_back(TextureSpec{ "slots/button.png",1,1 });
	v.push_back(TextureSpec{ "slots/buttonClick.png",1,1 });
	v.push_back(TextureSpec{ "slots/fondo.png",1,1 });
	v.push_back(TextureSpec{ "baccarat/Tick.png",1,1 });
	v.push_back(TextureSpec{ "baccarat/Cross.png",1,1 });
	v.push_back(TextureSpec{ "map/Casino_bg.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Baccarat_bg2.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Blackjack_bg2.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/BaccaratFlip__mask.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/barajaBaccarat.png", 14, 1 });
	v.push_back(TextureSpec{ "map/Casino_baccarat_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bf.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bj.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bb.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_slots_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_marbles_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_ring_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_roulette_cut_new.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Exit.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Exit_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Exit_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowL.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowL_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowL_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowU.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowU_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowD.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowD_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Info.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Info_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Info_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Go.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Go_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Go_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x2.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x2_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x2_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x5.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x5_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x5_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_1.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_2.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_5.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_10.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_25.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_50.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_100.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_200.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_500.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_1K.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_2K.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_5K.png", 1, 1 });
	v.push_back(TextureSpec{ "other/player.png", 1, 1 });
	v.push_back(TextureSpec{ "marbles/Marbles_bg.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/1_1_NoFill_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/1_1_NoFill_Clicked_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/2_1_NoFill_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/2_1_NoFill_Clicked_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/3_1_NoFill_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/3_1_NoFill_Clicked_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/4_3_NoFill_MRB.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/4_3_NoFill_Clicked_MRB.png",1,1 });
	v.push_back(TextureSpec{ "marbles/redMarble.png",1,1 });
	v.push_back(TextureSpec{ "marbles/greenMarble.png",1,1 });
	v.push_back(TextureSpec{ "marbles/blueMarble.png",1,1 });
	v.push_back(TextureSpec{ "marbles/yellowMarble.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/RedMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/RedMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "marbles/Marbles_tube.png",1,1 });
	v.push_back(TextureSpec{ "marbles/Marbles_slot.png",1,1 });
	v.push_back(TextureSpec{ "marbles/cup.png",1,1 });
	v.push_back(TextureSpec{ "other/blackFont.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteBG.png",1,1 });
	v.push_back(TextureSpec{ "roulette/roulette_frame.png",1,1 });
	v.push_back(TextureSpec{ "roulette/roulette.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteLocura.png",1,1 });
	v.push_back(TextureSpec{ "roulette/Demoniosenala.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_baccarat.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg2_baccarat.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg3_baccarat.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_blackjack.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg2_blackjack.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg3_blackjack.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_bet.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_flip.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_marbles.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_marblesInsanity.png",1,1 });
	v.push_back(TextureSpec{ "peleas/FondoTarjetasConReglas.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/FondoDeFotoDeTarjeta.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/TarjetaDePeleadores.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Ring.png", 1, 1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim0.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim1.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim2.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim3.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim4.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim5.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim6.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim7.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim8.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim9.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim10.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim11.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim12.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim13.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim14.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim15.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim16.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim17.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim18.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim19.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim20.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim21.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim22.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim23.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim24.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim25.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim26.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim27.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim28.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim29.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim30.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim31.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim32.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim33.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim34.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim35.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim36.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim37.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim38.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim39.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim40.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim41.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim42.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim43.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim44.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim45.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim46.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim47.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim48.png",1,1 });
	v.push_back(TextureSpec{ "roulette/RecompensasRoulette.png",1,1 });
	v.push_back(TextureSpec{ "roulette/RecompensasRouletteInsanity.png",1,1 });
	v.push_back(TextureSpec{ "roulette/ChooseDemon.png",1,1 });
	v.push_back(TextureSpec{ "baccarat/smoke.png",9,1 });
	v.push_back(TextureSpec{ "menus/pause.png",1,1 });
	v.push_back(TextureSpec{ "menus/back.png",1,1 });
	v.push_back(TextureSpec{ "menus/menu.png",1,1 });
	v.push_back(TextureSpec{ "menus/rank.png",1,1 });
	v.push_back(TextureSpec{ "escenaTutorial/FlechasManos.png",2,1 });
	v.push_back(TextureSpec{ "escenaTutorial/PiedraPapelTijera.png",3,1 });
	v.push_back(TextureSpec{ "menus/GoodText.png",1,1 });
	v.push_back(TextureSpec{ "menus/GoodEnding.png",1,1 });
	v.push_back(TextureSpec{ "menus/BadText.png",1,1 });
	v.push_back(TextureSpec{ "menus/BadEnding.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_slots.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_slots_locura.png",1,1 });
	v.push_back(TextureSpec{ "peleas/Fighters/skeletor.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/romelario.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/alfredo.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/boodoo.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/corneo.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/mcdougald.png", 1, 1 }); 
	v.push_back(TextureSpec{ "peleas/Fighters/paulter_geist.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Fighters/potape.png", 1, 1 }); 
	v.push_back(TextureSpec{ "peleas/RingLocura.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Precios.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Results.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Board.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Items/Gramophone.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Items/Lamp.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Items/Perfume.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Items/Phone.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/Items/Champagne.png", 1, 1 });
	v.push_back(TextureSpec{ "peleas/RoundBoard.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/hud/insanityFrame_white.png",1,1 });
	v.push_back(TextureSpec{ "ui/hud/insanityFrame_yellow.png",1,1 });
	v.push_back(TextureSpec{ "ui/hud/insanitySlot.png",1,1 });
	v.push_back(TextureSpec{ "baccarat/counter.png",10,1 });
	v.push_back(TextureSpec{ "roulette/scythe.png",1,1 });
	v.push_back(TextureSpec{ "menus/portada.png",1,1 });
	v.push_back(TextureSpec{ "menus/iniciar.png",1,1 });
	v.push_back(TextureSpec{ "menus/salir.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_Peleas1.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_Peleas2.png",1,1 });
	v.push_back(TextureSpec{ "ui/slots/Lock.png",1,1 });
	v.push_back(TextureSpec{ "ui/slots/Lock_Clicked.png",1,1 });
	v.push_back(TextureSpec{ "MarcoDialogo.png",1,1 });
	v.push_back(TextureSpec{ "interfaz locura.png",1,1 });

	if (v.size() != NUM_TEXTURES) throw "Texturas sin índice, error al cargar";
	return v;
}

vector<TTF_Font*> Game::loadFonts() {
	vector<TTF_Font*> v;
	int x = (int)((200 / 1920.0f) * WIN_WIDTH);
	int y = (int)((125 / 1920.0f) * WIN_WIDTH);
	int z = (int)((50 / 1920.0f) * WIN_WIDTH);
	int t = (int)((100 / 1920.0f) * WIN_WIDTH);

	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE1));
	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE2));
	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE3));
	v.push_back(TTF_OpenFont("assets/typo/Cute Dino.ttf", t));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", x));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", y));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", z));
	v.push_back(TTF_OpenFont("assets/typo/Cute Dino.ttf", FONTBIGSIZE));
	v.push_back(TTF_OpenFont("assets/typo/CANDY.TTF", FONTSMALLSIZE));
	if (v.size() != NUM_TYPO) throw "Fonts sin índice, error al cargar";
	return v;
};


Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Death Token",
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

	//Inicializa firebase
	startDatabase();

	// Carga las texturas
	vector<TextureSpec> textureSpec = loadTextures();
	std::string textureRoot = "assets/images/";
	for (auto& tex: textureSpec)
		textures.push_back(new Texture(renderer, (textureRoot + tex.name).c_str(), tex.numRows, tex.numColumns));

	TTF_Init();
	fonts = loadFonts();
	// CARGA DE SONIDOS
	SoundManager& soundManager = SoundManager::obtenerInstancia();
	if (!soundManager.inicializar(44100, 2, 2048)) {
#if _DEBUG
		std::cerr << "Error initializing SoundManager" << std::endl;
#endif
		SDL_Quit();
	}

	// Ajustar volumen de música y efectos
	soundManager.ajustarVolumenMusica(50);
	soundManager.ajustarVolumenEfectos(50);

	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonPeleas.wav",
		"PresionaBotonPeleas",
		SoundManager::EFECTO)) {
#ifdef DEBUG
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
#endif
	}

	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonCanicas.wav",
		"PresionaBotonCanicas",
		SoundManager::EFECTO)) {
#ifdef DEBUG
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
#endif
	}

	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonBaccarat.wav",
		"PresionaBotonBaccarat",
		SoundManager::EFECTO)) {
#ifdef DEBUG
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
#endif
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonSlots.wav",
		"PresionaBotonSlots",
		SoundManager::EFECTO)) {
#ifdef DEBUG
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
#endif
	}

	if (!soundManager.cargarSonido("assets/sonido/Ruleta/RuletaSonido.wav",
		"RuletaSonido",
		SoundManager::EFECTO)) {
#ifdef DEBUG
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
#endif
	}

	if (!soundManager.cargarSonido("assets/sonido/Generales/BaccaratIntro.wav",
		"BaccaratIntro",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido BaccaratIntro." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/MarblesIntro.wav",
		"MarblesIntro",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido MarblesIntro." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/PresionaBoton.wav",
		"PresionaBoton",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido PresionaBoton." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/SlotChoose.wav",
		"SlotChoose",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido SlotChoose." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/SlotSpin.wav",
		"SlotSpin",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido SlotSpin." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/SlotsIntro.wav",
		"SlotsIntro",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido SlotsIntro." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/StaticVinyl.mp3",
		"Static",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido Static." << std::endl;
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/Fights.wav", "FightsIntro", SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido Fights." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Generales/PokerChips.wav",
		"PokerChips",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido PokerChips." << std::endl;
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Tutoriales/PasaPaginaTutorial.wav",
		"PasaPaginaTutorial",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido PasaPaginaTutorial." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Music/BaccaratDToken.wav",
		"BaccaratDT",
		SoundManager::MUSICA)) {
		std::cerr << "Error al cargar la música BaccaratDToken." << std::endl;
	}
	if (!soundManager.cargarSonido("assets/sonido/Music/CanicasDT_v2.wav",
		"CanicasDT",
		SoundManager::MUSICA)) {
		std::cerr << "Error al cargar la música CanicasDT_v2." << std::endl;
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Music/PeleasDT.wav", "PeleasDT", SoundManager::MUSICA)) {
		std::cerr << "Error al cargar la música PeleasDT." << std::endl;
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Music/SlotsDT.wav", "SlotsDT", SoundManager::MUSICA)) {
		std::cerr << "Error al cargar la música SlotsDT." << std::endl;
	}


	if (loadFightersFromJSON("assets/jsons/peleadores.json") &&
		loadMatchupsFromJSON("assets/jsons/matchups.json")) {
#ifdef DEBUG
		cerr << "error en la carga de jsons de peleas" << endl;
#endif 
	}

	MainMenu* menu = new MainMenu(this);
	pushState(menu);

	//SEMILLA DE NUMEROS ALEATORIOS
	random_device rd;
	gen = std::mt19937(rd()); // Inicializar con una semilla aleatoria
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Elimina las texturas
	for (Texture* texture : textures) {
		delete texture;
	}
	for (TTF_Font* font : fonts){
		TTF_CloseFont(font);
	}
	FirebaseUtils::DeleteFirebaseUtils();
	TTF_Quit();
	// Desactiva la SDL
	SDL_Quit();
}
void Game::run() {
	SoundManager& soundManager = SoundManager::obtenerInstancia();
	const int staticChannel = 0; // Canal reservado para la estática
	bool staticPlaying = false; // Controlar si ya está sonando
	// Bucle principal del juego. Sigue mientras Mario este vivo o no haya llegado al final
	while (!empty()) {
		// Marca de tiempo del inicio de la iteración
		uint32_t frameStart = SDL_GetTicks();
		SDLUtils::updateDeltaTime();
		float dt = SDLUtils::getDeltaTime();

		update();       // Actualiza el estado de los objetos del juego

		SDL_RenderClear(renderer);
		render();       // Dibuja los objetos en la ventana
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			// Obtener el estado actual
			GameState* currentState = gameStates.top().get();

			// Verificar si estamos en menú principal o pausa
			bool enMenuOPausa = dynamic_cast<MainMenu*>(currentState) ||
				dynamic_cast<PauseState*>(currentState);

			// Control del sonido de estática
			if (enMenuOPausa) {
				if (staticPlaying) {
					Mix_HaltChannel(staticChannel);
					staticPlaying = false;
				}
			}
			else {
				if (!staticPlaying) {
                    soundManager.reproducirEfectoCanalEsp("Static", -1, staticChannel);
					staticPlaying = true;
				}
			}
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				FirebaseUtils::SaveState(PlayerEconomy::getBlueSouls(), PlayerEconomy::getRedSouls(), PlayerEconomy::getInsanity(), FirebaseUtils::tutorial);
				stop();
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p &&
				typeid(*gameStates.top()) != typeid(MainMenu) && typeid(*gameStates.top()) != typeid(FinalMenu)) {
				if (!pause)
				{
					push(new PauseState(this, gameStates.top().get()));
					pause = true;//si la pausa esta en true no se puede abrir otra
				}
			}
			else {
				handleEvent(event);
			}
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
TTF_Font* Game::getTypo(TypoName name) const {
	return fonts[name];
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

void Game::startDatabase()
{
	FirebaseUtils::StartFirebase();
	FirebaseUtils::CleanFirebase();
}

bool Game::loadFightersFromJSON(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
#ifdef DEBUG
		std::cout << "No se pudo abrir el archivo de peleadores." << endl;
#endif 

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
		cout << "Error al procesar el JSON: " << err.what() << endl;
#else
		(void)err;
#endif
		return false;
	}

	file.close();
	return true;
}