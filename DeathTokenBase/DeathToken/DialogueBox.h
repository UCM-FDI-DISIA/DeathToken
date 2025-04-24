#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#pragma region INCLUDES
#include "game.h"           // Configuraciones del juego
#include "gameObject.h"     // Clase base para objetos del juego
#include <deque>            // Contenedor para historial de diálogos
#include <memory>           // Para punteros inteligentes (no usado directamente aquí)
#include <SDL.h>            // Librería gráfica principal
#include <SDL_ttf.h>        // Manejo de fuentes de texto
#include <string>           // Para manejo de strings
#pragma endregion

#pragma region CONSTANTS
// Espacio de nombres para constantes de la caja de diálogo
namespace DialogueBoxConstants {
	// Constantes de temporización
	const int NEXT_DIALOGUE_DELAY = 6000;       // 6 segundos para diálogo automático
	const int EXTRA_LINE_DELAY = 2000;          // +2 segundos por línea extra
	const int SCROLL_TIMEOUT = 3000;            // 3 segundos para resetear scroll
	const int MANUAL_SCROLL_SPEED = 20;         // Velocidad scroll manual (px)
	const float AUTO_SCROLL_BASE_SPEED = 1.2f;  // Velocidad base scroll automático
	const float AUTO_SCROLL_FAST_FACTOR = 4 + (1.0f / 3.0f); // Factor velocidad rápida

	// Dimensiones por defecto
	const int BOXWIDTH = 500;       // Ancho predeterminado
	const int BOXHEIGHT = 250;      // Alto predeterminado
	const int TEXT_MARGIN = 10;     // Margen interior del texto

	// Configuración de texto
	const float LINE_HEIGHT_FACTOR = 1.3f;  // Altura de línea (1.3 * tamaño fuente)
	const float CHAR_WIDTH_FACTOR = 0.6f;   // Ancho estimado por carácter

	// Temporizadores de escritura
	const int NORMAL_LETTER_DELAY = 30;     // Retardo entre letras (normal)
	const int FAST_LETTER_DELAY = 5;        // Retardo entre letras (rápido)
}
#pragma endregion

#pragma region CLASS_DEFINITION
/*****************************************************************/
/* Clase DialogueBox: Maneja la visualización de texto en el juego*/
/* Hereda de EventHandler para gestionar eventos de entrada       */
/*****************************************************************/
class DialogueBox : EventHandler {
public:
#pragma region CONSTRUCTORS_DESTRUCTOR
	/// Constructor por defecto
	DialogueBox();

	/**
	 * Constructor parametrizado
	 * @param renderer Renderizador SDL
	 * @param font Fuente de texto a usar
	 * @param posx Posición X (opcional, default: 800)
	 * @param posy Posición Y (opcional, default: 200)
	 * @param update Si necesita actualización (opcional, default: false)
	 * @param transparente Si es transparente (opcional, default: true)
	 * @param wi Ancho (opcional, default: 500)
	 * @param he Alto (opcional, default: 250)
	 */
	DialogueBox(SDL_Renderer* renderer, TTF_Font* font, int posx = 800, int posy = 200,
		bool update = false, bool transparente = true, int wi = 500, int he = 250);

	/// Destructor
	~DialogueBox();
#pragma endregion

#pragma region PUBLIC_METHODS
	/**
	 * Muestra un mensaje en la caja
	 * @param message Texto a mostrar
	 * @param instantShow Mostrar inmediatamente (opcional, default: true)
	 */
	void showMessage(const std::string& message, bool instantShow = false);

	/// Oculta la caja de diálogo
	void hideMessage();

	/// Limpia el historial de mensajes
	void resetHistory();

	/// Renderiza la caja
	void render() const;

	/**
	 * Actualiza el estado de la caja
	 * @param deltaTime Tiempo desde último frame (ms)
	 */
	void update(float deltaTime);

	/// Maneja eventos de entrada (override de EventHandler)
	void handleEvent(const SDL_Event& event) override;
#pragma endregion

#pragma region GETTERS_SETTERS
	// Indica si debe avanzar al siguiente estado
	inline bool shouldAdvanceState() const { return nextState; }

	// Establece posición (x,y)
	inline void setPosition(int posx, int posy) { x = posx; y = posy; }

	// Establece posición X
	inline void setX(int posx) { x = posx; }

	// Establece posición Y
	inline void setY(int posy) { y = posy; }

	// Establece ancho y recalcula métricas
	inline void setWidth(int wi) { w = wi; calculateTextMetrics(); }

	// Establece alto
	inline void setHeight(int he) { h = he; }

	// Activa/desactiva diálogo automático
	inline void setAuto(bool a) { autoDialog = a; }

	// Alterna diálogo automático
	inline void toggleAuto() { autoDialog = !autoDialog; }

	// Resetea flag de estado (para nuevo texto)
	inline void resetDialogStateFlag() { nextState = false; }
#pragma endregion

protected:
#pragma region PROTECTED_METHODS
	/**
	 * Calcula métricas del texto
	 * @param fontSize Tamaño de fuente (opcional, default: Game::FONTSMALLSIZE)
	 */
	void calculateTextMetrics(int fontSize = Game::FONTSMALLSIZE);

	/**
	 * Maneja el desplazamiento del texto
	 * @param deltaTime Tiempo desde último frame
	 * @param numLines Número de líneas de texto
	 */
	void handleScroll(float deltaTime, int numLines);
#pragma endregion

#pragma region MEMBER_VARIABLES
	// Elementos básicos
	SDL_Renderer* renderer;  // Renderer SDL
	TTF_Font* font;          // Fuente de texto

	// Control de texto
	std::string displayedText;   // Texto actual mostrado
	std::deque<std::string> history; // Historial de diálogos (cola)
	std::string message;         // Mensaje actual completo

	// Posición y dimensiones
	int x, y;   // Posición (coordenadas)
	int h, w;   // Dimensiones (alto, ancho)

	// Estados y flags
	bool visible;        // Visibilidad
	bool transparente;   // Transparencia
	bool isScrolling;    // Scroll activo
	bool fast;           // Modo rápido
	bool instantDisplay; // Mostrar todo
	bool needsUpdate;    // Si el texto mostrado usará el update para escrito caracter a carácter o saldrá inmediatamente del update
	bool nextState;      // Fin de diálogos
	bool autoDialog;     // Avance automático

	// Temporizadores y contadores
	int scrollingTime;       // Tiempo scroll
	int scrollOffset;        // Desplazamiento
	int currentDialogIndex;  // Índice diálogo
	int charIndex;          // Índice carácter
	int completedTextTime;  // Tiempo texto completo
	int textWidth;         // Ancho texto disponible
	int charsPerLine;     // Caracteres por línea
#pragma endregion
};
#pragma endregion

#endif // DIALOGUEBOX_H