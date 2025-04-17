#include "tutorial.h"


Tutorial::Tutorial(Game* game, GameState* gameState, std::vector<Texture*> imagesTutorial) :
	GameState(game), 
	anterior(gameState),
	images(imagesTutorial),//vector imagenes del tutorial
	ui(new UITutorial(this, game, imagesTutorial.size())),//botones de exit, sig...
	currentPage(0)
{
}

void Tutorial::render() const {
	//render estado anterior
	anterior->render();

	//capa negra translucida
	SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
	SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
	SDL_RenderFillRect(game->getRenderer(), &black);

	//render imagenes de cada tutorial
	if (!images.empty() && currentPage < images.size()) {
		images[currentPage]->render();
	}
	GameState::render();//render botones de exit y flechas
}

void Tutorial::nextPage()//pag sig
{
	if (currentPage < images.size() - 1) {
		currentPage++;
	}
}

void Tutorial::previousPage()//pag ant
{
	if (currentPage > 0) {
		currentPage--;
	}
}
