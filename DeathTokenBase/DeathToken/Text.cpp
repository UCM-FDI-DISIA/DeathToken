#include "Text.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"

Text::Text(GameState* gS, const char* typo, int x, int y, int size)
    : GameObject(gS), renderer(renderer),
      red(255), green(255), blue(255), alpha(255), x(x), y(y), size(size)
{
    renderer = gS->getGame()->getRenderer();
    boxWidth = gS->getGame()->WIN_WIDTH;
    font = TTF_OpenFont(typo, 24);
}
Text::Text(GameState* gS, const char* typo, int x, int y, int size, int red, int green, int blue, int alpha)
    : GameObject(gS), renderer(renderer),
    red(red), green(green), blue(blue), alpha(alpha), x(x), y(y), size(size)
{
    renderer = gS->getGame()->getRenderer();
    boxWidth = gS->getGame()->WIN_WIDTH;
    font = TTF_OpenFont(typo, 24);
}
void
Text::setMessage(const std::string& message)
{
    this->message = message;
}
void
Text::addMessage(const std::string& message)
{
    this->message += message;
}
void
Text::eraseMessage()
{
    this->message = "";
}
void
Text::setColor(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}
void
Text::setAlpha(int alpha) {
    this->alpha = alpha;
}
void
Text::setWidth(int width)
{
    boxWidth = width;
}
void
Text::render() const
{

    SDL_Color textColor = { red, green, blue, alpha };

    // Crear la superficie del texto (con ajuste de ancho de 400px)
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textColor, boxWidth);
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

    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };

    // Renderizar el texto sobre el cuadro de di�logo
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}