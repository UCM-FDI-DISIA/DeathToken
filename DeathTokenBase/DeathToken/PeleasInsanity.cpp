#include "PeleasInsanity.h"
#include <algorithm>
#include <iostream>
#include <random>  // Asegúrate que incluya <random> para std::normal_distribution y std::clamp
#include <sstream>
PeleasInsanity::PeleasInsanity(Game* game)
  : GameState(game)
  , currentState(State::PRESENTACION)
  , mostrarTextoResultado(false)
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
  , rondaBox(new DialogueBox(game->getRenderer(),
                             game->getTypo(FIGHTS_SMALL),
                             1605,
                             110,
                             true,
                             true,
                             300,
                             175))
  , resultadoBox(new DialogueBox(game->getRenderer(),
                                 game->getTypo(FIGHTS_SMALL),
                                 790,
                                 475,
                                 true,
                                 true,
                                 400,
                                 375))
  , partidaTerminada(false)
  , ganador("") 
{
  generarNuevoObjeto();
  inputJugador->setMaxLength(4);
  addEventListener(inputJugador);
  addEventListener(descripcionBox);
  addEventListener(resultadoBox);
}
PeleasInsanity::~PeleasInsanity()
{
  delete inputJugador;
  delete descripcionBox;
  delete rondaBox;
  delete resultadoBox;
}
void PeleasInsanity::generarNuevoObjeto()
{
  std::cout << "\n=== GENERANDO NUEVO OBJETO ===" << std::endl;

  resetearCajasDialogo();
  objetoActual = generadorPrecios.generarObjeto();

  if (objetoActual.minRango >= objetoActual.maxRango) {
    objetoActual.maxRango = objetoActual.minRango + 1;
    std::cerr << "Error: Rango inválido. Corregido a [" << objetoActual.minRango
              << "-" << objetoActual.maxRango << "]" << std::endl;
  }

  rondasActuales.clear();
  rondasRestantesObjeto = 3;
  partidaTerminada = false;
  ganador = "";

  std::string descripcion = "[Categoría] " + objetoActual.descripcionRango +
                            "\n[Estado] " + objetoActual.descripcionModificador;
  descripcionBox->showMessage(descripcion, true);

  rondaBox->showMessage("Ronda 1/3", true);
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

  SDL_Rect objetoRect = { static_cast<int>(Game::WIN_WIDTH / 2 - 235),
                          static_cast<int>(Game::WIN_HEIGHT / 4 + 140),
                          300,
                          300 };
  game->getTexture(objetoActual.tex)->render(objetoRect);

  SDL_Rect boardRect = { 100, 200, 440, 294 };
  game->getTexture(PELEASBOARD)->render(boardRect);

  SDL_Rect roundBoard = { 1550, 40, 300, 175 };
  game->getTexture(PELEASROUND)->render(roundBoard);

  SDL_Rect prizeBoard = { 1580, 670, 300, 400 };
  game->getTexture(PELEASLOCURAPRECIO)->render(prizeBoard);

  if (resultadoBox->isTextVisible()) {
    SDL_Rect resultBoard = { 700, 200, 400, 600 };
    game->getTexture(PELEASLOCURARESULTS)->render(resultBoard);
  }

  descripcionBox->render();
  rondaBox->render();
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
        if (rondasRestantesObjeto == 3)
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.15f;
        else if (rondasRestantesObjeto == 2)
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.07f;
        else
          desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.02f;

        std::normal_distribution<float> distRival(objetoActual.precioReal,
                                                  desviacion);
        nuevaRonda.intentoRival =
          std::clamp(static_cast<int>(distRival(generadorPrecios.gen)),
                     objetoActual.minRango,
                     objetoActual.maxRango);

        rondasActuales.push_back(nuevaRonda);
        calcularResultadoRonda();

        // Comprobamos si alguien adivinó el precio exacto
        if (nuevaRonda.intentoJugador == objetoActual.precioReal) {
          partidaTerminada = true;
          ganador = "¡GANASTE!";
          mostrarTextoResultado = false;
          currentState = State::FINAL_OBJETO;
          stateStartTime = currentTime;
          return;  // Salir para no seguir con el flujo normal
        }
        if (nuevaRonda.intentoRival == objetoActual.precioReal) {
          partidaTerminada = true;
          ganador = "¡PERDISTE!";
          mostrarTextoResultado = false;
          currentState = State::FINAL_OBJETO;
          stateStartTime = currentTime;
          return;
        }

        currentState = State::MOSTRAR_RESULTADO_RONDA;
        mostrarTextoResultado = false;  // Reiniciar el flag
        stateStartTime = currentTime;
      }
      break;

    case State::MOSTRAR_RESULTADO_RONDA:
      if (!mostrarTextoResultado) {
        // Mostrar el mensaje inmediatamente al entrar en el estado
        auto& ronda = rondasActuales.back();
        std::stringstream resultado;
        resultado << "Tu: " << ronda.intentoJugador << "\n";
        resultado << "Rival: " << ronda.intentoRival << "\n";
        resultado << "Dif. Tú: " << ronda.diferenciaJugador << "\n";
        resultado << "Dif. Rival: " << ronda.diferenciaRival;

        std::stringstream resultado;
        resultado << "Ronda " << (3 - rondasRestantesObjeto + 1) << "/3\n";
        resultado << "Tú: " << rondasActuales.back().intentoJugador << "\n";
        resultado << "Rival: " << rondasActuales.back().intentoRival << "\n";
        resultado << "Diferencia: " << rondasActuales.back().diferenciaJugador;

        resultadoBox->resetHistory();
        resultadoBox->showMessage(resultado.str(), true);
        mostrarTextoResultado = true;
        stateStartTime = currentTime;
      }
      else if (currentTime - stateStartTime >= TIEMPO_RESULTADO_MOSTRADO) {
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
        rondaBox->resetHistory();
        std::string rondaMsg =
          "Ronda " + std::to_string(4 - rondasRestantesObjeto) + "/3";
        rondaBox->showMessage(rondaMsg, true);
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
        if (!partidaTerminada) {
          if (++rondasTotales < 3) {
            generarNuevoObjeto();
            currentState = State::PRESENTACION;
          }
          else {
            currentState = State::FINAL_JUEGO;
          }
        }
        else {
          currentState = State::FINAL_JUEGO;  // Si alguien ganó, termina juego
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
  if (partidaTerminada) {
    // Ya hay ganador por adivinar el precio
    std::string resultadoFinal =
      "Precio real: " + std::to_string(objetoActual.precioReal) + "\n\n" +
      ganador;
    resultadoBox->showMessage(resultadoFinal, true);
    return;
  }

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
