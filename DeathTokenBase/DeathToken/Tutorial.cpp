#include "tutorial.h"
#include "soundManager.h"

Tutorial::Tutorial(Game* game, GameState* gameState, std::vector<Texture*> imagesTutorial) :
	GameState(game), 
	anterior(gameState),
	images(imagesTutorial),//vector imagenes del tutorial
	ui(new UITutorial(this, game, imagesTutorial.size())),//botones de exit, sig...
	currentPage(0)
{
}

void Tutorial::update()
{
	//render imagenes de cada tutorial
	if (!images.empty() && currentPage < images.size()) {
	
		if (currentPage != 0 && upArrowBut == nullptr) {
			upArrowBut = ui->upArrow();
		}
		if (currentPage == 0 && upArrowBut != nullptr) {
			GameState::deleteSpecificGO(upArrowBut);
			GameState::deleteSpecificEH(upArrowBut);
			upArrowBut = nullptr;
		}
		if (images.size() > 1 && currentPage != images.size()-1 && downArrow==nullptr) {
			downArrow = ui->downArrow();
		}
		if (currentPage == images.size() - 1 && downArrow != nullptr) {
			GameState::deleteSpecificGO(downArrow);
			GameState::deleteSpecificEH(downArrow);
			downArrow = nullptr;
		}
	}
}

void Tutorial::render() const {
	//render estado anterior
	anterior->render();

	//capa negra translucida
	SDL_Rect black{ 0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT };
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
	auto& soundManager = SoundManager::obtenerInstancia();
	soundManager.reproducirEfecto("PasaPag");
	game->pop();
	if (currentPage < images.size() - 1) {
		currentPage++;
	}
}

void Tutorial::previousPage()//pag ant
{
	auto& soundManager = SoundManager::obtenerInstancia();
	soundManager.reproducirEfecto("PasaPag");
	if (currentPage > 0) {
		currentPage--;
	}
}
