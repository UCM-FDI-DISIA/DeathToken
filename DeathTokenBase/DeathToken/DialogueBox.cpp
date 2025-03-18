#include "DialogueBox.h"
#include <iostream>
#include "Game.h"

const int MARGIN = 100;
const int NEXTDIALOG = 3000;
const int SCROLL_SPEED = 20;
const float AUTO_SCROLL_SPEED = 1.2;
const float AUTO_SCROLL_FAST = 5 + 1.0f / 3.0f;

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

    // Definir la altura de línea según la fuente (puede variar)
    int lineHeight = 32;  // Se recomienda usar 1.3 * tamaño de la fuente
    int textWidth = w - MARGIN / 5;  // Ancho disponible para el texto

    // Estimar el ancho promedio de un carácter
    float charWidth = 24 * 0.6;  // Aproximadamente 14.4 px para fuente de 24px

    // Calcular cuántos caracteres caben en una línea
    int charsPerLine = textWidth / charWidth;

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


    // Si la altura total del texto excede la caja de diálogo
    if (numLines * lineHeight > h) {
        // Desplazamos hacia abajo si el texto excede la caja
        if (scrollOffset < (numLines * lineHeight) - h) {
            scrollOffset += AUTO_SCROLL_SPEED * fast * AUTO_SCROLL_FAST;
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
        int lineHeight = 24;  // Altura de cada línea en píxeles
        int textWidth = w - MARGIN / 5;  // Ancho disponible para el texto

        // Calculamos el número de líneas
        int numLines = (displayedText.size() * lineHeight / textWidth) + 1;
        int totalTextHeight = numLines * lineHeight;

        // Permitir que el jugador haga scroll solo si hay más texto
        if (totalTextHeight > h) {
            scrollOffset -= event.wheel.y * SCROLL_SPEED;

            // Evitar que se mueva hacia arriba más allá del inicio del texto
            if (scrollOffset < 0) {
                scrollOffset = 0;
            }

            // Evitar que se mueva más allá del final del texto
            else if (scrollOffset > totalTextHeight - h) {
                scrollOffset = totalTextHeight - h;
            }
        }
    }
}
