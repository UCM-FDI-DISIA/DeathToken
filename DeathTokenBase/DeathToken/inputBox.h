#ifndef USER_INPUT_BOX_H
#define USER_INPUT_BOX_H

#include "dialogueBox.h"
#include <SDL.h>
#include <string>

class InputBox : public DialogueBox {
private:
	std::string userInput;          // Texto ingresado por el usuario
	bool isActive;                  // Si la caja está recibiendo entrada
	SDL_Color cursorColor;         // Color del cursor parpadeante
	Uint32 lastCursorBlink;         // Tiempo del último parpadeo del cursor
	bool cursorVisible;             // Si el cursor está visible actualmente
	unsigned maxLength;             // Longitud máxima de entrada permitida
	int cursorHeight;              // Altura del cursor
	bool numberInput;              // Si solo se permiten números

public:
	// Constructor
	InputBox(SDL_Renderer* renderer, TTF_Font* font, int posx, int posy,
		bool update = true, bool transparente = false, int wi = DialogueBoxConstants::BOXWIDTH,
		int he = DialogueBoxConstants::BOXHEIGHT);

	// Métodos públicos
	void setActive(bool active, bool onlyNumbers = false);
	inline bool getActive() const { return isActive; };
	void setMaxLength(unsigned length);
	const std::string& getUserInput() const;
	void clearInput();
	void updateDisplayText();

	// Métodos sobreescritos
	void handleEvent(const SDL_Event& event) override;
	void update(float deltaTime) override;
	void render() const override;
	void showMessage(const std::string& message, bool instantShow = true) override;

	void setCursorColor(SDL_Color color);
};

#endif // USER_INPUT_BOX_H