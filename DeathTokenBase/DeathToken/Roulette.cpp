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
		if (SDL_GetTicks() - animTime >= 35.0f) {
			if (i == 0)
			{
				texture = game->getTexture(ROULETTEANIM0);
			}
			else if (i == 1)
			{
				texture = game->getTexture(ROULETTEANIM1);
			}
			else if (i == 2)
			{
				texture = game->getTexture(ROULETTEANIM2);
			}
			else if (i == 3)
			{
				texture = game->getTexture(ROULETTEANIM3);
			}
			else if (i == 4)
			{
				texture = game->getTexture(ROULETTEANIM4);
			}
			else if (i == 5)
			{
				texture = game->getTexture(ROULETTEANIM5);
			}
			else if (i == 6)
			{
				texture = game->getTexture(ROULETTEANIM6);
			}
			else if (i == 7)
			{
				texture = game->getTexture(ROULETTEANIM7);
			}
			else if (i == 8)
			{
				texture = game->getTexture(ROULETTEANIM8);
			}
			else if (i == 9)
			{
				texture = game->getTexture(ROULETTEANIM9);
			}
			else if (i == 10)
			{
				texture = game->getTexture(ROULETTEANIM10);
			}
			else if (i == 11)
			{
				texture = game->getTexture(ROULETTEANIM11);
			}
			else if (i == 12)
			{
				texture = game->getTexture(ROULETTEANIM12);
			}
			else if (i == 13)
			{
				texture = game->getTexture(ROULETTEANIM13);
			}
			else if (i == 14)
			{
				texture = game->getTexture(ROULETTEANIM14);
			}
			else if (i == 15)
			{
				texture = game->getTexture(ROULETTEANIM15);
			}
			else if (i == 16)
			{
				texture = game->getTexture(ROULETTEANIM16);
			}
			else if (i == 17)
			{
				texture = game->getTexture(ROULETTEANIM17);
			}
			else if (i == 18)
			{
				texture = game->getTexture(ROULETTEANIM18);
			}
			else if (i == 19)
			{
				texture = game->getTexture(ROULETTEANIM19);
			}
			else if (i == 20)
			{
				texture = game->getTexture(ROULETTEANIM20);
			}
			else if (i == 21)
			{
				texture = game->getTexture(ROULETTEANIM21);
			}
			else if (i == 22)
			{
				texture = game->getTexture(ROULETTEANIM22);
			}
			else if (i == 23)
			{
				texture = game->getTexture(ROULETTEANIM23);
			}
			else if (i == 24)
			{
				texture = game->getTexture(ROULETTEANIM24);
			}
			else if (i == 25)
			{
				texture = game->getTexture(ROULETTEANIM25);
			}
			else if (i == 26)
			{
				texture = game->getTexture(ROULETTEANIM26);
			}
			else if (i == 27)
			{
				texture = game->getTexture(ROULETTEANIM27);
			}
			else if (i == 28)
			{
				texture = game->getTexture(ROULETTEANIM28);
			}
			else if (i == 29)
			{
				texture = game->getTexture(ROULETTEANIM29);
			}
			else if (i == 30)
			{
				texture = game->getTexture(ROULETTEANIM30);
			}
			else if (i == 31)
			{
				texture = game->getTexture(ROULETTEANIM31);
			}
			else if (i == 32)
			{
				texture = game->getTexture(ROULETTEANIM32);
			}
			else if (i == 33)
			{
				texture = game->getTexture(ROULETTEANIM33);
			}
			else if (i == 34)
			{
				texture = game->getTexture(ROULETTEANIM34);
			}
			else if (i == 35)
			{
				texture = game->getTexture(ROULETTEANIM35);
			}
			else if (i == 36)
			{
				texture = game->getTexture(ROULETTEANIM36);
			}
			else if (i == 37)
			{
				texture = game->getTexture(ROULETTEANIM37);
			}
			else if (i == 38)
			{
				texture = game->getTexture(ROULETTEANIM38);
			}
			else if (i == 39)
			{
				texture = game->getTexture(ROULETTEANIM39);
			}
			else if (i == 40)
			{
				texture = game->getTexture(ROULETTEANIM40);
			}
			else if (i == 41)
			{
				texture = game->getTexture(ROULETTEANIM41);
			}
			else if (i == 42)
			{
				texture = game->getTexture(ROULETTEANIM42);
			}
			else if (i == 43)
			{
				texture = game->getTexture(ROULETTEANIM43);
			}
			else if (i == 44)
			{
				texture = game->getTexture(ROULETTEANIM44);
			}
			else if (i == 45)
			{
				texture = game->getTexture(ROULETTEANIM45);
			}
			else if (i == 46)
			{
				texture = game->getTexture(ROULETTEANIM46);
			}
			else if (i == 47)
			{
				texture = game->getTexture(ROULETTEANIM47);
			}
			else if (i == 48)
			{
				texture = game->getTexture(ROULETTEANIM48);
			}
			else {
				texture = game->getTexture(ROULETTEINSANITY);
			}
			i++;
			animTime = (float)SDL_GetTicks();
		}
	}
	else {
		texture = game->getTexture(ROULETTE);
	}
	rot += speed;
	if (rot > 360.0) rot -= 360.0;
	speed *= decelerate;
	if (speed < 0.1)
	{
		speed = 0;
	}
	if (started && speed == 0) {
		started = false;
		if (eco->getInsanity() > 0) {
			if (rot >= 0.0f && rot < 7.2f || rot >= 14.4f && rot < 18.0f
				|| rot >= 43.2f && rot < 50.4f || rot >= 100.8f && rot < 108.0f
				|| rot >= 165.6f && rot < 172.8f || rot >= 219.6f && rot < 226.8f
				|| rot >= 248.4f && rot < 255.6f || rot >= 298.8f && rot < 306.0f
				|| rot >= 334.8f && rot < 342.0f) {
				cout << "-10 ALMA ROJA" << endl;
				eco->addRedSouls(-10);
			}
			else if (rot >= 7.2f && rot < 14.4f || rot >= 18.0f && rot < 25.2f
				|| rot >= 32.4 && rot < 36.0f || rot >= 50.4f && rot < 57.6f
				|| rot >= 64.8f && rot < 72.0f || rot >= 93.6f && rot < 100.8f
				|| rot >= 122.4f && rot < 129.6f || rot >= 136.8f && rot < 144.0f
				|| rot >= 198.0f && rot < 205.2f
				|| rot >= 212.4f && rot < 219.6f || rot >= 241.2f && rot < 248.4f
				|| rot >= 270.0f && rot < 277.2f || rot >= 284.4f && rot < 291.6f
				|| rot >= 306.0f && rot < 313.2f || rot >= 320.4f && rot < 327.6f
				|| rot >= 342.0f && rot < 349.2f) {
				cout << "20 ALMA ROJA" << endl;
				eco->addRedSouls(20);
			}
			else if (rot >= 25.2f && rot < 32.4f || rot >= 57.6f && rot < 64.8f
				|| rot >= 79.2f && rot < 86.4f || rot >= 115.2f && rot < 122.4f
				|| rot >= 151.2f && rot < 158.4f || rot >= 187.2f && rot < 194.4f
				|| rot >= 226.8f && rot < 234.0f || rot >= 262.8f && rot < 270.0f
				|| rot >= 356.4f && rot <= 360.0f) {
				cout << "1 ALMA ROJA" << endl;
				eco->addRedSouls(1);
			}
			else if (rot >= 36.0f && rot < 43.2f || rot >= 72.0f && rot < 79.2f
				|| rot >= 86.4f && rot < 93.6f || rot >= 108.0f && rot < 115.2f
				|| rot >= 129.6f && rot < 136.8f || rot >= 144.0f && rot < 151.2f
				|| rot >= 158.4f && rot < 165.6f
				|| rot >= 194.4f && rot < 198.0f || rot >= 205.2f && rot < 212.4f
				|| rot >= 234.0 && rot < 241.2f || rot >= 255.6f && rot < 262.8f
				|| rot >= 277.2f && rot < 284.4f || rot >= 291.6f && rot < 298.8f
				|| rot >= 313.2f && rot < 320.4f || rot >= 327.6f && rot < 334.8f
				|| rot >= 349.2f && rot < 356.4f) {
				cout << "NADA" << endl;
			}
			else if (rot >= 180.0f && rot < 187.2f) {
				cout << "MUERTE" << endl;
			}
			else if (rot >= 172.8f && rot < 180.0f) {
				cout << "GUADAÑA" << endl;
			}
		}
		else {
			if (rot >= 0.0f && rot < 7.2f || rot >= 14.4f && rot < 18.0f
				|| rot >= 43.2f && rot < 50.4f || rot >= 100.8f && rot < 108.0f
				|| rot >= 165.6f && rot < 172.8f || rot >= 219.6f && rot < 226.8f
				|| rot >= 248.4f && rot < 255.6f || rot >= 298.8f && rot < 306.0f
				|| rot >= 334.8f && rot < 342.0f) {
				cout << "NADA" << endl;
			}
			else if (rot >= 7.2f && rot < 14.4f || rot >= 18.0f && rot < 25.2f
				|| rot >= 32.4 && rot < 36.0f || rot >= 50.4f && rot < 57.6f
				|| rot >= 64.8f && rot < 72.0f || rot >= 93.6f && rot < 100.8f
				|| rot >= 122.4f && rot < 129.6f || rot >= 136.8f && rot < 144.0f
				|| rot >= 172.8f && rot < 180.0f || rot >= 198.0f && rot < 205.2f
				|| rot >= 212.4f && rot < 219.6f || rot >= 241.2f && rot < 248.4f
				|| rot >= 270.0f && rot < 277.2f || rot >= 284.4f && rot < 291.6f
				|| rot >= 306.0f && rot < 313.2f || rot >= 320.4f && rot < 327.6f
				|| rot >= 342.0f && rot < 349.2f) {
				cout << "LOCURA" << endl;
				animTime =(float) SDL_GetTicks();
				i = 0;
				eco->setInsanity(5);
			}
			else if (rot >= 25.2f && rot < 32.4f || rot >= 57.6f && rot < 64.8f
				|| rot >= 79.2f && rot < 86.4f || rot >= 115.2f && rot < 122.4f
				|| rot >= 151.2f && rot < 158.4f || rot >= 187.2f && rot < 194.4f
				|| rot >= 226.8f && rot < 234.0f || rot >= 262.8f && rot < 270.0f
				|| rot >= 356.4f && rot <= 360.0f) {
				cout << "1 ALMA ROJA" << endl;
				eco->addRedSouls(1);
			}
			else if (rot >= 36.0f && rot < 43.2f || rot >= 72.0f && rot < 79.2f
				|| rot >= 86.4f && rot < 93.6f || rot >= 108.0f && rot < 115.2f
				|| rot >= 129.6f && rot < 136.8f || rot >= 144.0f && rot < 151.2f
				|| rot >= 158.4f && rot < 165.6f || rot >= 180.0f && rot < 187.2f
				|| rot >= 194.4f && rot < 198.0f || rot >= 205.2f && rot < 212.4f
				|| rot >= 234.0 && rot < 241.2f || rot >= 255.6f && rot < 262.8f
				|| rot >= 277.2f && rot < 284.4f || rot >= 291.6f && rot < 298.8f
				|| rot >= 313.2f && rot < 320.4f || rot >= 327.6f && rot < 334.8f
				|| rot >= 349.2f && rot < 356.4f) {
				cout << "4000 TOKEN" << endl;
				//game->push(new Award(game, gS, 1, 4000));
			}
		}
	}
}

void Roulette::addSpeed(int s) {
	if (speed == 0)
	{
		eco->addBlueSouls(-500);
		speed = s;
		started = true;
	}
}