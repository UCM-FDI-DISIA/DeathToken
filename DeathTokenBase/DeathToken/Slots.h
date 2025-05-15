#pragma once
#include "gameState.h"
#include "button.h"
#include "ui.h"

// Clase abstracta de la que heredan SlotsNormal y SlotsInstanity con elementos comunes
class Slots : public GameState {
protected:
	long long bet; // apuesta en el juego actual
	std::vector<int> multiplicadores = { 2,3,5,10,50,80,120 }; // Multiplicadores asociados a los 7 iconos
	ButtonSlots* btnBet; // Boton para poner la apuesta

	UISlots* ui; // Ui del juego
	HUDBet* hud; // Hud
public:
	inline Slots(Game* g) : GameState(g), ui(new UISlots(this, g, this)), hud(new HUDBet(this)), bet(0), btnBet() // Crea el UI y el Hud
	{
		hud->refresh(); //Actualiza el hud al entrar
	}
	inline virtual ~Slots() {
		delete ui;
		HUDManager::popGame();
	}
	virtual void iniciarGiro() = 0; //Metodo que inicia el juego
	inline void setBetTurno(long long n) { bet = n; } // Asigna la apuesta
	inline void clear() { //Metodo para vaciar el botón de apuestas y aplicar la actual
		btnBet->clear();
		PlayerEconomy::setBet(0);
		hud->refresh();
	}
	inline virtual void showTutorial() override { ui->OnInfo(); } // Muestra el tutorial. Se llama solo la primera vez
};