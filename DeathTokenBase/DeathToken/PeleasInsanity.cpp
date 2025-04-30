#include "inputBox.h"
#include "PeleasInsanity.h"

PeleasInsanity::PeleasInsanity(Game* game)
	: GameState(game)
	, input1(new InputBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>(Game::WIN_WIDTH / 3), static_cast<int>(3 * Game::WIN_HEIGHT / 4), true, false, 400, 180))
{
	input1->setMaxLength(3);
	input1->setActive(true);
	addEventListener((EventHandler*)input1);
}

void PeleasInsanity::render() const
{
	SDL_Rect fondo;
	fondo.x = fondo.y = 0;
	fondo.h = Game::WIN_HEIGHT;
	fondo.w = Game::WIN_WIDTH;
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 255, 255, 255);
	SDL_RenderFillRect(game->getRenderer(), &fondo);

	input1->render();

	GameState::render();
}


int lastUpdate = 0;

int valor = 100;

void PeleasInsanity::update()
{
	uint currentTime = SDL_GetTicks();
	input1->update(static_cast<float>(currentTime - lastUpdate));
	if (!input1->getActive()) {
		int apuesta = std::stoi(input1->getMessage().empty() ? "0" : input1->getMessage());
		if (apuesta == valor) {
			input1->showMessage("Ganaste");
		}
		else {
			input1->showMessage("Perdiste");
			input1->setActive(true);
		}
	}
	GameState::update();
	lastUpdate = currentTime;
}

