#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "gameObject.h"

class Text : public GameObject {
public:
    enum Alignment { IZQUIERDA, DERECHA, CENTRO };
    //Constructora sencilla, texto blanco, si no se especifica alineamiento a la izquierda
    Text(GameState* gS, TTF_Font* typo, int x, int y, int size, Alignment alignment = IZQUIERDA);
    //Constructora para color, si no se especifica alineamiento a la izquierda
    Text(GameState* gS, TTF_Font* typo, int x, int y, int size, SDL_Color textColor, Alignment alignment = IZQUIERDA);
    //Constructora para usar contorno, relleno blanco y contorno negro, si no se especifica alineamiento a la izquierda
    Text(GameState* gS, TTF_Font* typo, int x, int y, int size, int outlineSize, Alignment alignment = IZQUIERDA);
    //Constructora para usar contorno con colores, si no se especifica alineamiento a la izquierda
    Text(GameState* gS, TTF_Font* typo, int x, int y, int size, int outlineSize,
         SDL_Color textColor, SDL_Color outlineColor, Alignment alignment = IZQUIERDA);
    virtual ~Text() { renderer = nullptr; TTF_CloseFont(font); };
    void setPos(int x, int y);
    std::string getMessage();
    void setMessage(const std::string& message);
    void addMessage(const std::string& message);
    void eraseMessage();
    void setColor(int red, int green, int blue, int alpha);
    void setSize(int size);
    void setOutlineColor(int red, int green, int blue, int alpha);
    //Para cajas de texto, por defecto el ancho es infinito (no habrá saltos de línea automáticos)
    void setWidth(int width);
    void update() override {};
    void render() const override;

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string message;

    int x;
    int y;
    int size;
    int outlineSize;

    SDL_Color textColor;
    SDL_Color outlineColor;
    Alignment alignment;
    int boxWidth;

private:
    void createTextSurfaces(SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const;
    void createTextTextures(SDL_Texture*& textTexture, SDL_Texture*& outlineTexture, SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const;
    void createTextRects(SDL_Rect& textRect, SDL_Rect& outlineRect, SDL_Surface*& textSurface, SDL_Surface*& outlineSurface) const;
};