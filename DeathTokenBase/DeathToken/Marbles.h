#pragma once

#include "gameState.h"
#include "vector"
#include "Texture.h"

class Marbles : public GameState
{
public:
	Marbles(Game* game);
	enum colors { RED, GREEN, BLUE, YELLOW };
	Texture* texture;

	std::vector<colors> marbles;


	void generateMarbles();

	void render() const override;



	//Detectar botones y que apuesta hace y con que cantidad de monedas
	//Metodo play que hace que el juego lanze las 3 bolas de colores con un random
	//Con las bolas que salen detectar si estan igual que la apuesta
	//dependiendo de que apuesta ganadora, dar un mult de las fichas que apuestas
};

