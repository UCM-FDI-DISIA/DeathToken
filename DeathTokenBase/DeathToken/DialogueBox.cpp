#include "DialogueBox.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

DialogueBox::DialogueBox(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font), visible(false) {
}

void DialogueBox::showMessage(const std::string& message) {
    this->message = message;
    visible = true;
}

void DialogueBox::hideMessage() {
    visible = false;
}

void DialogueBox::render() {
    if (!visible) return;

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
    SDL_Rect dialogBox = { 50, 300, 500, 100 };  // Dimensiones por defecto para el cuadro
    SDL_Rect textRect = { dialogBox.x + 10, dialogBox.y + 10, textSurface->w, textSurface->h };

    // Ajustar el tamaño del cuadro de diálogo si el texto es más largo
    if (textSurface->w + 20 > dialogBox.w) {
        dialogBox.w = textSurface->w + 20;
        textRect.w = textSurface->w;
    }

    // Establecer el color del cuadro de diálogo (transparente con negro)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(renderer, &dialogBox);  // Dibujar el cuadro de diálogo

    // Renderizar el texto sobre el cuadro de diálogo
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}