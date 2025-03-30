#include "DialogueBox.h"
#include "Game.h"
#include <iostream>

const int NEXTDIALOG = 6000;
const int NEXTDIALOGSPARETIME = 2000;
const int SCROLLINGTIME = 3000;
const int SCROLL_SPEED = 20;
const float AUTO_SCROLL_SPEED = 1.2f;
const float AUTO_SCROLL_FAST = 4 + 1.0f / 3.0f;



void DialogueBox::showMessage(const std::string& in) {
	if (!in.empty()) {
		history.push_back(in);
		if (!needsUpdate) {
			message = history[currentDialogIndex];
			displayedText = message;
		}
	}
	visible = true;
}

void DialogueBox::ResetHistory() {
	message = "";
	displayedText = "";
	history.clear();
	visible = false;
	scrollOffset = 0;
	charIndex = 0;
	currentDialogIndex = 0;

}

void DialogueBox::hideMessage() {
	visible = false;
}

void DialogueBox::update(float deltaTime) {
	if (!visible || !needsUpdate) return;

	message = history[currentDialogIndex];

	// Calcular el número de líneas necesarias
	int numLines = (displayedText.size() / charsPerLine) + 1;

	if (!instantDisplay && charIndex < message.size()) {
		if (fast) {
			for (int i = 0; i < letterdelay / fastLetter && charIndex < message.size(); i++)
			{
				displayedText += message[charIndex++];
			}
		}
		else {
			displayedText += message[charIndex++];
		}
	}
	else if (instantDisplay) {
		displayedText = message;
		scrollOffset = (numLines * lineHeight) - h;
		charIndex = message.size();
	}

	if (charIndex == message.size() && autoDialog) {
		if (completedTextTime >= NEXTDIALOG + (((numLines * lineHeight) - h) > 0? (numLines * lineHeight) - h : 0) * NEXTDIALOGSPARETIME) {
			completedTextTime = 0;
			if (currentDialogIndex + 1 < history.size()) {
				currentDialogIndex++;
				displayedText = "";
				charIndex = 0;
				instantDisplay = false;
				scrollOffset = 0;
			}
			else {
				visible = false;
			}
		}
		else {
			completedTextTime += deltaTime;
		}
	}

	if (isScrolling) {

		if (autoDialog) {
			scrollingTime += deltaTime;
			completedTextTime -= deltaTime;
		}

		if (scrollingTime >= SCROLLINGTIME) {
			isScrolling = false;
		}

		return;
	}

	// Si la altura total del texto excede la caja de diálogo
	if (numLines * lineHeight > h) {
		// Desplazamos hacia abajo si el texto excede la caja
		if (scrollOffset < (numLines * lineHeight) - h) {
			scrollOffset += AUTO_SCROLL_SPEED + AUTO_SCROLL_SPEED * fast * AUTO_SCROLL_FAST;
		}
	}


}

void DialogueBox::render() const {
	if (!visible) return;
	int transparent = transparente ? SDL_ALPHA_TRANSPARENT : 255;

	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, displayedText.c_str(), textColor, textWidth);
	if (!textSurface) {
		std::cerr << "Error al crear la superficie del texto: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture) {
		SDL_FreeSurface(textSurface);
		std::cerr << "Error al crear la textura del texto: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_Rect dialogBox = { x, y, w, h };
	SDL_Rect textRect = { dialogBox.x + MARGIN, dialogBox.y + MARGIN - scrollOffset, textSurface->w, textSurface->h };

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, transparent);
	SDL_RenderFillRect(renderer, &dialogBox);

	SDL_RenderSetClipRect(renderer, &dialogBox);
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	SDL_RenderSetClipRect(renderer, nullptr);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void DialogueBox::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			fast = true;
		}
		if (event.key.keysym.sym == SDLK_RETURN) {
			if (charIndex < message.size()) {
				instantDisplay = true;
			}
			else {
				if (currentDialogIndex + 1 < history.size()) {
					currentDialogIndex++;
					displayedText = "";
					charIndex = 0;
					instantDisplay = false;
					scrollOffset = 0;
					completedTextTime = 0;
				}
				else {
					visible = false;
				}
			}
		}
	}
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			fast = false;
		}
	}
	if (event.type == SDL_MOUSEWHEEL) {

		// Calcular el número de líneas necesarias
		int numLines = (displayedText.size() / charsPerLine) + 1;

		// Permitir que el jugador haga scroll solo si hay más texto
		if (numLines * lineHeight > h) {

			isScrolling = true;
			scrollingTime = 0;
			scrollOffset -= event.wheel.y * SCROLL_SPEED;

			// Evitar que se mueva hacia arriba más allá del inicio del texto
			if (scrollOffset < 0) {
				scrollOffset = 0;
			}

			// Evitar que se mueva más allá del final del texto
			else if (scrollOffset > numLines * lineHeight - h) {
				scrollOffset = numLines * lineHeight - h;
			}
		}
	}
}
