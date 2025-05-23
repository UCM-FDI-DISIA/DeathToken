﻿#ifndef PELEAS_INSANITY_H
#define PELEAS_INSANITY_H

#include "dialogueBox.h"
#include "gameState.h"
#include "generaPrecios.h"
#include "inputBox.h"
#include "ui.h"
#include <vector>

const Uint32 TIEMPO_PRESENTACION = 3000;
const Uint32 TIEMPO_COMPARACION = 6000;
const Uint32 TIEMPO_SIGUIENTE_RONDA = 2500;
const Uint32 TIEMPO_FINAL_OBJETO = 4000;
const Uint32 TIEMPO_RESULTADO_MOSTRADO = 2500;
const Uint32 TIEMPO_RESULTADO = 4000;


struct Ronda {
  int intentoJugador = 0;
  int intentoRival = 0;
  int diferenciaJugador = 0;
  int diferenciaRival = 0;
};

class PeleasInsanity : public GameState {
public:
  explicit PeleasInsanity(Game* game);
  ~PeleasInsanity();

  void render() const override;
  void update() override;
  inline void empezaPartida() { empezarPartida = true; PlayerEconomy::setInsanity(PlayerEconomy::getInsanity() - 1); }
  void showTutorial() override { ui->OnInfo(); };

private:
  enum class State {
    PRESENTACION,
    INPUT_JUGADOR,
    MOSTRAR_RESULTADO_RONDA,
    SIGUIENTE_RONDA,
    FINAL_OBJETO,
    FINAL_JUEGO
  };

  // Lógica del juego
  void generarNuevoObjeto();
  void calcularResultadoRonda();
  void determinarGanadorObjeto();
  void prepararSiguienteRonda();
  void resetearCajasDialogo();

  // Estado
  State currentState;
  Uint32 stateStartTime = 0;
  Uint32 lastUpdate = 0;
  bool mostrarTextoResultado = false;

  // Componentes UI
  InputBox* inputJugador = nullptr;
  DialogueBox* descripcionBox = nullptr;
  DialogueBox* rondaBox = nullptr;
  DialogueBox* resultadoBox = nullptr;
  UIPeleasInsanity* ui = nullptr;
  HUDBet* bet;

  // Datos juego
  GeneraPrecios generadorPrecios;
  InfoObjeto objetoActual;
  std::vector<Ronda> rondasActuales;
  int rondasRestantesObjeto = 3;
  int rondasTotales = 0;

  // Control de partida
  bool empezarPartida = false;
  bool partidaTerminada = false;
  std::string ganador = "";
  bool objetoTerminado = false;
  bool resultadoMostrado = false;
};

#endif  // PELEAS_INSANITY_H
