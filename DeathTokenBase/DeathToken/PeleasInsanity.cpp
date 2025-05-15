#include "PeleasInsanity.h"
#include <algorithm>
#include <iostream>
#include <sstream>
PeleasInsanity::PeleasInsanity(Game* game)
  : GameState(game)
  , currentState(State::PRESENTACION)
  , inputJugador(new InputBox(game->getRenderer(),
                              game->getTypo(FIGHTS_SMALL),
                              static_cast<int>(Game::WIN_WIDTH / 3),
                              static_cast<int>(3 * Game::WIN_HEIGHT / 4),
                              true,
                              false,
                              400,
                              180))
  , descripcionBox(new DialogueBox(game->getRenderer(),
                                   game->getTypo(FIGHTS_SMALL),
                                   static_cast<int>(Game::WIN_WIDTH / 4),
                                   static_cast<int>(Game::WIN_HEIGHT / 4),
                                   true,
                                   true,
                                   500,
                                   200))
  , resultadoBox(new DialogueBox(game->getRenderer(),
                                 game->getTypo(FIGHTS_SMALL),
                                 static_cast<int>(Game::WIN_WIDTH / 4),
                                 static_cast<int>(Game::WIN_HEIGHT / 2),
                                 true,
                                 true,
                                 500,
                                 200))
  , rondasRestantesObjeto(3)
  , rondasTotales(0)
{
  generarNuevoObjeto();
  inputJugador->setMaxLength(4);
  addEventListener(inputJugador);
  addEventListener(descripcionBox);
  addEventListener(resultadoBox);
}

void PeleasInsanity::generarNuevoObjeto()
{
  std::cout << "\n=== GENERANDO NUEVO OBJETO ===" << std::endl;

  resetearCajasDialogo();
  objetoActual = generadorPrecios.generarObjeto();
  rondasActuales.clear();
  rondasRestantesObjeto = 3;

  // Mover el debug después de generar el objeto
  std::cout << "Rango: [" << objetoActual.minRango << "-"
            << objetoActual.maxRango << "]\n"
            << "Precio Real: " << objetoActual.precioReal << "\n"
            << "Descripción: " << objetoActual.descripcionRango << "\n"
            << "Modificador: " << objetoActual.descripcionModificador
            << std::endl;

  std::string descripcion = objetoActual.descripcionRango + "\n" +
                            objetoActual.descripcionModificador + "\n" +
                            "Rango: [" + std::to_string(objetoActual.minRango) +
                            "-" + std::to_string(objetoActual.maxRango) + "]";

  descripcionBox->showMessage(descripcion, true);
  resultadoBox->showMessage("Ronda 1/3 - Introduce tu guess", true);
  inputJugador->showMessage("");
}

void PeleasInsanity::resetearCajasDialogo()
{
  descripcionBox->resetHistory();
  resultadoBox->resetHistory();
  inputJugador->clearInput();
}

void PeleasInsanity::render() const
{
  SDL_Rect fondoRect = { 0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT };
  game->getTexture(PELEASLOCURAFONDO)->render(fondoRect);

  descripcionBox->render();
  resultadoBox->render();

  if (currentState == State::INPUT_JUGADOR) {
    inputJugador->render();
  }

  GameState::render();
}

void PeleasInsanity::update()
{
  Uint32 currentTime = SDL_GetTicks();
  float deltaTime = (currentTime - lastUpdate) / 1000.0f;

  // Debug: Mostrar estado actual
  static State previousState = State::PRESENTACION;
  if (previousState != currentState) {
    std::cout << "--- Cambio de estado: " << static_cast<int>(previousState)
              << " -> " << static_cast<int>(currentState) << std::endl;
    previousState = currentState;
  }

  descripcionBox->update(deltaTime);
  resultadoBox->update(deltaTime);

  switch (currentState) {
    case State::PRESENTACION:
      std::cout << "[PRESENTACION] Mostrando nuevo objeto. Tiempo restante: "
                << 2000 - (currentTime - stateStartTime) << "ms" << std::endl;
      if (currentTime - stateStartTime >= TIEMPO_PRESENTACION) {
        std::cout << ">>> Transición a INPUT_JUGADOR (tiempo completado)"
                  << std::endl;
        currentState = State::INPUT_JUGADOR;
        inputJugador->setActive(true);
        stateStartTime = currentTime;
      }
      break;

    case State::INPUT_JUGADOR:
      std::cout << "[INPUT_JUGADOR] Esperando entrada..." << std::endl;
      inputJugador->update(deltaTime);
      if (!inputJugador->getActive()) {
        std::cout << ">>> Input recibido: " << inputJugador->getMessage()
                  << std::endl;
        Ronda nuevaRonda;
        try {
          nuevaRonda.intentoJugador = std::stoi(inputJugador->getMessage());
        }
        catch (...) {
          nuevaRonda.intentoJugador = 0;
        }

       float desviacion;
        if (rondasRestantesObjeto == 3) {
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.15f;
        }
        else if (rondasRestantesObjeto == 2) {
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.07f;
        }
        else {
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.02f;
        }  // <--- ¡Aquí faltaba esta llave de cierre!

        std::normal_distribution<float> distRival(objetoActual.precioReal,
                                                  desviacion);
        nuevaRonda.intentoRival =
          std::clamp(static_cast<int>(distRival(generadorPrecios.gen)),
                     objetoActual.minRango,
                     objetoActual.maxRango);
        rondasActuales.push_back(nuevaRonda);
        currentState = State::COMPARACION;
        stateStartTime = currentTime;
      }
      break;

    case State::COMPARACION:
      std::cout << "[COMPARACION] Procesando resultados. Tiempo restante: "
                << 1000 - (currentTime - stateStartTime) << "ms" << std::endl;
      if (currentTime - stateStartTime >= TIEMPO_COMPARACION) {
        calcularResultadoRonda();
        auto& ronda = rondasActuales.back();

        std::cout << "Resultado Ronda:"
                  << "\n  Jugador: " << ronda.intentoJugador
                  << " (Diff: " << ronda.diferenciaJugador << ")"
                  << "\n  Rival: " << ronda.intentoRival
                  << " (Diff: " << ronda.diferenciaRival << ")" << std::endl;

        std::stringstream resultado;
        resultado << "Ronda " << (3 - rondasRestantesObjeto + 1) << "/3\n";
        resultado << "Tú: " << rondasActuales.back().intentoJugador << "\n";
        resultado << "Rival: " << rondasActuales.back().intentoRival << "\n";
        resultado << "Diferencia: " << rondasActuales.back().diferenciaJugador;

        resultadoBox->resetHistory();
        resultadoBox->showMessage(resultado.str(), true);

        if (--rondasRestantesObjeto > 0) {
          std::cout << ">>> Quedan " << rondasRestantesObjeto
                    << " rondas. Transición a SIGUIENTE_RONDA" << std::endl;
          currentState = State::SIGUIENTE_RONDA;
        }
        else {
          std::cout << ">>> Última ronda completada. Transición a FINAL_OBJETO"
                    << std::endl;
          currentState = State::FINAL_OBJETO;
        }
        stateStartTime = currentTime;
      }
      break;

    case State::SIGUIENTE_RONDA:
      std::cout << "[SIGUIENTE_RONDA] Preparando ronda. Tiempo restante: "
                << 2000 - (currentTime - stateStartTime) << "ms" << std::endl;
      if (currentTime - stateStartTime >= TIEMPO_SIGUIENTE_RONDA) {
        std::cout << ">>> Transición a INPUT_JUGADOR (nueva ronda)"
                  << std::endl;
        prepararSiguienteRonda();
        currentState = State::INPUT_JUGADOR;
        stateStartTime = currentTime;
      }
      break;

    case State::FINAL_OBJETO:
      std::cout << "[FINAL_OBJETO] Determinando ganador. Tiempo restante: "
                << 3000 - (currentTime - stateStartTime) << "ms" << std::endl;
      if (currentTime - stateStartTime >= TIEMPO_FINAL_OBJETO) {
        std::cout << ">>> Resultado final del objeto:" << std::endl;
        determinarGanadorObjeto();
        if (++rondasTotales < 3) {
          std::cout << ">>> Iniciando nuevo objeto (" << rondasTotales
                    << "/3). Transición a PRESENTACION" << std::endl;
          generarNuevoObjeto();
          currentState = State::PRESENTACION;
        }
        else {
          std::cout << ">>> Juego completado. Transición a FINAL_JUEGO"
                    << std::endl;
          currentState = State::FINAL_JUEGO;
        }
        stateStartTime = currentTime;
      }
      break;
  }

  lastUpdate = currentTime;
  GameState::update();
}
void PeleasInsanity::calcularResultadoRonda()
{
  auto& ronda = rondasActuales.back();
  ronda.diferenciaJugador = abs(ronda.intentoJugador - objetoActual.precioReal);
  ronda.diferenciaRival = abs(ronda.intentoRival - objetoActual.precioReal);
}

void PeleasInsanity::prepararSiguienteRonda()
{
  std::string mensaje =
    "Ronda " + std::to_string(3 - rondasRestantesObjeto + 1) + "/3\n";
  mensaje += "Nuevo intento - Precio entre [" +
             std::to_string(objetoActual.minRango) + "-" +
             std::to_string(objetoActual.maxRango) + "]";

  resultadoBox->resetHistory();
  resultadoBox->showMessage(mensaje, true);
  inputJugador->clearInput();
  inputJugador->setActive(true);
}

void PeleasInsanity::determinarGanadorObjeto()
{
  int totalJugador = 0;
  int totalRival = 0;
  for (const auto& ronda : rondasActuales) {
    totalJugador += ronda.diferenciaJugador;
    totalRival += ronda.diferenciaRival;
  }

  std::string resultadoFinal = "Objeto terminado!\nPrecio real: " +
                               std::to_string(objetoActual.precioReal) + "\n";
  resultadoFinal +=
    "Tu diferencia total: " + std::to_string(totalJugador) + "\n";
  resultadoFinal += "Diferencia rival: " + std::to_string(totalRival) + "\n";
  resultadoFinal +=
    (totalJugador < totalRival) ? "¡Ganas este objeto!" : "¡El rival gana!";

  resultadoBox->resetHistory();
  resultadoBox->showMessage(resultadoFinal, true);
}