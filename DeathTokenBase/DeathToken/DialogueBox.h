#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include "Game.h"
#include "gameObject.h"
#include <deque>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class DialogueBox {

	const int BOXWIDTH = 500;
	const int BOXHEIGHT = 250;
	const int MARGIN = 10;
	// Definir la altura de línea según la fuente (puede variar)
	const int lineHeight = Game::FONTSMALLSIZE * 1.3f;  // Se recomienda usar 1.3 * tamaño de la fuente
	// Estimar el ancho promedio de un carácter
	const float charWidth = Game::FONTSMALLSIZE * 0.6f;  // Aproximadamente 14.4 px para fuente de 24px
	const int letterdelay = 30; // en milisegundos
	const int fastLetter = 5; // en milisegundos

public:
	DialogueBox()
		: renderer(nullptr)
		, font(nullptr)
		, history()
		, message("")
		, visible(false)
		, transparente(true)
		, charIndex(0)
		, currentDialogIndex(0)
		, scrollOffset(0)
		, fast(false)
		, instantDisplay(false)
		, needsUpdate(false)
		, isScrolling(false)
		, scrollingTime(0)
		, x(800)
		, y(200)
		, h(BOXHEIGHT)
		, w(BOXWIDTH)
		, textWidth(w - 2 * MARGIN)
		, charsPerLine(textWidth / charWidth)
	{
	}

	DialogueBox(SDL_Renderer* renderer, TTF_Font* font, int posx = 800, int posy = 200, bool update = false, bool transparente = true, int wi = 500, int he = 250)
		: renderer(renderer)
		, font(font)
		, visible(false)
		, displayedText("")
		, message("")
		, charIndex(0)
		, currentDialogIndex(0)
		, scrollOffset(0)
		, instantDisplay(false)
		, fast(false)
		, isScrolling(false)
		, scrollingTime(0)
		, transparente(transparente)
		, needsUpdate(update)
		, x(posx)
		, y(posy)
		, h(he)
		, w(wi)
	{
		textWidth = w - 2 * MARGIN;
		charsPerLine = textWidth / charWidth;
	}

	~DialogueBox() {
		renderer = nullptr;
		font = nullptr;
		history.clear();
		displayedText.clear();
		message.clear();
	};

	void showMessage(const std::string& message);
	void hideMessage();
	void ResetHistory();
	void render() const;
	void update(float deltaTime);
	void handleEvent(const SDL_Event& event);

	inline void SetPosition(int posx, int posy) {
		x = posx;
		y = posy;
	}

	inline void SetX(int posx) {
		x = posx;
	}

	inline void SetY(int posy) {
		y = posy;
	}
	inline void SetW(int wi) {
		w = wi;
	}

	inline void SetH(int he) {
		h = he;
	}

	inline void SetAuto(bool a) {
		autoDialog = a;
	}
	inline void InvertAuto() {
		autoDialog = !autoDialog;
	}

protected:
	// Basico
		// Render
		// Renderer de la clase game
	SDL_Renderer* renderer;

	// Configuraciones de la letra
	TTF_Font* font;

	// Es el texto que será mostrado en pantalla. 
	// Depende de si tiene escritura o no.
	// En caso de tener escritura se iran añadiendo caracteres con un delay de
	// letterDelay o en caso de ir rapido con la pulsación de espacio por el jugador
	// ira a letterdelay / fastLetter. En caso de que se pulse enter se escribira automaticamente el dialogo.
	// En caso de no tenerla será igual a message
	std::string displayedText;
	// Control de los mensajes
	std::deque<std::string> history;
	std::string message;

	// Posicion en pantalla (se usan pixeles)
	int x;
	int y;

	// Tamaño del cuadro de texto
	int h;
	int w;

	// Si debe de ser renderizado
	bool visible;

	// Si tiene un fondo
	bool transparente;

	// True si el jugador esta desplazando el texto visible para leer otra parte
	bool isScrolling;

	// Acumulador que cuenta cuanto tiempo a transcurrido desde la ultima vez que se
	// ha movido el texto. En caso de no haberse movido por 3000 ms (3 segundos) 
	// establece isScrolling a false.
	int scrollingTime;

	// Espacio extra sobre el que se renderiza con respecto a la altura inicial del texto.
	// Es decir si el texto es muy grande y no cabe en pantalla para verlo se incrementa 
	// esta variable y recortara el texto extra por arriba para poder leer lo de abajo.
	int scrollOffset;

	// Indice del ultimo dialgo renderizado dentro del historial
	int currentDialogIndex;

	int textWidth;  // Ancho disponible para el texto

	// Calcular cuántos caracteres caben en una línea
	int charsPerLine;


	// Escritura
		// Si true debe de actualizar con más caracteres el displayedText
	bool fast;
	// Si true muestra todo el texto inmediatamente
	bool instantDisplay;

	// Si true realizara la "animacion" de escritura y si correspondera calculará el momento del paso automatico entre dialogos.
	bool needsUpdate;

	// Indice del ultimo caracter escrito dentro de un message
	int charIndex;

	// Salto Automatico de dialogos
		// Acumulador que cuenta cuantos milisegundos pasan desde que el texto se ha terminado de leer.
		// Una vez llega a los 6000 ms salta al siguiente texto si esta activo el auto.
		// En caso de que el texto sea muy grande y no se haya cortado en varios mensajes se añaden 2000 ms
		// por linea extra.
	int completedTextTime = 0;

	// Si true salta al siguiente dialogo automatico cuando llega el momento. 
	// La condicion de salto es controlada por completedTextTime.
	bool autoDialog = true;
};
#endif // DIALOGUEBOX_H