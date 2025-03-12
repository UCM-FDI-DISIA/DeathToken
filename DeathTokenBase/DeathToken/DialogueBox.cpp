#include "DialogueBox.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"

const int BOXWIDTH = 500;
const int BOXHEIGHT = 250;
const int MARGIN = 100;

DialogueBox::DialogueBox(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font), visible(false) {
}

void DialogueBox::showMessage(const std::string& message) {
    this->message = message;
    visible = true;
}
void DialogueBox::addMessage(const std::string& message) {
    this->message += message;
    visible = true;
}
void DialogueBox::ResetMessage() {
    this->message = "";
    visible = true;
}
void DialogueBox::hideMessage() {
    visible = false;
}

void DialogueBox::render(bool transparente) const {
    if (!visible) return;
    int transparent;
    if (transparente) {
        transparent = SDL_ALPHA_TRANSPARENT;
    }
    else {
        transparent = 255;
    }

    SDL_Color textColor = { 255, 255, 255, 255 };  // Blanco para el texto

    // Crear la superficie del texto (con ajuste de ancho de 400px)
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textColor, 400);
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
    SDL_Rect dialogBox = { (Game::WIN_WIDTH - BOXWIDTH) / 2, Game::WIN_HEIGHT - BOXHEIGHT + MARGIN, BOXWIDTH, BOXHEIGHT };
    SDL_Rect textRect = { dialogBox.x, dialogBox.y, textSurface->w, textSurface->h };

    // Ajustar el tamaño del cuadro de diálogo si el texto es más largo
    if (textSurface->w + 20 > dialogBox.w) {
        dialogBox.w = textSurface->w + 20;
        textRect.w = textSurface->w;
    }

    // Habilitar el modo de mezcla para permitir transparencia
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Establecer el color del cuadro de diálogo (transparente con negro)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, transparent);  // Fondo negro semi-transparente
    SDL_RenderFillRect(renderer, &dialogBox);  // Dibujar el cuadro de diálogo

    // Renderizar el texto sobre el cuadro de diálogo
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void DialogueBox::render(int x, int y, bool transparente) const {
    if (!visible) return;
    int transparent;
    if (transparente) {
        transparent = SDL_ALPHA_TRANSPARENT;
    }
    else {
        transparent = 255;
    }
    
    SDL_Color textColor = { 0, 0, 0, 255 };  // Blanco para el texto

    // Crear la superficie del texto (con ajuste de ancho de 400px)
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textColor, 400);
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
    SDL_Rect dialogBox = { x, y - BOXHEIGHT / 2 + MARGIN, BOXWIDTH, BOXHEIGHT };  // Dimensiones por defecto para el cuadro
    SDL_Rect textRect = { dialogBox.x + MARGIN / 10, dialogBox.y + MARGIN / 10, textSurface->w, textSurface->h };

    // Ajustar el tamaño del cuadro de diálogo si el texto es más largo
    if (textSurface->w + 20 > dialogBox.w) {
        dialogBox.w = textSurface->w + 20;
        textRect.w = textSurface->w;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Establecer el color del cuadro de diálogo (transparente con negro)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, transparent);

    SDL_RenderFillRect(renderer, &dialogBox);  // Dibujar el cuadro de diálogo

    // Renderizar el texto sobre el cuadro de diálogo
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}