#include "DialogueBox.h"
#include <iostream>
#include "Game.h"

const int MARGIN = 100;
const int NEXTDIALOG = 3000;
const int SCROLL_SPEED = 20;
const int AUTO_SCROLL_SPEED = 2;

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
    this->message = "";
    history.clear();
    visible = true;
    scrollOffset = 0;
}

void DialogueBox::hideMessage() {
    visible = false;
}

void DialogueBox::update(float deltaTime) {
    if (!visible || !needsUpdate) return;

    message = history[currentDialogIndex];

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
        charIndex = message.size();
    }

    // Calculamos el n�mero de l�neas de texto
    int lineHeight = 24;  // Altura de cada l�nea en p�xeles
    int textWidth = w - MARGIN / 5;  // Ancho disponible para el texto
    int numLines = (displayedText.size() * lineHeight / textWidth) + 1;  // N�mero de l�neas de texto necesarias

    // Si la altura total del texto excede la altura de la caja
    if (numLines * lineHeight > h) {
        // Desplazamos hacia abajo si el texto excede la caja de di�logo
        if (scrollOffset < numLines * lineHeight - h) {
            scrollOffset += AUTO_SCROLL_SPEED;  // Sumamos para mover hacia abajo
        }
    }

    if (charIndex == message.size()) {
        if (completedTextTime >= NEXTDIALOG) {
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
}

void DialogueBox::render() const {
    if (!visible) return;
    int transparent = transparente ? SDL_ALPHA_TRANSPARENT : 255;

    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, displayedText.c_str(), textColor, w - MARGIN / 5);
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

    SDL_Rect dialogBox = { x - w / 2, y, w, h };
    SDL_Rect textRect = { dialogBox.x + MARGIN / 10, dialogBox.y + MARGIN / 10 - scrollOffset, textSurface->w, textSurface->h };

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
        int lineHeight = 24;  // Altura de cada l�nea en p�xeles
        int textWidth = w - MARGIN / 5;  // Ancho disponible para el texto

        // Calculamos el n�mero de l�neas
        int numLines = (displayedText.size() * lineHeight / textWidth) + 1;
        int totalTextHeight = numLines * lineHeight;

        // Permitir que el jugador haga scroll solo si hay m�s texto
        if (totalTextHeight > h) {
            scrollOffset -= event.wheel.y * SCROLL_SPEED;

            // Evitar que se mueva hacia arriba m�s all� del inicio del texto
            if (scrollOffset < 0) {
                scrollOffset = 0;
            }

            // Evitar que se mueva m�s all� del final del texto
            else if (scrollOffset > totalTextHeight - h) {
                scrollOffset = totalTextHeight - h;
            }
        }
    }
}
