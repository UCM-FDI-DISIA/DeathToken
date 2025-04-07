#include "award.h"
#include "game.h"
#include "SDL.h"

Award::Award(Game* game, GameState* lastState, long long bet, long long mWin)
	: GameState(game), state(lastState), betG(bet), mWinG(mWin), startTime(SDL_GetTicks()), background(game->getTexture(BLACKFOND)), currentWin(0) {

	background->modAlfa(140);

	//Crear calse intermedia PLAystate que herede todos los juegos y hacer un puntero que puedas pillar de cada juego
	//Mirar el virtualTimer


	text = new Text(state, game->getTypo(AWARD), relativeX(Game::WIN_WIDTH / 2.0f), relativeY(Game::WIN_HEIGHT / 5.0f), relativeX(wSize), relativeX(cSize), Text::CENTRO);
	//if (betG != 0) {
		int multi = mWinG / betG;
		text->setMessage(getWinMessage(multi));
	//}
	this->addObjects(text);

	winText = new Text(state, game->getTypo(AWARD), relativeX(Game::WIN_WIDTH / 2.0f), relativeY(Game::WIN_HEIGHT / 2.0f), relativeX(nSize), relativeX(cSize), Text::CENTRO);
	winText->setMessage("0");
	this->addObjects(winText);
}


void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
	if (currentWin < mWinG) {
		currentWin += std::min((long long)10, mWinG - currentWin);
		winText->setMessage(std::to_string(currentWin));
		startTime = SDL_GetTicks();
	}
	else if (SDL_GetTicks() - startTime >= 1000) {
		HUDManager::applyWinBet(currentWin);
		game->pop(); // Regresar al estado anterior
	}

}

void Award::render() const {
	state->render();
	//background->render();
	GameState::render();
	//Una vez entrado tiene que ir a show Message y renderizar la cantidad del premio con un mensaje
	//

}

std::string Award::getWinMessage(int multiplier) {
	if (multiplier <= 3) return "WIN";
	if (multiplier <= 5) return "BIG WIN";
	if (multiplier <= 10) return "MEGA WIN";
	if (multiplier <= 20) return "EPIC WIN";
	return "ESTAS LOCOOO";
}
inline int Award::relativeX(const float& n)
{
	return (int)((n / 1920.0f) * Game::WIN_WIDTH);
}

inline int
Award::relativeY(const float& n)
{
	return (int)((n / 1080.0f) * Game::WIN_HEIGHT);
}