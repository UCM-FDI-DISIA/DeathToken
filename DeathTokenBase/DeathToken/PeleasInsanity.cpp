#include "peleasInsanity.h"
#include "SoundManager.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

PeleasInsanity::PeleasInsanity(Game* game)
	: GameState(game)
	, currentState(State::PRESENTACION)
	, mostrarTextoResultado(false)
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
		50,
		495,
		true,
		true,
		390,
		275))
	, rondaBox(new DialogueBox(game->getRenderer(),
		game->getTypo(FIGHTS_SMALL),
		1300,
		105,
		true,
		true,
		300,
		175))
	, resultadoBox(new DialogueBox(game->getRenderer(),
		game->getTypo(FIGHTS_SMALL),
		590,
		475,
		true,
		true,
		400,
		375))
	, partidaTerminada(false)
	, ganador("")
	, ui(new UIPeleasInsanity(game, this))
	, empezarPartida(false)
{
	auto& soundManager = SoundManager::obtenerInstancia();
	soundManager.reproducirMusica("PeleasDT");
	generarNuevoObjeto();
	inputJugador->setMaxLength(4);
	addEventListener(inputJugador);
	addEventListener(descripcionBox);
	addEventListener(rondaBox);
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

#ifdef _DEBUG
	std::cout << "\n=== GENERANDO NUEVO OBJETO ===" << std::endl;
#endif // _DEBUG

	resetearCajasDialogo();
	ui->Show();
	empezarPartida = false;
	objetoActual = generadorPrecios.generarObjeto();

	if (objetoActual.minRango >= objetoActual.maxRango) {
		objetoActual.maxRango = objetoActual.minRango + 1;
#ifdef _DEBUG
		std::cerr << "Error: Rango inválido. Corregido a [" << objetoActual.minRango
			<< "-" << objetoActual.maxRango << "]" << std::endl;
#endif //_DEBUG
	}

	rondasActuales.clear();
	rondasRestantesObjeto = 3;
	partidaTerminada = false;
	ganador = "";

	std::string descripcion = "[Categoría] " + objetoActual.descripcionRango +
		"\n[Estado] " + objetoActual.descripcionModificador;
	descripcionBox->showMessage(descripcion, true);
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

	SDL_Rect objetoRect = { static_cast<int>(Game::WIN_WIDTH / 2 - 210),
							static_cast<int>(Game::WIN_HEIGHT / 4 + 40),
							300,
							300 };
	game->getTexture(objetoActual.tex)->render(objetoRect);

	SDL_Rect boardRect = { -30, 400, 540, 294 };
	game->getTexture(PELEASBOARD)->render(boardRect);

	SDL_Rect roundBoard = { 1250, 40, 300, 175 };
	game->getTexture(PELEASROUND)->render(roundBoard);

	SDL_Rect prizeBoard = { 1200, 400, 300, 400 };
	game->getTexture(PELEASLOCURAPRECIO)->render(prizeBoard);

	if (resultadoBox->isTextVisible()) {
		SDL_Rect resultBoard = { 500, 200, 400, 600 };
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

	descripcionBox->update(deltaTime);
	rondaBox->update(deltaTime);
	resultadoBox->update(deltaTime);

	switch (currentState) {
	case State::PRESENTACION:
		rondaBox->hideMessage();
		if (empezarPartida) {
			rondaBox->showMessage("Ronda 1/3", true);
			currentState = State::INPUT_JUGADOR;
			ui->Hide();
			inputJugador->setActive(true, true);
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

			float desviacion;
			if (rondasRestantesObjeto == 3)
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.15f;
			else if (rondasRestantesObjeto == 2)
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.07f;
			else
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.02f;

			std::normal_distribution<float> distRival(static_cast<float>(objetoActual.precioReal),
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

			resultadoBox->showMessage(resultado.str(), true);
			mostrarTextoResultado = true;
			stateStartTime = currentTime;
		}
		else if (currentTime - stateStartTime >= TIEMPO_RESULTADO_MOSTRADO) {
			if (--rondasRestantesObjeto > 0) {
				currentState = State::SIGUIENTE_RONDA;
			}
			else {
				currentState = State::FINAL_OBJETO;
			}
			stateStartTime = currentTime;
		}
		break;

	case State::SIGUIENTE_RONDA:
		if (currentTime - stateStartTime >= TIEMPO_SIGUIENTE_RONDA) {
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
		if (currentTime - stateStartTime >= TIEMPO_FINAL_OBJETO) {
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
	inputJugador->clearInput();
	inputJugador->setActive(true, true);
	resultadoBox->resetHistory();
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

	std::string resultadoFinal =
		"Precio real: " + std::to_string(objetoActual.precioReal) +
		"\n\nDif. Total Tú: " + std::to_string(totalJugador) +
		"\nDif. Total Rival: " + std::to_string(totalRival) + "\n\n" +
		((totalJugador < totalRival) ? "¡GANASTE!" : "¡PERDISTE!");

	resultadoBox->showMessage(resultadoFinal, true);
}
