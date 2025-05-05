#pragma once
#include "gameState.h"
#include "texture.h"
#include "button.h"

class PauseState: public GameState
{
protected:
	Button* back;
	Button* menu;
	Texture* texture;
	GameState* anterior;//para renderizar el juego en el fondo
public:
	PauseState(Game* g, GameState* other);
	virtual ~PauseState();//borrar botones
	
	virtual void render() const;
};

