#include "PeleasInsanity.h"
#include <algorithm>
#include <iostream>
#include <sstream>

PeleasInsanity::PeleasInsanity(Game* game)
  : GameState(game)
  , currentState(State::PRESENTACION)
  , inputJugador(new InputBox(game->getRenderer(),
                              game->getTypo(FIGHTS_SMALL),
                              static_cast<int>(Game::WIN_WIDTH / 2 - 150),
                              static_cast<int>(3 * Game::WIN_HEIGHT / 4),
                              true,
                              true,
                              400,
                              180))
  , descripcionBox(new DialogueBox(game->getRenderer(),
                                   game->getTypo(FIGHTS_SMALL),
                                   170,
                                   275,
                                   true,
                                   true,
                                   275,
                                   200))
  , rondaBox(new DialogueBox(game->getRenderer(),  // Nueva caja de rondas
                             game->getTypo(FIGHTS_SMALL),
                             1605,
                             110,
                             true,
                             true,
                             300,
                             175))
  , resultadoBox(new DialogueBox(game->getRenderer(),
                                 game->getTypo(FIGHTS_SMALL),
                                 1605,
                                 275,
                                 true,
                                 true,
                                 300,
                                 400))
{
  generarNuevoObjeto();
  inputJugador->setMaxLength(4);
  addEventListener(inputJugador);
  addEventListener(descripcionBox);
  addEventListener(rondaBox);
  addEventListener(resultadoBox);
}

void PeleasInsanity::generarNuevoObjeto()
{
  std::cout << "\n=== GENERANDO NUEVO OBJETO ===" << std::endl;

  resetearCajasDialogo();
  objetoActual = generadorPrecios.generarObjeto();

  // Asegurar rango válido
  if (objetoActual.minRango >= objetoActual.maxRango) {
    objetoActual.maxRango = objetoActual.minRango + 1;
    std::cerr << "Error: Rango inválido. Corregido a [" << objetoActual.minRango
              << "-" << objetoActual.maxRango << "]" << std::endl;
  }

  rondasActuales.clear();
  rondasRestantesObjeto = 3;

  std::string descripcion = objetoActual.descripcionRango + "\n" +
                            objetoActual.descripcionModificador + "\n";

  // Mostrar en cajas separadas
  descripcionBox->showMessage(descripcion, true);
  resultadoBox->showMessage("Preparado para empezar", true);  // Mensaje inicial
  rondaBox->showMessage("Ronda 1/3", true);  // Nueva caja de rondas

  inputJugador->showMessage("");
}

void PeleasInsanity::resetearCajasDialogo()
{
  descripcionBox->resetHistory();
  rondaBox->resetHistory();
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
  SDL_Rect roundBoard = {
    static_cast<int>(1550), static_cast<int>(40), 300, 175
  };
  game->getTexture(PELEASROUND)->render(roundBoard);

  descripcionBox->render();
  rondaBox->render();  // Renderizar caja de rondas
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

  descripcionBox->update(deltaTime);
  rondaBox->update(deltaTime);
  resultadoBox->update(deltaTime);

  switch (currentState) {
    case State::PRESENTACION:
      if (currentTime - stateStartTime >= TIEMPO_PRESENTACION) {
        currentState = State::INPUT_JUGADOR;
        inputJugador->setActive(true);
        stateStartTime = currentTime;
      }
      break;

    case State::INPUT_JUGADOR:
      inputJugador->update(deltaTime);
      if (!inputJugador->getActive()) {
        Ronda nuevaRonda;
        try {
          nuevaRonda.intentoJugador = std::stoi(inputJugador->getMessage());
        }
        catch (...) {
          nuevaRonda.intentoJugador = 0;
        }
        // En el caso State::INPUT_JUGADOR

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
      if (currentTime - stateStartTime >= TIEMPO_COMPARACION) {
        calcularResultadoRonda();
        auto& ronda = rondasActuales.back();

        std::stringstream resultado;
        resultado << "Tu: " << ronda.intentoJugador << "\n";
        resultado << "Rival: " << ronda.intentoRival << "\n";
        resultado << "Dif. Tú: " << ronda.diferenciaJugador << "\n";
        resultado << "Dif. Rival: " << ronda.diferenciaRival;

        resultadoBox->showMessage(resultado.str(), true);

        if (--rondasRestantesObjeto > 0) {
          currentState = State::SIGUIENTE_RONDA;
        }
        else {
          currentState = State::FINAL_OBJETO;
        }
        stateStartTime = currentTime;

        // Actualizar caja de rondas
        std::string rondaMsg =
          "Ronda " + std::to_string(3 - rondasRestantesObjeto) + "/3";
        rondaBox->showMessage(rondaMsg, true);
      }
      break;

    case State::SIGUIENTE_RONDA:
      if (currentTime - stateStartTime >= TIEMPO_SIGUIENTE_RONDA) {
        prepararSiguienteRonda();
        currentState = State::INPUT_JUGADOR;
        stateStartTime = currentTime;
      }
      break;

    case State::FINAL_OBJETO:
      if (currentTime - stateStartTime >= TIEMPO_FINAL_OBJETO) {
        determinarGanadorObjeto();
        if (++rondasTotales < 3) {
          generarNuevoObjeto();
          currentState = State::PRESENTACION;
        }
        else {
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
  inputJugador->clearInput();
  inputJugador->setActive(true);
  resultadoBox->resetHistory();
}

void PeleasInsanity::determinarGanadorObjeto()
{
  int totalJugador = 0;
  int totalRival = 0;
  for (const auto& ronda : rondasActuales) {
    totalJugador += ronda.diferenciaJugador;
    totalRival += ronda.diferenciaRival;
  }

  std::string resultadoFinal =
    "Precio real: " + std::to_string(objetoActual.precioReal) +
    "\n\nDif. Total Tú: " + std::to_string(totalJugador) +
    "\nDif. Total Rival: " + std::to_string(totalRival) + "\n\n" +
    ((totalJugador < totalRival) ? "¡GANASTE!" : "¡PERDISTE!");

  resultadoBox->showMessage(resultadoFinal, true);
}