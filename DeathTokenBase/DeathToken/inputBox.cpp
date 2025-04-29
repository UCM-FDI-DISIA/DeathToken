#include "inputBox.h"
#include <algorithm> // Para std::ranges::copy
#include <cctype>    // Para std::isdigit
#include <ranges>    // Para std::ranges y views::filter
#include <SDL_ttf.h> // Para trabajar con fuentes TTF
#include <string>    // Para std::string y std::string_view

#pragma region Constructor

/*****************************************************************/
/* Constructor: Inicializa la caja de entrada de usuario         */
/*****************************************************************/
InputBox::InputBox(SDL_Renderer* renderer, TTF_Font* font, int posx, int posy,
	bool update, bool transparente, int wi, int he)
	: DialogueBox(renderer, font, posx, posy, update, transparente, wi, he),
	userInput(""),
	isActive(false),
	cursorColor({ 0, 0, 0, 255 }), // Negro por defecto
	cursorVisible(true),
	maxLength(50), // Longitud máxima por defecto
	lastCursorBlink(0),
	cursorHeight(static_cast<int>(TTF_FontHeight(font) * 0.8)) // Cacheamos la altura del cursor
{
	DialogueBox::instantDisplay = true; // Mostrar texto instantáneamente
	DialogueBox::autoDialog = false;    // Desactivar diálogo automático
}

#pragma endregion

#pragma region Configuración

/*****************************************************************/
/* Activa/desactiva la caja para recibir entrada                 */
/*****************************************************************/
void InputBox::setActive(bool active) {
	isActive = active;
	if (active) {
		lastCursorBlink = SDL_GetTicks();
		cursorVisible = true;
	}
}

/*****************************************************************/
/* Establece la longitud máxima de entrada permitida             */
/*****************************************************************/
void InputBox::setMaxLength(unsigned int length) {
	maxLength = length;
}

/*****************************************************************/
/* Establece el color del cursor                                 */
/*****************************************************************/
void InputBox::setCursorColor(SDL_Color color) {
	cursorColor = color;
}

#pragma endregion

#pragma region Setters y Getters

/*****************************************************************/
/* Obtiene el texto ingresado por el usuario                     */
/*****************************************************************/
const std::string& InputBox::getUserInput() const {
	return userInput;
}

/*****************************************************************/
/* Limpia la entrada del usuario                                 */
/*****************************************************************/
void InputBox::clearInput() {
	userInput.clear();
	updateDisplayText();
}

#pragma endregion

#pragma region Actualizar texto

/*****************************************************************/
/* Actualiza el texto mostrado basado en la entrada del usuario  */
/*****************************************************************/
void InputBox::updateDisplayText() {
	showMessage(userInput, true); // Usamos showMessage para actualizar el display
}

/*****************************************************************/
/* Establece y muestra el mensaje en la caja                     */
/*****************************************************************/
void InputBox::showMessage(const std::string& input_text, bool instantShow) {
	if (instantShow) {
		message = input_text;
		displayedText = message;
	}
	visible = true;
}

#pragma endregion

#pragma region Eventos

/*****************************************************************/
/* Maneja eventos de entrada específicos para texto              */
/*****************************************************************/
void InputBox::handleEvent(const SDL_Event& event) {
	if (!isActive) return;

	if (event.type == SDL_KEYDOWN) {
		// Si presionamos BACKSPACE y el texto no está vacío, eliminamos el último carácter
		if (event.key.keysym.sym == SDLK_BACKSPACE && !userInput.empty()) {
			userInput.pop_back();
			updateDisplayText(); // Actualiza el texto mostrado
		}
		// Si presionamos ENTER, confirmamos la entrada
		else if (event.key.keysym.sym == SDLK_RETURN) {
			history.push_back(userInput); // Guardamos el input en el historial
			clearInput(); // Limpiamos la entrada
			setActive(false); // Desactivamos la caja de entrada
		}
	}
	else if (event.type == SDL_TEXTINPUT) {
		// Si el tamaño del texto es menor que el máximo, agregamos el texto ingresado
		if (userInput.length() < maxLength) {
			// Solo aceptamos números con std::ranges::filter
			std::ranges::copy(
				std::string_view(event.text.text) | std::ranges::views::filter([](char c) { return std::isdigit(c); }),
				std::back_inserter(userInput)
			);
			// Recortamos el texto si excede la longitud máxima
			if (userInput.length() > maxLength) userInput.resize(maxLength);
			updateDisplayText(); // Actualizamos la pantalla
		}
	}
}

#pragma endregion

#pragma region Update y Render

/*****************************************************************/
/* Actualiza el estado de la caja (cursor parpadeante)           */
/*****************************************************************/
void InputBox::update(float deltaTime) {
	if (isActive) {
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime - lastCursorBlink > 500) {
			cursorVisible = !cursorVisible; // Alterna entre visible e invisible
			lastCursorBlink = currentTime;  // Actualiza el tiempo del parpadeo
		}
	}

	// Manejamos el desplazamiento de texto si es necesario
	DialogueBox::handleScroll(deltaTime);
}

/*****************************************************************/
/* Renderiza la caja con el texto y el cursor                    */
/*****************************************************************/
void InputBox::render() const {
	// Si hay texto, renderizamos la caja
	if (!message.empty()) {
		DialogueBox::render();
	}

	// Si la caja está activa y el cursor es visible, lo renderizamos
	if (isActive && cursorVisible) {
		// Calculamos la posición horizontal del cursor
		int cursorX = x + DialogueBoxConstants::TEXT_MARGIN;
		int cursorY = y + DialogueBoxConstants::TEXT_MARGIN;
		if (!userInput.empty()) {
			int textWidth = 0;
			// Calculamos el ancho del texto para posicionar el cursor al final
			TTF_SizeText(font, userInput.c_str(), &textWidth, nullptr);
			cursorX += textWidth - (w - (2 * DialogueBoxConstants::TEXT_MARGIN) - TTF_FontHeight(font) * DialogueBoxConstants::NUM_WIDTH_FACTOR) * static_cast<int>(textWidth / (w - 2 * DialogueBoxConstants::TEXT_MARGIN));
			cursorY += (DialogueBoxConstants::TEXT_MARGIN + cursorHeight) * static_cast<int>(textWidth / (w - 2 * DialogueBoxConstants::TEXT_MARGIN));
		}

		// Creamos el rectángulo del cursor (línea vertical)
		SDL_Rect cursorRect = {
			cursorX,
			cursorY,
			2, // Ancho del cursor
			cursorHeight // Usamos la altura cacheada
		};

		// Establecemos el color del cursor
		SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, cursorColor.a);
		// Renderizamos el cursor
		SDL_RenderFillRect(renderer, &cursorRect);
	}
}

#pragma endregion
