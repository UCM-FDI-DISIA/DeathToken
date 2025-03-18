#include "DialogueBox.h"
#include <iostream>
#include "Game.h"

const int BOXWIDTH = 500;
const int BOXHEIGHT = 250;
const int MARGIN = 100;
const int NEXTDIALOG = 3000;

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
}

void DialogueBox::hideMessage() {
    visible = false;
}


void DialogueBox::update(float deltaTime) {
    if (!visible || !needsUpdate) return;

    message = history[currentDialogIndex];
    
    // Animación letra por letra
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

    // Mostrar todo si instantDisplay está activado
    else if (instantDisplay) {
        displayedText = message;
        charIndex = message.size();
    }

    if (charIndex == message.size()) {

        if (completedTextTime >= NEXTDIALOG) {
            completedTextTime = 0;
            if (currentDialogIndex + 1 < history.size()) {
                currentDialogIndex++;
                displayedText = "";
                charIndex = 0;
                instantDisplay = false;
            }
            else {
                visible = false; // Ocultar diálogo al terminar
            }
        }
        else {
            completedTextTime += deltaTime;
        }
        
    }
}

void DialogueBox::render() const {
    if (!visible) return;
    int transparent;
    std::string text;
    if (transparente) {
        transparent = SDL_ALPHA_TRANSPARENT;
    }
    else {
        transparent = 255;
    }

    SDL_Color textColor = { 0, 0, 0, 255 };  // Blanco para el texto

    // Crear la superficie del texto (con ajuste de ancho de 400px)
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, displayedText.c_str(), textColor, 400);
    if (!textSurface) {
        std::cerr << "Error al crear la superficie del texto: " << TTF_GetError() << std::endl;
        return;
    }

    // Crear la textura a partir de la superficie
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        std::cerr << "Error al crear la textura del texto: " << SDL_GetError() << std::endl;
        return;
    }

    // Rectángulo para el cuadro de diálogo
    SDL_Rect dialogBox = { x - BOXWIDTH/2, y, BOXWIDTH, BOXHEIGHT };  // Dimensiones por defecto para el cuadro
    SDL_Rect textRect = { dialogBox.x + MARGIN / 10, dialogBox.y + MARGIN / 10, textSurface->w, textSurface->h };


    // Ajustar el tamaño del cuadro de diálogo si el texto es más largo
    if (textSurface->w + 20 > dialogBox.w) {
        dialogBox.w = textSurface->w + 20;
        textRect.w = textSurface->w;
    }

    // Habilitar el modo de mezcla para permitir transparencia
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Establecer el color del cuadro de diálogo (transparente con negro)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, transparent);  // Fondo negro semi-transparente
    SDL_RenderFillRect(renderer, &dialogBox);  // Dibujar el cuadro de diálogo

    // Renderizar el texto sobre el cuadro de diálogo
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
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
                }
                else {
                    visible = false; // Ocultar diálogo al terminar
                }
            }
        }
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            fast = false;
        }
    }
}