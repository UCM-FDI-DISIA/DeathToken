#pragma once
#include "GameObject.h"
#include <SDL.h>

class BarraVida : public GameObject {
public:
    BarraVida(GameState* estadoJuego,
        SDL_Renderer* renderizador,
        int x,
        int y,
        int ancho,
        int alto,
        int valorMaximo,
        SDL_Color colorRelleno = { 0, 255, 0, 255 },
        SDL_Color colorFondo = { 70, 70, 70, 255 },
        bool esEspejo = false);

    virtual void render() const override;
    virtual void update() override {}

    void establecerValor(int nuevoValor);
    void establecerPosicion(int x, int y);
    void establecerVisible(bool esVisible);
    void updateColorBasedOnHealth(float currentHealth, float maxHealth) const;
    int obtenerValor() const;
    bool estaVisible() const;

    static const SDL_Color COLOR_VIDA_ALTA;     // Verde
    static const SDL_Color COLOR_VIDA_MEDIA;     // Amarillo
    static const SDL_Color COLOR_VIDA_BAJA;      // Rojo
    static const SDL_Color COLOR_FONDO;           // Fondo

private:
    SDL_Renderer* renderizador;
    SDL_Rect rect;
    int ancho, alto;
    int valorActual;
    int valorMaximo;
    SDL_Color colorRelleno;
    SDL_Color colorFondo;
    bool visible;
    bool esEspejo;
};

// Definición de los colores fuera de la clase
const SDL_Color BarraVida::COLOR_VIDA_ALTA = { 0, 255, 0, 255 };
const SDL_Color BarraVida::COLOR_VIDA_MEDIA = { 255, 255, 0, 255 };
const SDL_Color BarraVida::COLOR_VIDA_BAJA = { 255, 0, 0, 255 };
const SDL_Color BarraVida::COLOR_FONDO = { 70, 70, 70, 255 };
