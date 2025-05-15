#include "award.h"
#include "game.h"
#include "SDL.h"

Award::Award(Game* game, GameState* lastState, long long bet, long long mWin)
	: GameState(game), state(lastState), betG(bet), mWinG(mWin), startTime(SDL_GetTicks()), background(game->getTexture(BLACKFOND)), currentWin(0) {

	background->modAlfa(140);

	//Crear calse intermedia PLAystate que herede todos los juegos y hacer un puntero que puedas pillar de cada juego
	//Mirar el virtualTimer


	text = new Text(state, game->getTypo(AWARD), relativeX((float)Game::WIN_WIDTH / 2.0f), relativeY((float)Game::WIN_HEIGHT / 5.0f), relativeX((float)wSize), relativeX((float)cSize), Text::CENTRO);
	long long multi = 0;
	if (betG != 0) {
		multi = mWinG / betG;
		text->setMessage(getWinMessage((int)multi));
	}
	this->addObjects(text);

	winText = new Text(state, game->getTypo(AWARD), relativeX((float)Game::WIN_WIDTH / 2.0f), relativeY((float)Game::WIN_HEIGHT / 2.0f), relativeX((float)nSize), relativeX((float)cSize), Text::CENTRO);
	winText->setMessage("0");
	this->addObjects(winText);

	soulText = new Text(state, game->getTypo(AWARD), relativeX((float)Game::WIN_WIDTH / 2.0f), relativeY((float)Game::WIN_HEIGHT / 6.0f) * 5, relativeX((float)nSize), relativeX((float)cSize), Text::CENTRO);

	if (PlayerEconomy::getInsanity() > 0) {
		std::string souls = std::to_string(multi) + " SOULS";
		soulText->setMessage(souls);
		soulText->setColor(255, 70, 70, 255);
	}
	else {
		soulText->setMessage(" ");
	}
	this->addObjects(soulText);
}


void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
	if (currentWin < mWinG) {
		if (mWinG <= 1000) {
			currentWin += std::min((long long)10, mWinG - currentWin);
		}
		else {
			currentWin += std::min((long long)100, mWinG - currentWin);
		}
		winText->setMessage(std::to_string(currentWin));
		startTime = SDL_GetTicks();
	}
	else if (SDL_GetTicks() - startTime >= 1000) {
		long long multi = 0;
		if (PlayerEconomy::getInsanity() > 0 && betG != 0) {
			multi = mWinG / betG;
		}
		HUDManager::applyWinBet(currentWin);
		PlayerEconomy::addRedSouls(multi);
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
	int m = (int)((n / 1920.0f) * Game::WIN_WIDTH);
	return m;
}

inline int
Award::relativeY(const float& n)
{
	int m = (int)((n / 1080.0f) * Game::WIN_HEIGHT);
	return m;
}