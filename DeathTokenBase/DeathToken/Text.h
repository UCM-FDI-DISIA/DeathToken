#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "gameObject.h"

class Text : public GameObject {
public:
    Text(GameState* gS, const char*, int x, int y, int size);
    Text(GameState* gS, const char*, int x, int y, int size, int red, int green, int blue, int alpha);
    virtual ~Text() { renderer = nullptr; TTF_CloseFont(font); };
    void setMessage(const std::string& message);
    void addMessage(const std::string& message);
    void eraseMessage();
    void setColor(int red, int green, int blue);
    void setAlpha(int alpha);
    void setWidht(int width);
    void update() override {};
    void render() const override;

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string message;

    int x;
    int y;
    int size;

    int red;
    int green;
    int blue;
    int alpha;

    int boxWidth; //Para cajas de texto, por defecto todo el ancho de la pantalla
};