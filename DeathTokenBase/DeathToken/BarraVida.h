#pragma once
#include "GameObject.h"
#include <SDL.h>

class BarraVida : public GameObject {
public:
    BarraVida(GameState* estadoJuego, SDL_Renderer* renderizador, int x, int y,
        int ancho, int alto, int valorMaximo,
        SDL_Color colorRelleno, SDL_Color colorFondo);

    BarraVida() : GameObject(), renderizador(nullptr), ancho(0), alto(0),
        valorActual(0), valorMaximo(0),
        colorRelleno({ 255, 0, 0, 255 }), colorFondo({ 50, 50, 50, 255 }),
        visible(false) {}


    virtual void render() const override;
    virtual void update() override {}  

    void establecerValor(int nuevoValor);
    void establecerPosicion(int x, int y);
    void establecerVisible(bool esVisible);

    int obtenerValor() const;
    bool estaVisible() const;

private:
    SDL_Renderer* renderizador;
    int ancho, alto;
    int valorActual;
    int valorMaximo;
    SDL_Color colorRelleno;
    SDL_Color colorFondo;
    bool visible;
};