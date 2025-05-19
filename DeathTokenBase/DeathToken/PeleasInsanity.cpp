#include "Award.h"
#include "peleasInsanity.h"
#include "SoundManager.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>

PeleasInsanity::PeleasInsanity(Game* game)
	: GameState(game)
	, currentState(State::PRESENTACION)
	, generadorPrecios(game->getGen())
	, mostrarTextoResultado(false)
	, bet(new HUDBet(this, false))
	, inputJugador(new InputBox(game->getRenderer(),
		game->getTypo(FIGHTS_BIG),
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
		1000,
		705,
		true,
		true,
		300,
		175))
	, resultadoBox(new DialogueBox(game->getRenderer(),
		game->getTypo(FIGHTS_SMALL),
		565,
		375,
		true,
		true,
		275,
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
std::string generarPista(int diferencia)
{
	if (diferencia > 100)
		return "Muy lejos";
	else if (diferencia > 50)
		return "Lejos";
	else if (diferencia > 20)
		return "Cerca";
	return "Muy cerca";
}

PeleasInsanity::~PeleasInsanity()
{
	HUDManager::popGame();
	delete inputJugador;
	delete descripcionBox;
	delete rondaBox;
	delete resultadoBox;
}
void PeleasInsanity::generarNuevoObjeto()
{
#ifdef _DEBUG
	std::cout << "\n=== GENERANDO NUEVO OBJETO ===" << std::endl;
#endif  // _DEBUG

	resetearCajasDialogo();
	ui->Show();
	empezarPartida = false;
	objetoActual = generadorPrecios.generarObjeto();
	partidaTerminada = false;  
	ganador = "";              
	objetoTerminado = false;
	if (objetoActual.minRango >= objetoActual.maxRango) {
		objetoActual.maxRango = objetoActual.minRango + 1;
#ifdef _DEBUG
		std::cerr << "Error: Rango inválido. Corregido a [" << objetoActual.minRango
			<< "-" << objetoActual.maxRango << "]" << std::endl;
#endif  //_DEBUG
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
							315 };
	game->getTexture(objetoActual.tex)->render(objetoRect);

	SDL_Rect boardRect = { -30, 400, 540, 294 };
	game->getTexture(PELEASBOARD)->render(boardRect);

	SDL_Rect roundBoard = { 950, 650, 300, 175 };
	game->getTexture(PELEASROUND)->render(roundBoard);

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
		resultadoBox->hideMessage();
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
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.5f;  
			else if (rondasRestantesObjeto == 2)
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.3f; 
			else
				desviacion = (objetoActual.maxRango - objetoActual.minRango) * 0.2f; 

			std::normal_distribution<float> distRival(
				static_cast<float>(objetoActual.precioReal), desviacion);
			nuevaRonda.intentoRival =
				std::clamp(static_cast<int>(distRival(generadorPrecios.gen)),
					objetoActual.minRango,
					objetoActual.maxRango);

			rondasActuales.push_back(nuevaRonda);
			calcularResultadoRonda();

			auto& ronda = rondasActuales.back();
			if (ronda.diferenciaJugador == 0 || ronda.diferenciaRival == 0) {
				partidaTerminada = true;
				ganador = (ronda.diferenciaJugador == 0) ? "Tú" : "Rival";

				if (ganador == "Tú") {
					game->push(new Award(game, this, objetoActual.precioReal, static_cast<long>(objetoActual.precioReal * 5), true));
				}
				else {
					PlayerEconomy::subtractBlueSouls(objetoActual.precioReal);
					PlayerEconomy::subtractRedSouls(2);
				}
				bet->update();
				bet->refresh();
				objetoTerminado = true;
				currentState = State::FINAL_OBJETO;
				stateStartTime = currentTime;
			}
			else {
				currentState = State::MOSTRAR_RESULTADO_RONDA;
				mostrarTextoResultado = false;
				stateStartTime = currentTime;
			}
		}
		break;

	case State::MOSTRAR_RESULTADO_RONDA:
		if (!mostrarTextoResultado) {
			// Mostrar el mensaje inmediatamente al entrar en el estado
			auto& ronda = rondasActuales.back();
			std::stringstream resultado;
			resultado << "Tu pista: " << generarPista(ronda.diferenciaJugador)
				<< "\n" << "\n" << "\n";
			resultado << "Pista rival: " << generarPista(ronda.diferenciaRival)
				<< "\n";

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
		if (!resultadoMostrado) {
			determinarGanadorObjeto();
			resultadoMostrado = true;
			stateStartTime = currentTime;
		}
		else {
			if (currentTime - stateStartTime >= TIEMPO_RESULTADO) {  // 4 segundos
				resultadoMostrado = false;

				// Reiniciar contadores
				rondasTotales = 0;  // Añade esta línea para reiniciar el contador
				generarNuevoObjeto();
				currentState = State::PRESENTACION;
			}
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

void PeleasInsanity::determinarGanadorObjeto() {
	std::stringstream ss;
	ss << "Precio real: " << objetoActual.precioReal << "\n\n";

	if (ganador.empty()) {  // Solo si no hubo acierto exacto
		int totalJugador = std::accumulate(
			rondasActuales.begin(), rondasActuales.end(), 0,
			[](int suma, const Ronda& r) { return suma + r.diferenciaJugador; }
		);
		int totalRival = std::accumulate(
			rondasActuales.begin(), rondasActuales.end(), 0,
			[](int suma, const Ronda& r) { return suma + r.diferenciaRival; }
		);

		bool jugadorGana = (totalJugador < totalRival);
		ganador = jugadorGana ? "Tú" : "Rival";

		ss << "Total Tú: " << totalJugador << "\n"
			<< "Total Rival: " << totalRival << "\n\n"
			<< (jugadorGana ? "¡GANASTE!" : "¡PERDISTE!");

		// Manejar economía
		if (!jugadorGana) {
			PlayerEconomy::subtractBlueSouls(objetoActual.precioReal);
			PlayerEconomy::subtractRedSouls(1);
		}
		else {
			game->push(new Award(game, this, objetoActual.precioReal, static_cast<long>(objetoActual.precioReal * 2), true));
		}
	}
	else {
		ss << (ganador == "Tú" ? "¡LO HAS ACERTADO!" : "El rival ha acertado.");
	}

	ss << "\n\nGanador: " << ganador;
	resultadoBox->resetHistory();
	resultadoBox->showMessage(ss.str(), true);
	bet->update();
	bet->refresh();
	objetoTerminado = true;  // Marcar objeto como completado
}