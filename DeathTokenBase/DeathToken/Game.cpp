#include <iostream>
#include "FirebaseUtils.h"
#include "game.h"
#include "json.hpp"
#include "mainMenu.h"
#include "pauseState.h"
#include "sdlutils.h"
#include "SoundManager.h"
<<<<<<< Updated upstream
#include "MainMenu.h"
#include "finalMenu.h"
#include <vector>
=======
#include <iostream>
>>>>>>> Stashed changes
#include <string>
#include <vector>
using namespace std;

int Game::WIN_WIDTH = 0;
int Game::WIN_HEIGHT = 0;


using json = nlohmann::json;

// Especificación de las texturas del juego
<<<<<<< Updated upstream
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
	///
	v.push_back(TextureSpec{ "baccarat/Baccarat_bg2.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Blackjack_bg2.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/BaccaratFlip__mask.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/barajaBaccarat.png", 14, 1 });
	v.push_back(TextureSpec{ "map/Casino_baccarat_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bf.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bj.png", 1, 1 });
	v.push_back(TextureSpec{ "baccarat/Bb.png", 1, 1 });
	///
	v.push_back(TextureSpec{ "map/Casino_slots_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_marbles_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_ring_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "map/Casino_roulette_cut.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Exit.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Exit_HV.png", 1, 1 });
	///
	v.push_back(TextureSpec{ "ui/Exit_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Erase_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowL.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/ArrowL_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowL_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowR_Clicked.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/ArrowU.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowU_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowD.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/ArrowD_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Info.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/Info_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Info_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Repeat_Clicked.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/Go.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Go_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/Go_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x2.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x2_HV.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/slots/x2_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x3_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x5.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/slots/x5_HV.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/slots/x5_Clicked.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_1.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_2.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_5.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "ui/chips/chip_10.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_25.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_50.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_100.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/chips/chip_200.png", 1, 1 });
=======
vector<Game::TextureSpec> Game::loadTextures()
{
  vector<Game::TextureSpec> v;
  v.push_back(TextureSpec{ "slots/celdaSlots.png", 1, 1 });
  v.push_back(TextureSpec{ "slots/bet.png", 1, 1 });
  v.push_back(TextureSpec{ "slots/iconosSlots.png", 7, 1 });
  v.push_back(TextureSpec{ "slots/button.png", 1, 1 });
  v.push_back(TextureSpec{ "slots/buttonClick.png", 1, 1 });
  v.push_back(TextureSpec{ "slots/fondo.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/Tick.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/Cross.png", 1, 1 });
  v.push_back(TextureSpec{ "map/Casino_bg.png", 1, 1 });
  ///
  v.push_back(TextureSpec{ "baccarat/Baccarat_bg2.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/Blackjack_bg2.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/BaccaratFlip__mask.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/barajaBaccarat.png", 14, 1 });
  v.push_back(TextureSpec{ "map/Casino_baccarat_cut.png", 14, 1 });
  v.push_back(TextureSpec{ "baccarat/Bf.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/Bj.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/Bb.png", 1, 1 });
  ///
  v.push_back(TextureSpec{ "map/Casino_slots_cut.png", 1, 1 });
  v.push_back(TextureSpec{ "map/Casino_marbles_cut.png", 1, 1 });
  v.push_back(TextureSpec{ "map/Casino_ring_cut.png", 1, 1 });
  v.push_back(TextureSpec{ "map/Casino_roulette_cut.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Exit.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Exit_HV.png", 1, 1 });
  ///
  v.push_back(TextureSpec{ "ui/Exit_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Erase.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Erase_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Erase_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowL.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/ArrowL_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowL_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowR.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowR_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowR_Clicked.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/ArrowU.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowU_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowD.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/ArrowD_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Info.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/Info_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Info_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Repeat.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Repeat_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Repeat_Clicked.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/Go.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Go_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/Go_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x2.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x2_HV.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/slots/x2_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x3.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x3_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x3_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x5.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/slots/x5_HV.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/slots/x5_Clicked.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_1.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_2.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_5.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/chips/chip_10.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_25.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_50.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_100.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_200.png", 1, 1 });
>>>>>>> Stashed changes

  v.push_back(TextureSpec{ "ui/chips/chip_500.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_1K.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_2K.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/chips/chip_5K.png", 1, 1 });
  v.push_back(TextureSpec{ "player.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "marbles/Marbles_bg.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/1_1_NoFill_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/1_1_NoFill_Clicked_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/2_1_NoFill_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/2_1_NoFill_Clicked_MRB.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "ui/marbles/3_1_NoFill_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/3_1_NoFill_Clicked_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/4_3_NoFill_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/4_3_NoFill_Clicked_MRB.png", 1, 1 });
  v.push_back(TextureSpec{ "ui/marbles/marble_icons/RedMarbleIcon.png", 1, 1 });

<<<<<<< Updated upstream
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/RedMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon_sm.png",1,1 });
	//
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon.png",1,1 });
	v.push_back(TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon_sm.png",1,1 });
	v.push_back(TextureSpec{ "marbles/cup.png",1,1 });
	v.push_back(TextureSpec{ "blackFont.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteBG.png",1,1 });
	//
	v.push_back(TextureSpec{ "roulette/roulette_frame.png",1,1 });
	v.push_back(TextureSpec{ "roulette/roulette.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteLocura.png",1,1 });
	v.push_back(TextureSpec{ "roulette/Demoniosenala.png",1,1 });
	//
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
	v.push_back(TextureSpec{ "FondoTarjetasConReglas.png", 1, 1 });
	v.push_back(TextureSpec{ "FondoDeFotoDeTarjeta.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "TarjetaDePeleadores.png", 1, 1 });
	v.push_back(TextureSpec{ "Ring.png", 1, 1 });
	//
	v.push_back(TextureSpec{ "roulette/rouletteAnim0.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim1.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim2.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim3.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim4.png",1,1 });
	v.push_back(TextureSpec{ "roulette/rouletteAnim5.png",1,1 });
=======
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/RedMarbleIcon_sm.png", 1, 1 });
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon.png", 1, 1 });
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/GreenMarbleIcon_sm.png", 1, 1 });
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon.png", 1, 1 });
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/CyanMarbleIcon_sm.png", 1, 1 });
  //
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon.png", 1, 1 });
  v.push_back(
    TextureSpec{ "ui/marbles/marble_icons/YellowMarbleIcon_sm.png", 1, 1 });
  v.push_back(TextureSpec{ "marbles/cup.png", 1, 1 });
  v.push_back(TextureSpec{ "blackFont.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteBG.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "roulette/roulette_frame.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/roulette.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteLocura.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/Demoniosenala.png", 1, 1 });
  v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_baccarat.png", 1, 1 });
  v.push_back(TextureSpec{ "tutorial/Tutorial_bg2_baccarat.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "tutorial/Tutorial_bg3_baccarat.png", 1, 1 });
  v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_marbles.png", 1, 1 });
  v.push_back(TextureSpec{ "tutorial/Tutorial_bg1_marblesInsanity.png", 1, 1 });
  v.push_back(TextureSpec{ "FondoTarjetasConReglas.png", 1, 1 });
  v.push_back(TextureSpec{ "FondoDeFotoDeTarjeta.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "TarjetaDePeleadores.png", 1, 1 });
  v.push_back(TextureSpec{ "Ring.png", 1, 1 });
  //
  v.push_back(TextureSpec{ "roulette/rouletteAnim0.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim1.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim2.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim3.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim4.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim5.png", 1, 1 });
>>>>>>> Stashed changes

  v.push_back(TextureSpec{ "roulette/rouletteAnim6.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim7.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim8.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim9.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim10.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim11.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim12.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim13.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim14.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim15.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim16.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim17.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim18.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim19.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim20.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim21.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim22.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim23.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim24.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim25.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim26.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim27.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim28.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim29.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim30.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim31.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim32.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim33.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim34.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim35.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim36.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim37.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim38.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim39.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim40.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim41.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim42.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim43.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim44.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim45.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim46.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/rouletteAnim47.png", 1, 1 });

  v.push_back(TextureSpec{ "roulette/rouletteAnim48.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/RecompensasRoulette.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/RecompensasRouletteInsanity.png", 1, 1 });
  v.push_back(TextureSpec{ "roulette/ChooseDemon.png", 1, 1 });
  v.push_back(TextureSpec{ "baccarat/smoke.png", 9, 1 });

  v.push_back(TextureSpec{ "menus/pause.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/back.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/menu.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/rank.png", 1, 1 });

  v.push_back(TextureSpec{ "escenaTutorial/FlechasManos.png", 2, 1 });
  v.push_back(TextureSpec{ "escenaTutorial/PiedraPapelTijera.png", 3, 1 });

  v.push_back(TextureSpec{ "menus/GoodText.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/GoodEnding.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/BadText.png", 1, 1 });
  v.push_back(TextureSpec{ "menus/BadEnding.png", 1, 1 });

<<<<<<< Updated upstream
	v.push_back(TextureSpec{ "tutorial/Tutorial_slots.png",1,1 });
	v.push_back(TextureSpec{ "tutorial/Tutorial_slots_locura.png",1,1 });

	v.push_back(
		TextureSpec{ "Fighters/skeletor.png", 1, 1 });  // TEXTURE_SKELETOR
	v.push_back(
		TextureSpec{ "Fighters/romelario.png", 1, 1 });  // TEXTURE_ROMELARIO
	v.push_back(TextureSpec{ "Fighters/alfredo.png", 1, 1 });  // TEXTURE_ALFREDO
	v.push_back(TextureSpec{ "Fighters/boodoo.png", 1, 1 });   // TEXTURE_BOODOO
	v.push_back(TextureSpec{ "Fighters/corneo.png", 1, 1 });   // TEXTURE_CORNEO
	v.push_back(
		TextureSpec{ "Fighters/mcdougald.png", 1, 1 });  // TEXTURE_MCDOUGALD
	v.push_back(TextureSpec{
	  "Fighters/paulter_geist.png", 1, 1 });  // TEXTURE_PAULTER_GEIST
	v.push_back(TextureSpec{ "Fighters/potape.png", 1, 1 });  // TEXTURE_POTAPE

	v.push_back(TextureSpec{ "RingLocura.png", 1, 1 });
	v.push_back(TextureSpec{ "Precios.png", 1, 1 });
	v.push_back(TextureSpec{ "Results.png", 1, 1 });

	v.push_back(TextureSpec{ "Board.png", 1, 1 });
	v.push_back(TextureSpec{ "Items/Gramophone.png", 1, 1 });
	v.push_back(TextureSpec{ "Items/Lamp.png", 1, 1 });
	v.push_back(TextureSpec{ "Items/Perfume.png", 1, 1 });
	v.push_back(TextureSpec{ "Items/Phone.png", 1, 1 });
	v.push_back(TextureSpec{ "Items/Champagne.png", 1, 1 });

	v.push_back(TextureSpec{ "RoundBoard.png", 1, 1 });
	v.push_back(TextureSpec{ "ui/hud/insanityFrame_white.png",1,1 });
	v.push_back(TextureSpec{ "ui/hud/insanityFrame_yellow.png",1,1 });
	v.push_back(TextureSpec{ "ui/hud/insanitySlot.png",1,1 });

	v.push_back(TextureSpec{ "baccarat/counter.png",10,1 });
	v.push_back(TextureSpec{ "roulette/scythe.png",1,1 });
=======
  v.push_back(TextureSpec{ "tutorial/Tutorial_slots.png", 1, 1 });
  v.push_back(TextureSpec{ "tutorial/Tutorial_slots_locura.png", 1, 1 });
  v.push_back(
    TextureSpec{ "Fighters/skeletor.png", 1, 1 });  // TEXTURE_SKELETOR
  v.push_back(
    TextureSpec{ "Fighters/romelario.png", 1, 1 });  // TEXTURE_ROMELARIO
  v.push_back(TextureSpec{ "Fighters/alfredo.png", 1, 1 });  // TEXTURE_ALFREDO
  v.push_back(TextureSpec{ "Fighters/boodoo.png", 1, 1 });   // TEXTURE_BOODOO
  v.push_back(TextureSpec{ "Fighters/corneo.png", 1, 1 });   // TEXTURE_CORNEO
  v.push_back(
    TextureSpec{ "Fighters/mcdougald.png", 1, 1 });  // TEXTURE_MCDOUGALD
  v.push_back(TextureSpec{
    "Fighters/paulter_geist.png", 1, 1 });  // TEXTURE_PAULTER_GEIST
  v.push_back(TextureSpec{ "Fighters/potape.png", 1, 1 });  // TEXTURE_POTAPE

  v.push_back(TextureSpec{ "RingLocura.png", 1, 1 });
  v.push_back(TextureSpec{ "Precios.png", 1, 1 });
  v.push_back(TextureSpec{ "Results.png", 1, 1 });
  v.push_back(TextureSpec{ "Board.png", 1, 1 });

  v.push_back(TextureSpec{ "Items/Gramophone.png", 1, 1 });
  v.push_back(TextureSpec{ "Items/Lamp.png", 1, 1 });
  v.push_back(TextureSpec{ "Items/Perfume.png", 1, 1 });
  v.push_back(TextureSpec{ "Items/Phone.png", 1, 1 });
  v.push_back(TextureSpec{ "Items/Champagne.png", 1, 1 });
  v.push_back(TextureSpec{ "RoundBoard.png", 1, 1 });
>>>>>>> Stashed changes

  if (v.size() != NUM_TEXTURES)
    throw "Texturas sin índice, error al cargar";
  return v;
}

<<<<<<< Updated upstream
vector<TTF_Font*> Game::loadFonts() {
	vector<TTF_Font*> v;
	int x = (int)((200 / 1920.0f) * WIN_WIDTH);
	int y = (int)((125 / 1920.0f) * WIN_WIDTH);
	int z = (int)((50 / 1920.0f) * WIN_WIDTH);
	int t = (int)((100 / 1920.0f) * WIN_WIDTH);

	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE1));
	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE2));
	v.push_back(TTF_OpenFont("assets/typo/Grand_Casino.otf", CASINOSIZE3));
	v.push_back(TTF_OpenFont("assets/cute_dino_2/Cute Dino.ttf", t));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", x));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", y));
	v.push_back(TTF_OpenFont("assets/typo/Magnificent Serif.ttf", z));
	v.push_back(TTF_OpenFont("assets/cute_dino_2/Cute Dino.ttf", FONTBIGSIZE));
	v.push_back(TTF_OpenFont("assets/Candice/CANDY.TTF", FONTSMALLSIZE));
	if (v.size() != NUM_TYPO) throw "Fonts sin índice, error al cargar";
	return v;
=======
vector<TTF_Font*> Game::loadFonts()
{
  vector<TTF_Font*> v;
  int x = (int)((200 / 1920.0f) * WIN_WIDTH);
  v.push_back(TTF_OpenFont("../assets/typo/Grand_Casino.otf", FONTBIGSIZE));
  v.push_back(TTF_OpenFont("../assets/typo/Magnificent Serif.ttf", x));
  v.push_back(TTF_OpenFont("../assets/cute_dino_2/Cute Dino.ttf", FONTBIGSIZE));
  v.push_back(TTF_OpenFont("../assets/Candice/CANDY.TTF", FONTSMALLSIZE));
  if (v.size() != NUM_TYPO)
    throw "Fonts sin índice, error al cargar";
  return v;
>>>>>>> Stashed changes
};

Game::Game()
{
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
  vector<TextureSpec> textureSpec = loadTextures();
  std::string textureRoot = "../assets/images/";
  for (int i = 0; i < NUM_TEXTURES; ++i)
    textures.push_back(new Texture(renderer,
                                   (textureRoot + textureSpec[i].name).c_str(),
                                   textureSpec[i].numRows,
                                   textureSpec[i].numColumns));

<<<<<<< Updated upstream
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
	// Carga las texturas
	startDatabase();

	vector<TextureSpec> textureSpec = loadTextures();
	std::string textureRoot = "assets/images/";
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures.push_back(new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns));

	TTF_Init();
	fonts = loadFonts();
	// CARGA DE SONIDOS
	SoundManager& soundManager = SoundManager::obtenerInstancia();
	if (!soundManager.inicializar(44100, 2, 2048)) {
		std::cerr << "Error initializing SoundManager" << std::endl;
		SDL_Quit();
	}
	/*if (!soundManager.cargarSonido("../assets/sonido/TralaleroTralala.wav", "EntrarJuego",SoundManager::EFECTO)) {
=======
  TTF_Init();
  fonts = loadFonts();
  // CARGA DE SONIDOS
  SoundManager& soundManager = SoundManager::obtenerInstancia();
  if (!soundManager.inicializar(44100, 2, 2048)) {
    std::cerr << "Error initializing SoundManager" << std::endl;
    SDL_Quit();
  }
  /*if (!soundManager.cargarSonido("../assets/sonido/TralaleroTralala.wav", "EntrarJuego",SoundManager::EFECTO)) {
>>>>>>> Stashed changes
		  std::cerr << "Error al cargar el sonido de la entrarjuego." << std::endl;
	  }*/
  soundManager.ajustarVolumenEfectos(50);
  if (!soundManager.cargarSonido("../assets/sonido/Generales/PresionaBoton.wav",
                                 "PresionaBoton",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido(
        "../assets/sonido/Generales/PresionaBotonPeleas.wav",
        "PresionaBotonPeleas",
        SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

<<<<<<< Updated upstream
	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonPeleas.wav",
		"PresionaBotonPeleas",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
	}

	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonCanicas.wav",
		"PresionaBotonCanicas",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
	}

	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonBaccarat.wav",
		"PresionaBotonBaccarat",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
	}
	if (!soundManager.cargarSonido(
		"assets/sonido/Generales/PresionaBotonSlots.wav",
		"PresionaBotonSlots",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
	}

	if (!soundManager.cargarSonido("assets/sonido/Ruleta/RuletaSonido.wav",
		"RuletaSonido",
		SoundManager::EFECTO)) {
		std::cerr << "Error al cargar el sonido del Button." << std::endl;
	}

	if (loadFightersFromJSON("assets/jsons/peleadores.json") &&
		loadMatchupsFromJSON("assets/jsons/matchups.json")) {
#ifdef DEBUG
		cerr << "error en la carga de jsons de peleas" << endl;
#endif // DEBUG
	}

	MainMenu* menu = new MainMenu(this);
	pushState(menu);
=======
  if (!soundManager.cargarSonido(
        "../assets/sonido/Generales/PresionaBotonCanicas.wav",
        "PresionaBotonCanicas",
        SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido(
        "../assets/sonido/Generales/PresionaBotonBaccarat.wav",
        "PresionaBotonBaccarat",
        SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido(
        "../assets/sonido/Generales/PresionaBotonSlots.wav",
        "PresionaBotonSlots",
        SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Ruleta/RuletaSonido.wav",
                                 "RuletaSonido",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Generales/MarblesIntro.wav",
                                 "MarblesIntro",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Generales/BaccaratIntro.wav",
                                 "BaccaratIntro",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Generales/Fights.wav",
                                 "FightsIntro",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Generales/SlotsIntro.wav",
                                 "SlotsIntro",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }

  if (!soundManager.cargarSonido("../assets/sonido/Generales/StaticVinyl.mp3",
                                 "Static",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido("../assets/sonido/Generales/PokerChips.wav",
                                 "ChipPlaced",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido("../assets/sonido/Generales/SlotSpin.wav",
                                 "SlotSpin",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido("../assets/sonido/Generales/SlotChoose.wav",
                                 "SlotChoose",
                                 SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (!soundManager.cargarSonido(
        "../assets/sonido/Tutoriales/PasaPaginaTutorial.wav",
        "PasaPag",
        SoundManager::EFECTO)) {
    std::cerr << "Error al cargar el sonido del Button." << std::endl;
  }
  if (loadFightersFromJSON("peleadores.json") &&
      loadMatchupsFromJSON("../DeathToken/matchups.json")) {
#ifdef DEBUG
    cerr << "error en la carga de jsons de peleas" << endl;
#endif  // DEBUG
  }
>>>>>>> Stashed changes

  MainMenu* menu = new MainMenu(this);
  pushState(menu);

  //SEMILLA DE NUMEROS ALEATORIOS
  random_device rd;
  gen = std::mt19937(rd());  // Inicializar con una semilla aleatoria
}

<<<<<<< Updated upstream
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Elimina las texturas
	for (Texture* texture : textures) {
		delete texture;
	}
	for (TTF_Font* font : fonts) {
		TTF_CloseFont(font);
	}

	FirebaseUtils::DeleteFirebaseUtils();
	TTF_Quit();
	// Desactiva la SDL
	SDL_Quit();
=======
Game::~Game()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  // Elimina las texturas
  for (Texture* texture : textures)
    delete texture;
  TTF_Quit();
  // Desactiva la SDL
  SDL_Quit();
>>>>>>> Stashed changes
}
void Game::run()
{
  SoundManager& soundManager = SoundManager::obtenerInstancia();
  const int staticChannel = 0;
  bool staticPlaying = false;
  // Bucle principal del juego. Sigue mientras Mario este vivo o no haya llegado al final
  while (!empty()) {
    // Marca de tiempo del inicio de la iteración
    GameState* currentState = gameStates.top().get();
    bool enMenuOPausa = dynamic_cast<MainMenu*>(currentState) ||
                        dynamic_cast<PauseState*>(currentState);
    uint32_t frameStart = SDL_GetTicks();
    SDLUtils::updateDeltaTime();
    float dt = SDLUtils::getDeltaTime();
    if (enMenuOPausa) {
      if (staticPlaying) {
        Mix_HaltChannel(staticChannel);
        staticPlaying = false;
      }
    }
    else {
      if (!staticPlaying) {
        soundManager.reproducirEfectoCanalEsp(
          "Static", -1, staticChannel);  // -1 = loop infinito
        staticPlaying = true;
      }
    }
    update();  // Actualiza el estado de los objetos del juego

    SDL_RenderClear(renderer);
    render();  // Dibuja los objetos en la venta
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT ||
          (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
        stop();
      }
      else if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)) {
        if (!pause) {
          push(new PauseState(this, gameStates.top().get()));
          pause = true;  //si la pausa esta en true no se puede abrir otra
        }
      }
      else {
        handleEvent(event);
      }
    }

<<<<<<< Updated upstream
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				FirebaseUtils::SaveState(PlayerEconomy::getBlueSouls(), PlayerEconomy::getRedSouls(), PlayerEconomy::getInsanity());
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
=======
    // Tiempo que se ha tardado en ejecutar lo anterior
    uint32_t frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < Game::FRAME_RATE)
      SDL_Delay(Game::FRAME_RATE - frameTime);
  }
}
Texture* Game::getTexture(TextureName name) const
{
  return textures[name];
}
TTF_Font* Game::getTypo(TypoName name) const
{
  return fonts[name];
}
SDL_Renderer* Game::getRenderer() const
{
  return renderer;
}
>>>>>>> Stashed changes

void Game::push(GameState* nextState)
{
  pushState(nextState);
}
void Game::replace(GameState* nextState)
{
  replaceState(nextState);
}
void Game::pop()
{
  popState();
}
void Game::stop()
{
  while (!empty())
    popState();
}

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
#endif  // DEBUG

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