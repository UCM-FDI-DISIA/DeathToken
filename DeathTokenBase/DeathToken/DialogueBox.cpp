#include "dialogueBox.h"
#include "game.h"
#include <iostream>

#pragma region CONSTRUCTORS_DESTRUCTOR
/*****************************************************************/
/* Constructor por defecto: Inicializa todos los valores b�sicos */
/*****************************************************************/
DialogueBox::DialogueBox()
	: renderer(nullptr)      // Renderizador SDL (se asignar� despu�s)
	, font(nullptr)         // Fuente de texto (se asignar� despu�s)
	, history()             // Lista vac�a de di�logos hist�ricos
	, message("")           // Mensaje actual vac�o
	, visible(false)        // Inicialmente invisible
	, transparente(true)    // Fondo transparente por defecto
	, charIndex(0)          // �ndice para animaci�n de texto
	, currentDialogIndex(0) // Primer di�logo
	, scrollOffset(0)       // Sin desplazamiento
	, fast(false)           // Velocidad normal de texto
	, instantDisplay(false) // Mostrar progresivo (no instant�neo)
	, needsUpdate(false)    // No requiere actualizaci�n inicial
	, isScrolling(false)    // No hay scroll manual activo
	, nextState(false)      // No est� listo para siguiente estado
	, scrollingTime(0)      // Temporizador de scroll en 0
	, x(800)                // Posici�n X por defecto
	, y(200)                // Posici�n Y por defecto
	, h(DialogueBoxConstants::BOXHEIGHT)  // Altura est�ndar
	, w(DialogueBoxConstants::BOXWIDTH)   // Ancho est�ndar
	, autoDialog(true)      // Di�logo autom�tico activado
	, completedTextTime(0)  // Temporizador de texto completo en 0
{
	calculateTextMetrics(); // Calcula m�tricas de texto
}

/***********************************************************************/
/* Constructor parametrizado: Permite configuraci�n personalizada       */
/* Par�metros:                                                         */
/* - renderer: Puntero al renderizador SDL                             */
/* - font: Fuente de texto a usar                                      */
/* - posx, posy: Posici�n de la caja                                   */
/* - update: Si requiere actualizaciones continuas                     */
/* - transparente: Si el fondo es transparente                        */
/* - wi, he: Ancho y alto personalizados                              */
/***********************************************************************/
DialogueBox::DialogueBox(SDL_Renderer* renderer, TTF_Font* font, int posx, int posy,
	bool update, bool transparente, int wi, int he)
	: renderer(renderer)    // Asigna renderizador
	, font(font)            // Asigna fuente
	, visible(false)        // Inicialmente invisible
	, displayedText("")    // Texto mostrado vac�o
	, message("")          // Mensaje actual vac�o
	, charIndex(0)         // Comenzar desde primer car�cter
	, currentDialogIndex(0) // Primer di�logo
	, scrollOffset(0)       // Sin desplazamiento
	, instantDisplay(false) // Mostrar progresivo
	, fast(false)          // Velocidad normal
	, isScrolling(false)   // No hay scroll manual
	, nextState(false)     // No est� listo para siguiente estado
	, scrollingTime(0)     // Temporizador de scroll en 0
	, transparente(transparente) // Transparencia seg�n par�metro
	, needsUpdate(update)  // Actualizaci�n seg�n par�metro
	, x(posx)              // Posici�n X personalizada
	, y(posy)             // Posici�n Y personalizada
	, h(he)               // Altura personalizada
	, w(wi)               // Ancho personalizado
	, completedTextTime(0) // Temporizador en 0
	, autoDialog(true)    // Di�logo autom�tico activado
{
	calculateTextMetrics(); // Calcula m�tricas de texto
}

/******************************************/
/* Destructor: Limpia recursos asignados  */
/******************************************/
DialogueBox::~DialogueBox() {
	renderer = nullptr; // No libera (lo gestiona otro componente)
	font = nullptr;    // No libera (lo gestiona otro componente)
}
#pragma endregion

#pragma region TEXT_MANAGEMENT
/**************************************************************************************/
/* Calcula las m�tricas del texto para el formato									  */
/* Par�metros:																		  */
/* - fontSize: Tama�o de fuente para c�lculos (opcional)							  */
/* IMPORTANTE: fontSize DEBE DE SER EL TAMA�O DE FONT PARA QUE FUNCIONE CORRECTAMENTE */
/**************************************************************************************/
void DialogueBox::calculateTextMetrics(int fontSize) {
	// Margen a ambos lados del texto
	textWidth = w - 2 * DialogueBoxConstants::TEXT_MARGIN;
	// Caracteres por l�nea basado en ancho de fuente
	charsPerLine = static_cast<int>((textWidth / (fontSize * DialogueBoxConstants::CHAR_WIDTH_FACTOR)));
}

/*******************************************************************/
/* Guarda un mensaje en el historial caja de di�logo y se mostrar� */
/* cuando le toque actualizarse.								   */
/* Par�metros:                                                     */
/* - input_text: Texto a mostrar                                   */
/* - instantShow: Si true, muestra todo el texto inmediatamente y  */
/*   se saltar� todos los dialogos anteriores.					   */
/*******************************************************************/
void DialogueBox::showMessage(const std::string& input_text, bool instantShow) {
	if (!input_text.empty()) {
		history.push_back(input_text); // A�ade al historial de di�logos

		if (instantShow) {
			// Va directamente al �ltimo mensaje a�adido
			currentDialogIndex = (int)history.size() - 1;
		}

		message = history[currentDialogIndex]; // Establece mensaje actual

		if (!needsUpdate) {
			displayedText = message; // Muestra texto completo si no necesita actualizaci�n
		}
	}
	visible = true; // Hace visible la caja de di�logo
}

/*******************************************************************/
/* Reinicia completamente el historial de di�logos                 */
/*******************************************************************/
void DialogueBox::resetHistory() {
	message = "";           // Limpia mensaje actual
	displayedText = "";     // Limpia texto mostrado
	history.clear();        // Vac�a el historial
	visible = false;        // Oculta la caja
	scrollOffset = 0;       // Reinicia scroll
	charIndex = 0;          // Reinicia �ndice de caracteres
	currentDialogIndex = 0; // Vuelve al primer di�logo
}

/*******************************************************************/
/* Oculta la caja de di�logo                                      */
/*******************************************************************/
void DialogueBox::hideMessage() {
	visible = false;
}
#pragma endregion

#pragma region SCROLL_HANDLING
/*******************************************************************/
/* Maneja el desplazamiento del texto                              */
/* Par�metros:                                                     */
/* - deltaTime: Tiempo transcurrido desde �ltima actualizaci�n     */
/* - numLines: N�mero de l�neas de texto                           */
/*******************************************************************/
void DialogueBox::handleScroll(float deltaTime, int numLines) {
	// Si hay scroll manual activo
	if (isScrolling) {
		if (autoDialog) {
			scrollingTime += (int)deltaTime; // Actualiza temporizador
			// Pausa temporizador de di�logo autom�tico
			completedTextTime -= (int)deltaTime;
		}

		// Vuelve a scroll autom�tico despu�s de tiempo
		if (scrollingTime >= DialogueBoxConstants::SCROLL_TIMEOUT) {
			isScrolling = false;
		}
		return;
	}

	// Scroll autom�tico solo si el texto no cabe
	if (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR > h) {
		if (scrollOffset < (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) {
			// Calcula velocidad basada en modo r�pido/normal
			int scrollSpeed = DialogueBoxConstants::AUTO_SCROLL_BASE_SPEED;
			if (fast) {
				scrollSpeed += DialogueBoxConstants::AUTO_SCROLL_BASE_SPEED *
					DialogueBoxConstants::AUTO_SCROLL_FAST_FACTOR;
			}
			scrollOffset += scrollSpeed;
		}
	}
}
#pragma endregion

#pragma region UPDATE_LOGIC
/*******************************************************************/
/* Actualiza el estado del di�logo                                 */
/* Par�metros:                                                     */
/* - deltaTime: Tiempo transcurrido desde �ltima actualizaci�n    */
/*******************************************************************/
void DialogueBox::update(float deltaTime) {
	if (!visible || !needsUpdate) return;

	message = history[currentDialogIndex]; // Actualiza mensaje actual

	// Calcular n�mero de l�neas necesarias
	int numLines = (int)((displayedText.size() / charsPerLine) + 1);
	
	// Animaci�n de texto progresivo
	if (charIndex < message.size()) {
		if (fast) { // Modo r�pido (espacio pulsado)
			// Avanza varios caracteres a la vez
			for (int i = 0; i < DialogueBoxConstants::NORMAL_LETTER_DELAY /
				DialogueBoxConstants::FAST_LETTER_DELAY && charIndex < message.size(); i++) {
				displayedText += message[charIndex++];
			}
		}
		else { // Modo normal (un car�cter por actualizaci�n)
			displayedText += message[charIndex++];
		}
	}
	// Mostrar todo inmediatamente si se solicit�
	if (instantDisplay) {
		displayedText = message;
		// Ajusta scroll si hay overflow
		if (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR > h) {
			scrollOffset = (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h;
		}
		charIndex = (int)message.size(); // Marca como completo
	}
	

	// L�gica para di�logo autom�tico
	if (charIndex == message.size() && autoDialog) {
		// Calcula tiempo necesario antes de avanzar
		int requiredTime = DialogueBoxConstants::NEXT_DIALOGUE_DELAY;
		if (((numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) > 0) {
			requiredTime += ((numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) *
				DialogueBoxConstants::EXTRA_LINE_DELAY;
		}

		if (completedTextTime >= requiredTime) {
			completedTextTime = 0;
			// Si hay m�s di�logos, avanzar
			if (currentDialogIndex + 1 < history.size()) {
				currentDialogIndex++;
				charIndex = 0;
				displayedText = "";
				instantDisplay = false;
				scrollOffset = 0;
			}
			else { // Fin de di�logos
				nextState = true; // Avisa al sistema de juego
			}
		}
		else {
			completedTextTime += (int)deltaTime; // Incrementa temporizador
		}
	}

	// Control de scroll manual/autom�tico
	handleScroll(deltaTime, numLines);
}
#pragma endregion

#pragma region RENDERING
/*******************************************************************/
/* Renderiza la caja de di�logo y su contenido                     */
/*******************************************************************/
void DialogueBox::render() const {
	if (!visible) return;

	// Configura transparencia
	int transparent = transparente ? SDL_ALPHA_TRANSPARENT : 255;
	SDL_Color textColor = { 0, 0, 0, 255 }; // Color negro

	// Renderizar texto con ajuste de l�neas autom�tico
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(
		font, displayedText.c_str(), textColor, textWidth);

	// Debug: Verificar errores en la superficie
#ifdef _DEBUG
	if (!textSurface) {
		std::cerr << "Error al crear la superficie del texto: "
			<< TTF_GetError() << std::endl;
		return;
	}
#endif

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	// Debug: Verificar errores en la textura
#ifdef _DEBUG
	if (!textTexture) {
		SDL_FreeSurface(textSurface);
		std::cerr << "Error al crear la textura del texto: "
			<< SDL_GetError() << std::endl;
		return;
	}
#endif

	// Definir �reas de renderizado
	SDL_Rect dialogBox = { x, y, w, h }; // Rect�ngulo de la caja
	SDL_Rect textRect = {
		dialogBox.x + DialogueBoxConstants::TEXT_MARGIN,
		dialogBox.y + DialogueBoxConstants::TEXT_MARGIN - scrollOffset,
		textSurface->w,
		textSurface->h
	};

	// Renderizar fondo
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, transparent);
	SDL_RenderFillRect(renderer, &dialogBox);

	// Renderizar texto con recorte (clipping)
	SDL_RenderSetClipRect(renderer, &dialogBox);
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	SDL_RenderSetClipRect(renderer, nullptr);

	// Liberar recursos
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}
#pragma endregion

#pragma region INPUT_HANDLING
/*******************************************************************/
/* Maneja eventos de entrada                                       */
/* Par�metros:                                                     */
/* - event: Evento SDL a procesar                                  */
/*******************************************************************/
void DialogueBox::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		// Tecla ESPACIO: Acelera animaci�n de texto
		if (event.key.keysym.sym == SDLK_SPACE) {
			fast = true;
		}
		// Tecla ENTER
		if (event.key.keysym.sym == SDLK_RETURN) {
			if (charIndex < message.size()) {
				// Muestra todo el texto inmediatamente
				instantDisplay = true;
			}
			else {
				// Avanza al siguiente di�logo
				if (currentDialogIndex + 1 < history.size()) {
					currentDialogIndex++;
					displayedText = "";
					charIndex = 0;
					instantDisplay = false;
					scrollOffset = 0;
					completedTextTime = 0;
				}
				else {
					// Indica que se completaron todos los di�logos
					nextState = true;
				}
			}
		}
	}

	// Al soltar ESPACIO: vuelve a velocidad normal
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			fast = false;
		}
	}

	// Rueda del rat�n: scroll manual
	if (event.type == SDL_MOUSEWHEEL) {
		int numLines = (int)((displayedText.size() / charsPerLine) + 1);

		// Solo si hay overflow de texto
		if (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR > h) {
			isScrolling = true;
			scrollingTime = 0;
			// Ajusta desplazamiento basado en movimiento de rueda
			scrollOffset -= event.wheel.y * DialogueBoxConstants::MANUAL_SCROLL_SPEED;

			// Limita scroll a los bordes del texto
			int maxOffset = numLines * static_cast<int>(Game::FONTSMALLSIZE *
				DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h;
			scrollOffset = std::max(0, std::min(scrollOffset, maxOffset));
		}
	}
}
#pragma endregion