#include "roulette.h"

Roulette::Roulette(GameState* gS, Game* game, Point2D<> pos, Texture* text, PlayerEconomy* eco) : sceneObject(gS, pos, text), gS(gS), game(game), eco(eco), texture(text) {
	w = Game::WIN_WIDTH / 2;
	h = Game::WIN_WIDTH / 2;
}

void Roulette::render() const {
	SDL_Rect rect = getRenderRect();
	texture->render(rect, rot);
}

void Roulette::update() {
	if (eco->getInsanity() > 0) {
		texture = game->getTexture(ROULETTEINSANITY);
	}
	else {
		texture = game->getTexture(ROULETTE);
	}
	rot += speed;
	if (rot > 360.0) rot -= 360.0;
	speed *= decelerate;
	if (started && speed == 0) {
		started = false;
		if (eco->getInsanity() > 0) {
			if (rot >= 0.0f && rot <= 61.2f) {
				cout << "20 ALMA ROJA" << endl;
				eco->addRedSouls(20);
			}
			else if (rot >= 61.2f && rot <= 68.4f) {
				cout << "GUADAÑA" << endl;
			}
			else if (rot >= 68.4f && rot <= 180.0f) {
				cout << "1 ALMA ROJA" << endl;
				eco->addRedSouls(1);
			}
			else if (rot >= 180.0f && rot <= 241.2f) {
				cout << "-10 ALMA ROJA" << endl;
				eco->addRedSouls(-10);
			}
			else if (rot >= 241.2f && rot <= 248.4f) {
				cout << "MUERTE" << endl;
			}
			else {
				cout << "NADA" << endl;
			}
		}
		else {
			if (rot >= 61.2f && rot <= 180.0f) {
				cout << "4000 TOKEN" << endl;
				eco->addBlueSouls(4000);
				game->push(new Award(game, gS, 1, 4000));
			}
			else if (rot >= 180.0f && rot <= 298.8f) {
				cout << "LOCURA" << endl;
				eco->setInsanity(5);
			}
			else if (rot >= 298.8f && rot <= 360.0f) {
				cout << "1 ALMA ROJA" << endl;
				eco->addRedSouls(1);
			}
			else {
				cout << "NADA" << endl;
			}
		}
	}
}

void Roulette::addSpeed(int s) {
	if (speed == 0)
	{
		speed = s;
		started = true;
	}
}