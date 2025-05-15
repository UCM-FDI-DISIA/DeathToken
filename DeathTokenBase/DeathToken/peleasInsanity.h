#ifndef PELEAS_INSANITY_H
#define PELEAS_INSANITY_H

#include "DialogueBox.h"
#include "GameState.h"
#include "GeneraPrecios.h"
#include "InputBox.h"
#include <vector>

const Uint32 TIEMPO_PRESENTACION = 3000;   
const Uint32 TIEMPO_COMPARACION = 2000;     
const Uint32 TIEMPO_SIGUIENTE_RONDA = 2500; 
const Uint32 TIEMPO_FINAL_OBJETO = 4000;   
struct Ronda {
  int intentoJugador;
  int intentoRival;
  int diferenciaJugador;
  int diferenciaRival;
};

class PeleasInsanity : public GameState {
public:
  PeleasInsanity(Game* game);
  void render() const override;
  void update() override;

private:
  enum class State {
    PRESENTACION,
    INPUT_JUGADOR,
    ESPERA_RIVAL,
    COMPARACION,
    SIGUIENTE_RONDA,
    FINAL_OBJETO,
    FINAL_JUEGO
  };

  void generarNuevoObjeto();
  void calcularResultadoRonda();
  void determinarGanadorObjeto();
  void prepararSiguienteRonda();
  void resetearCajasDialogo();

  State currentState;
  InputBox* inputJugador;
  DialogueBox* descripcionBox;
  DialogueBox* resultadoBox;
  GeneraPrecios generadorPrecios;
  InfoObjeto objetoActual;

  std::vector<Ronda> rondasActuales;
  int rondasRestantesObjeto;
  int rondasTotales;
  int precioReal;
  int guessRival;

  Uint32 stateStartTime;
  int lastUpdate;
};

#endif  