﻿#include "text.h"
#include "game.h"
#include <iostream>

Text::Text(GameState* gS, TTF_Font* typo, int x, int y, Alignment alignment)
    : GameObject(gS), textColor({ 255, 255, 255, 255 }), outlineColor({ 0, 0, 0, 0 }),
    x(x), y(y), outlineSize(0), alignment(alignment), boxWidth(0)
{
    font = typo;
    TTF_SetFontOutline(font, 2);
    renderer = gS->getGame()->getRenderer();
    message = "";
}
Text::Text(GameState* gS, TTF_Font* typo, int x, int y, SDL_Color textColor, Alignment alignment)
    : GameObject(gS), textColor(textColor), outlineColor({ 0, 0, 0, 0 }),
    x(x), y(y), outlineSize(0), alignment(alignment), boxWidth(0)
{
    font = typo;
    TTF_SetFontOutline(font, 2);
    renderer = gS->getGame()->getRenderer();
    message = "";
}
Text::Text(GameState* gS, TTF_Font* typo, int x, int y, int outlineSize, Alignment alignment)
    : GameObject(gS), textColor({ 255, 255, 255, 255 }), outlineColor({ 0, 0, 0, 0 }),
    x(x), y(y), outlineSize(outlineSize), alignment(alignment), boxWidth(0)
{
    font = typo;
    TTF_SetFontOutline(font, 2);
    renderer = gS->getGame()->getRenderer();
    message = "";
}
Text::Text(GameState* gS, TTF_Font* typo, int x, int y, int outlineSize,
    SDL_Color textColor, SDL_Color outlineColor, Alignment alignment)
    : GameObject(gS), textColor(textColor), outlineColor(outlineColor),
    x(x), y(y), outlineSize(outlineSize), alignment(alignment), boxWidth(0)
{
    font = typo;
    TTF_SetFontOutline(font, 2);
    renderer = gS->getGame()->getRenderer();
    message = "";
}
void Text::setFont(TTF_Font* newFont)
{
    font = newFont;
}
void
Text::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}
std::string
Text::getMessage()
{
    return message;
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
Text::setColor(int red, int green, int blue, int alpha)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;
}
void
Text::setOutlineColor(int red, int green, int blue, int alpha)
{
    outlineColor.r = red;
    outlineColor.g = green;
    outlineColor.b = blue;
    outlineColor.a = alpha;
}
void
Text::setWidth(int width)
{
    boxWidth = width;
}
void
Text::render() const
{
    SDL_Surface* textSurface = nullptr;
    SDL_Surface* outlineSurface = nullptr;
    createTextSurfaces(textSurface, outlineSurface);

    SDL_Texture* textTexture = nullptr;
    SDL_Texture* outlineTexture = nullptr;
    createTextTextures(textTexture, outlineTexture, textSurface, outlineSurface);

    SDL_Rect textRect;
    SDL_Rect outlineRect;
    createTextRects(textRect, outlineRect, textSurface, outlineSurface);

    SDL_RenderCopy(renderer, outlineTexture, nullptr, &outlineRect);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Liberar los recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(outlineTexture);
    SDL_FreeSurface(outlineSurface);
}
void
Text::createTextSurfaces(SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const
{
    if (alignment > 0 || boxWidth == 0)
    {
        TTF_SetFontOutline(font, 0);
        textSurface = TTF_RenderText_Blended(font, message.c_str(), textColor);
        TTF_SetFontOutline(font, outlineSize);
        outlineSurface = TTF_RenderText_Blended(font, message.c_str(), outlineColor);
    }
    else
    {
        TTF_SetFontOutline(font, 0);
        textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textColor, boxWidth);
        TTF_SetFontOutline(font, outlineSize);
        outlineSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), outlineColor, boxWidth);
    }

    if (!textSurface) {
#ifdef DEBUG
        std::cerr << "Error al crear la superficie del texto: " << TTF_GetError() << std::endl;
#endif // DEBUG

        return;
    }
}
void
Text::createTextTextures(SDL_Texture*& textTexture, SDL_Texture*& outlineTexture, SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const
{
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
#ifdef DEBUG
        std::cerr << "Error al crear la textura del texto: " << SDL_GetError() << std::endl;
#endif // DEBUG

        return;
    }
}
void
Text::createTextRects(SDL_Rect& textRect, SDL_Rect& outlineRect, SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const
{
    if (alignment == IZQUIERDA)
    {
        textRect = { x, y, textSurface->w, textSurface->h };
        int auxX = x - ((outlineSurface->w - textSurface->w) / 2);
        int auxY = y - ((outlineSurface->h - textSurface->h) / 2);
        outlineRect = { auxX, auxY, outlineSurface->w, outlineSurface->h };
    }
    if (alignment == DERECHA)
    {
        int text_width, text_height;
        TTF_SizeText(font, message.c_str(), &text_width, &text_height);

        int auxX = x - text_width;
        textRect = { auxX, y, textSurface->w, textSurface->h };
        auxX = auxX - ((outlineSurface->w - textSurface->w) / 2);
        int auxY = y - ((outlineSurface->h - textSurface->h) / 2);
        outlineRect = { auxX, auxY, outlineSurface->w, outlineSurface->h };
    }
    else
    {
        int text_width, text_height;
        TTF_SizeText(font, message.c_str(), &text_width, &text_height);

        int auxX = x - (text_width / 2);
        textRect = { auxX, y, textSurface->w, textSurface->h };
        auxX = auxX - ((outlineSurface->w - textSurface->w) / 2);
        int auxY = y - ((outlineSurface->h - textSurface->h) / 2);
        outlineRect = { auxX, auxY, outlineSurface->w, outlineSurface->h };
    }
}