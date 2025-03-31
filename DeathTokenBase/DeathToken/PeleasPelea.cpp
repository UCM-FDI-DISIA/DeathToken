#include "BarraVida.h"
#include "GameState.h"
#include <SDL.h>

class PeleasPelea : public GameState {
private:
  BarraVida* barraVida1;
  BarraVida* barraVida2;
  SDL_Renderer* renderizador;

public:
  PeleasPelea(Game* juego, SDL_Renderer* renderer)
    : GameState(juego)
    , renderizador(renderer)
  {
    // Crear primera barra de vida (roja)
    SDL_Color rojo = { 255, 0, 0, 255 };
    SDL_Color gris = { 100, 100, 100, 255 };
    barraVida1 = new BarraVida(this,
                               renderizador,
                               100,
                               100,  // Posición (x,y)
                               200,
                               30,   // Ancho y alto
                               100,  // Valor máximo
                               rojo,
                               gris);  // Colores

    // Crear segunda barra de vida (verde)
    SDL_Color verde = { 0, 255, 0, 255 };
    barraVida2 = new BarraVida(this,
                               renderizador,
                               100,
                               150,  // Posición (x,y)
                               200,
                               30,   // Ancho y alto
                               100,  // Valor máximo
                               verde,
                               gris);  // Colores
  }

  ~PeleasPelea()
  {
    delete barraVida1;
    delete barraVida2;
  }

  void render() const override
  {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);

    // Renderizar las barras de vida
    barraVida1->render();
    barraVida2->render();

    // Presentar render
    SDL_RenderPresent(renderizador);
  }

  void update() override
  {
    // Lógica de actualización (si es necesaria)
  }

  // Métodos para manipular las barras desde fuera si es necesario
  void setValorBarra1(int valor) { barraVida1->establecerValor(valor); }
  void setValorBarra2(int valor) { barraVida2->establecerValor(valor); }
};
