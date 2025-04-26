#include "dialogueBox.h"
#include "game.h"
#include <iostream>

#pragma region CONSTRUCTORS_DESTRUCTOR
/*****************************************************************/
/* Constructor por defecto: Inicializa todos los valores básicos */
/*****************************************************************/
DialogueBox::DialogueBox()
	: renderer(nullptr)      // Renderizador SDL (se asignará después)
	, font(nullptr)         // Fuente de texto (se asignará después)
	, history()             // Lista vacía de diálogos históricos
	, message("")           // Mensaje actual vacío
	, visible(false)        // Inicialmente invisible
	, transparente(true)    // Fondo transparente por defecto
	, charIndex(0)          // Índice para animación de texto
	, currentDialogIndex(0) // Primer diálogo
	, scrollOffset(0)       // Sin desplazamiento
	, fast(false)           // Velocidad normal de texto
	, instantDisplay(false) // Mostrar progresivo (no instantáneo)
	, needsUpdate(false)    // No requiere actualización inicial
	, isScrolling(false)    // No hay scroll manual activo
	, nextState(false)      // No está listo para siguiente estado
	, scrollingTime(0)      // Temporizador de scroll en 0
	, x(800)                // Posición X por defecto
	, y(200)                // Posición Y por defecto
	, h(DialogueBoxConstants::BOXHEIGHT)  // Altura estándar
	, w(DialogueBoxConstants::BOXWIDTH)   // Ancho estándar
	, autoDialog(true)      // Diálogo automático activado
	, completedTextTime(0)  // Temporizador de texto completo en 0
{
	calculateTextMetrics(); // Calcula métricas de texto
}

/***********************************************************************/
/* Constructor parametrizado: Permite configuración personalizada       */
/* Parámetros:                                                         */
/* - renderer: Puntero al renderizador SDL                             */
/* - font: Fuente de texto a usar                                      */
/* - posx, posy: Posición de la caja                                   */
/* - update: Si requiere actualizaciones continuas                     */
/* - transparente: Si el fondo es transparente                        */
/* - wi, he: Ancho y alto personalizados                              */
/***********************************************************************/
DialogueBox::DialogueBox(SDL_Renderer* renderer, TTF_Font* font, int posx, int posy,
	bool update, bool transparente, int wi, int he)
	: renderer(renderer)    // Asigna renderizador
	, font(font)            // Asigna fuente
	, visible(false)        // Inicialmente invisible
	, displayedText("")    // Texto mostrado vacío
	, message("")          // Mensaje actual vacío
	, charIndex(0)         // Comenzar desde primer carácter
	, currentDialogIndex(0) // Primer diálogo
	, scrollOffset(0)       // Sin desplazamiento
	, instantDisplay(false) // Mostrar progresivo
	, fast(false)          // Velocidad normal
	, isScrolling(false)   // No hay scroll manual
	, nextState(false)     // No está listo para siguiente estado
	, scrollingTime(0)     // Temporizador de scroll en 0
	, transparente(transparente) // Transparencia según parámetro
	, needsUpdate(update)  // Actualización según parámetro
	, x(posx)              // Posición X personalizada
	, y(posy)             // Posición Y personalizada
	, h(he)               // Altura personalizada
	, w(wi)               // Ancho personalizado
	, completedTextTime(0) // Temporizador en 0
	, autoDialog(true)    // Diálogo automático activado
{
	calculateTextMetrics(); // Calcula métricas de texto
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
/* Calcula las métricas del texto para el formato									  */
/* Parámetros:																		  */
/* - fontSize: Tamaño de fuente para cálculos (opcional)							  */
/* IMPORTANTE: fontSize DEBE DE SER EL TAMAÑO DE FONT PARA QUE FUNCIONE CORRECTAMENTE */
/**************************************************************************************/
void DialogueBox::calculateTextMetrics(int fontSize) {
	// Margen a ambos lados del texto
	textWidth = w - 2 * DialogueBoxConstants::TEXT_MARGIN;
	// Caracteres por línea basado en ancho de fuente
	charsPerLine = static_cast<int>((textWidth / (fontSize * DialogueBoxConstants::CHAR_WIDTH_FACTOR)));
}

/*******************************************************************/
/* Guarda un mensaje en el historial caja de diálogo y se mostrará */
/* cuando le toque actualizarse.								   */
/* Parámetros:                                                     */
/* - input_text: Texto a mostrar                                   */
/* - instantShow: Si true, muestra todo el texto inmediatamente y  */
/*   se saltará todos los dialogos anteriores.					   */
/*******************************************************************/
void DialogueBox::showMessage(const std::string& input_text, bool instantShow) {
	if (!input_text.empty()) {
		history.push_back(input_text); // Añade al historial de diálogos

		if (instantShow) {
			// Va directamente al último mensaje añadido
			currentDialogIndex = (int)history.size() - 1;
		}

		message = history[currentDialogIndex]; // Establece mensaje actual

		if (!needsUpdate) {
			displayedText = message; // Muestra texto completo si no necesita actualización
		}
	}
	visible = true; // Hace visible la caja de diálogo
}

/*******************************************************************/
/* Reinicia completamente el historial de diálogos                 */
/*******************************************************************/
void DialogueBox::resetHistory() {
	message = "";           // Limpia mensaje actual
	displayedText = "";     // Limpia texto mostrado
	history.clear();        // Vacía el historial
	visible = false;        // Oculta la caja
	scrollOffset = 0;       // Reinicia scroll
	charIndex = 0;          // Reinicia índice de caracteres
	currentDialogIndex = 0; // Vuelve al primer diálogo
}

/*******************************************************************/
/* Oculta la caja de diálogo                                      */
/*******************************************************************/
void DialogueBox::hideMessage() {
	visible = false;
}
#pragma endregion

#pragma region SCROLL_HANDLING
/*******************************************************************/
/* Maneja el desplazamiento del texto                              */
/* Parámetros:                                                     */
/* - deltaTime: Tiempo transcurrido desde última actualización     */
/* - numLines: Número de líneas de texto                           */
/*******************************************************************/
void DialogueBox::handleScroll(float deltaTime) {

	int numLines = (int)((displayedText.size() / charsPerLine) + 1); // Líneas necesarias
	// Si hay scroll manual activo
	if (isScrolling) {
		if (autoDialog) {
			scrollingTime += (int)deltaTime; // Actualiza temporizador
			// Pausa temporizador de diálogo automático
			completedTextTime -= (int)deltaTime;
		}

		// Vuelve a scroll automático después de tiempo
		if (scrollingTime >= DialogueBoxConstants::SCROLL_TIMEOUT) {
			isScrolling = false;
		}
		return;
	}

	// Scroll automático solo si el texto no cabe
	if (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR > h) {
		if (scrollOffset < (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) {
			// Calcula velocidad basada en modo rápido/normal
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
/* Actualiza el estado del diálogo                                 */
/* Parámetros:                                                     */
/* - deltaTime: Tiempo transcurrido desde última actualización    */
/*******************************************************************/
void DialogueBox::update(float deltaTime) {
	if (!visible || !needsUpdate) return;

	message = history[currentDialogIndex]; // Actualiza mensaje actual

	// Calcular número de líneas necesarias
	int numLines = (int)((displayedText.size() / charsPerLine) + 1);
	
	// Animación de texto progresivo
	if (charIndex < message.size()) {
		if (fast) { // Modo rápido (espacio pulsado)
			// Avanza varios caracteres a la vez
			for (int i = 0; i < DialogueBoxConstants::NORMAL_LETTER_DELAY /
				DialogueBoxConstants::FAST_LETTER_DELAY && charIndex < message.size(); i++) {
				displayedText += message[charIndex++];
			}
		}
		else { // Modo normal (un carácter por actualización)
			displayedText += message[charIndex++];
		}
	}
	// Mostrar todo inmediatamente si se solicitó
	if (instantDisplay) {
		displayedText = message;
		// Ajusta scroll si hay overflow
		if (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR > h) {
			scrollOffset = (numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h;
		}
		charIndex = (int)message.size(); // Marca como completo
	}
	

	// Lógica para diálogo automático
	if (charIndex == message.size() && autoDialog) {
		// Calcula tiempo necesario antes de avanzar
		int requiredTime = DialogueBoxConstants::NEXT_DIALOGUE_DELAY;
		if (((numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) > 0) {
			requiredTime += ((numLines * DialogueBoxConstants::LINE_HEIGHT_FACTOR) - h) *
				DialogueBoxConstants::EXTRA_LINE_DELAY;
		}

		if (completedTextTime >= requiredTime) {
			completedTextTime = 0;
			// Si hay más diálogos, avanzar
			if (currentDialogIndex + 1 < history.size()) {
				currentDialogIndex++;
				charIndex = 0;
				displayedText = "";
				instantDisplay = false;
				scrollOffset = 0;
			}
			else { // Fin de diálogos
				nextState = true; // Avisa al sistema de juego
			}
		}
		else {
			completedTextTime += (int)deltaTime; // Incrementa temporizador
		}
	}

	// Control de scroll manual/automático
	handleScroll(deltaTime);
}
#pragma endregion

#pragma region RENDERING
/*******************************************************************/
/* Renderiza la caja de diálogo y su contenido                     */
/*******************************************************************/
void DialogueBox::render() const {
	if (!visible) return;

	// Configura transparencia
	int transparent = transparente ? SDL_ALPHA_TRANSPARENT : 255;
	SDL_Color textColor = { 0, 0, 0, 255 }; // Color negro

	// Renderizar texto con ajuste de líneas automático
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

	// Definir áreas de renderizado
	SDL_Rect dialogBox = { x, y, w, h }; // Rectángulo de la caja
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
/* Parámetros:                                                     */
/* - event: Evento SDL a procesar                                  */
/*******************************************************************/
void DialogueBox::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		// Tecla ESPACIO: Acelera animación de texto
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
				// Avanza al siguiente diálogo
				if (currentDialogIndex + 1 < history.size()) {
					currentDialogIndex++;
					displayedText = "";
					charIndex = 0;
					instantDisplay = false;
					scrollOffset = 0;
					completedTextTime = 0;
				}
				else {
					// Indica que se completaron todos los diálogos
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

	// Rueda del ratón: scroll manual
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