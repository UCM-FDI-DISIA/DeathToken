#include "barraVida.h"
#include <SDL.h>

BarraVida::BarraVida(GameState* estadoJuego, SDL_Renderer* renderizador, int x, int y,
	int ancho, int alto, int valorMaximo,
	SDL_Color colorRelleno, SDL_Color colorFondo,
	bool esEspejo)
	: GameObject(estadoJuego),
	renderizador(renderizador),
	ancho(ancho),
	alto(alto),
	valorActual(valorMaximo),
	valorMaximo(valorMaximo),
	colorRelleno(colorRelleno),
	colorFondo(colorFondo),
	visible(true),
	esEspejo(esEspejo) {
	rect.x = x;
	rect.y = y;
	rect.w = ancho;
	rect.h = alto;
}

void BarraVida::updateColorBasedOnHealth(float currentHealth, int maxHealth)
{
	float ratio = currentHealth / maxHealth;

	if (ratio > 0.6f) {
		colorRelleno = COLOR_VIDA_ALTA;  // Verde (>60%)
	}
	else if (ratio > 0.3f) {
		colorRelleno = COLOR_VIDA_MEDIA;  // Amarillo (30%-60%)
	}
	else {
		colorRelleno = COLOR_VIDA_BAJA;  // Rojo (<30%)
	}
}
void BarraVida::render() const
{
	if (!visible || !renderizador)
		return;
	SDL_SetRenderDrawColor(renderizador, colorFondo.r, colorFondo.g, colorFondo.b, colorFondo.a);
	SDL_RenderFillRect(renderizador, &rect);
	if (valorMaximo > 0 && valorActual > 0) {
		int anchoRelleno = (valorActual * rect.w) / valorMaximo;
		SDL_Rect relleno;

		if (esEspejo) {
			relleno = { rect.x + (rect.w - anchoRelleno), rect.y, anchoRelleno, rect.h };
		}
		else {
			relleno = { rect.x, rect.y, anchoRelleno, rect.h };
		}
		SDL_SetRenderDrawColor(renderizador, colorRelleno.r, colorRelleno.g, colorRelleno.b, colorRelleno.a);
		SDL_RenderFillRect(renderizador, &relleno);
	}

	// Dibujar borde
	SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderizador, &rect);
}
void BarraVida::establecerValor(int nuevoValor)
{
	valorActual = nuevoValor;
	if (valorActual < 0) valorActual = 0;
	if (valorActual > valorMaximo) valorActual = valorMaximo;

	updateColorBasedOnHealth(static_cast<float>(valorActual),
                                 (valorMaximo));
}
void BarraVida::establecerPosicion(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void BarraVida::establecerVisible(bool esVisible)
{
	visible = esVisible;
}


int BarraVida::obtenerValor() const
{
	return valorActual;
}

bool BarraVida::estaVisible() const
{
	return visible;
}

