#pragma once
#include "gameObject.h"
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
	void updateColorBasedOnHealth(float currentHealth, int maxHealth);
	int obtenerValor() const;
	bool estaVisible() const;

	const SDL_Color COLOR_VIDA_ALTA = { 0, 255, 0, 255 };     // Verde
	const SDL_Color COLOR_VIDA_MEDIA = { 255, 255, 0, 255 };     // Amarillo
	const SDL_Color COLOR_VIDA_BAJA = { 255, 0, 0, 255 };;      // Rojo
	const SDL_Color COLOR_FONDO = { 70, 70, 70, 255 };           // Fondo

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
