#include "award.h"
#include "game.h"
#include "SDL.h"

Award::Award(Game* game, GameState* lastState, long long bet, long long mWin, bool locura, long long multiplicator, bool insanity)
	: GameState(game), state(lastState), betG(bet), mWinG(mWin), startTime(SDL_GetTicks()), background(game->getTexture(BLACKFOND)), currentWin(0) {

	background->modAlfa(140);
	if (!locura)
	{
		text = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY((float)Game::WIN_HEIGHT / 5.0f), relativeX((float)cSize), Text::CENTRO);
	}
	else {
		text = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY(130.0f), relativeX((float)cSize), Text::CENTRO);
	}
	long long multi = 0;
	if (betG != 0) {
		multi = mWinG / betG;
		text->setMessage(getWinMessage((int)multi));
	}
	else {
		text->setMessage(" ");
	}
	this->addObjects(text);
	if (!locura)
	{
		winText = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY((float)Game::WIN_HEIGHT / 2.0f), relativeX((float)cSize), Text::CENTRO);
	}
	else {
		winText = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY(380.0f), relativeX((float)cSize), Text::CENTRO);
	}
	if (betG != 0)
	{
		winText->setMessage("0");
	}
	else {
		winText->setMessage(" ");
	}
	this->addObjects(winText);
	if (multiplicator == -1)
	{
		soulText = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY(700.0f), relativeX((float)cSize), Text::CENTRO);
	}
	else {
		soulText = new Text(state, game->getTypo(AWARD), Game::WIN_WIDTH / 2.0f, relativeY(450.0f), relativeX((float)cSize), Text::CENTRO);
		multi = multiplicator;
	}


	if ((locura || multiplicator != -1) && !insanity) {
		std::string souls = std::to_string(multi) + " SOULS";
		soulText->setMessage(souls);
		soulText->setColor(255, 70, 70, 255);
	}
	else {
		soulText->setMessage(" ");
	}
	if (insanity && locura) {
		std::string souls = "10 INSANITY";
		soulText->setMessage(souls);
		soulText->setColor(254, 202, 0, 255);
	}
	this->addObjects(soulText);
}


void Award::update() {
	//Tendra que contar el tiempo para que despues de 5 segundos de mostrar el mensaje vuelva a la escena anterior
	if (currentWin < mWinG) {
		if (mWinG <= 1000) {
			currentWin += std::min((long long)10, mWinG - currentWin);
		}
		else if (mWinG <= 10000) {
			currentWin += std::min((long long)100, mWinG - currentWin);
		}
		else if (mWinG <= 100000) {
			currentWin += std::min((long long)1000, mWinG - currentWin);
		}
		else {
			currentWin += std::min((long long)10000, mWinG - currentWin);
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
	background->render();
	GameState::render();
	//Una vez entrado tiene que ir a show Message y renderizar la cantidad del premio con un mensaje


}

std::string Award::getWinMessage(int multiplier) {
	if (multiplier <= 3) return "WIN";
	if (multiplier <= 5) return "BIG WIN";
	if (multiplier <= 10) return "MEGA WIN";
	if (multiplier <= 20) return "EPIC WIN";
	return "ESTAS LOCOOO";
}
int Award::relativeX(const float& n)
{
	int m = (int)(Game::WIN_WIDTH * (n / 1920.0f));
	return m;
}

int
Award::relativeY(const float& n)
{
	int m = (int)(Game::WIN_HEIGHT * (n / 1080.0f));
	return m;
}