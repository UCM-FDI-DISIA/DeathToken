#pragma once
#include "gameState.h"
#include "button.h"
#include "texture.h"
#include "ui.h"
#include <vector>


class Tutorial : public GameState//con botones para pasar de imagen si es muy largo 
{
	Texture* texture;
	UITutorial* ui;//botones de siguiente y exit
	GameState* anterior;//para renderizar el juego en el fondo
	std::vector<Texture*> images; //vector de imágenes del tutorial
	size_t currentPage; //pag actual del tutorial

	ButtonUI* downArrow = nullptr;
	ButtonUI* upArrowBut = nullptr;

public:
	Tutorial(Game* game, GameState* gameState, std::vector<Texture*> imagesTutorial);//cuando instancies la clase desde otro lado, le metes tu imagen de tutorial como textura
	virtual ~Tutorial() {
		delete ui; GameState::deleteSpecificGO(downArrow);
		GameState::deleteSpecificEH(downArrow);
		GameState::deleteSpecificGO(upArrowBut);
		GameState::deleteSpecificEH(upArrowBut);
	};//CUIDADO DEJA BASURA PERO NOSE SI SON LA UI O QUE ,,,,, era eso!!

	void update() override;
	void render() const override;
	void nextPage(); //avanza a la siguiente pag
	void previousPage(); //retrocede a la pag anterior
	size_t getPage() {
		return currentPage;
	}; //devuelve el numero de pagina
};

