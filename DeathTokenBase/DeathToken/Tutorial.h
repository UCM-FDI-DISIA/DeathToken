#pragma once
#include "GameState.h"
#include "Button.h"
#include "Texture.h"
#include "UI.h"

class Tutorial: public GameState//con botones para pasar de imagen si es muy largo 
{
	Texture* texture;
	UITutorial* ui;
	GameState* anterior;

public:
	Tutorial(Game* game, GameState* gameState);//cuando instancies la clase desde otro lado, le metes tu imagen de tutorial como textura
	virtual ~Tutorial() { delete ui; };//CUIDADO DEJA BASURA PERO NOSE SI SON LA UI O QUE ,,,,, era eso!!

	//void update() override;  
	void render() const override;
};

