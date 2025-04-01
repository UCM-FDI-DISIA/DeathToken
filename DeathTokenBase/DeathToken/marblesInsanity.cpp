#include "marblesInsanity.h"
#include "sdlUtils.h"

MarblesInsanity::MarblesInsanity(Game* game) : Marbles(game), texture(game->getTexture(MARBLESBACK)), mInsanity(true), gameFinish(false), dColor({ 0,0,0,0 }) {
	StartRoundTrickster();
	CMarbles.push_back(game->getTexture(REDMARBLE));
	CMarbles.push_back(game->getTexture(GREENMARBLE));
	CMarbles.push_back(game->getTexture(BLUEMARBLE));
	CMarbles.push_back(game->getTexture(YELLOWMARBLE));
	//Desctivar el render de Marbles y solo habilitar el del trilero hasta que se haga el juego del trilero y se le pase el color
	//Crear 3 botones en ellos solo habra uno con win el cual se le pasara el color a  --
	// llega el color y tengo que marbles::marbles render cambiarlo y desactivar los botones con ese color

	//OBS->> creo que lo suyo es que el color se guarde como {",",","} dependiendo de como toque
}

MarblesInsanity::~MarblesInsanity()
{
	for (auto btn : trileroButtons) {
		delete btn;
	}
}




void MarblesInsanity::render() const
{
	//texture->render();
	if (!mInsanity) {
		GameState::render();

		//Marbles::render();
		
	}
	else if(!gameFinish){
		//render del trilero
		texture->render();
		for (auto btn : trileroButtons) {
			btn->render();
			
		}
		
	}
	else {
		texture->render();

	}
}

void MarblesInsanity::update()
{
	GameState::update();

	static float elapsedTime = 0.0f;
	if (gameFinish) {
		float dt = SDLUtils::getDeltaTime();
		elapsedTime += dt;

		if (elapsedTime >= 3.0f) {
			mInsanity = false;
		}
	}
	else {
		for (auto btn : trileroButtons) {
			btn->update();

		}
	}
	
}

void MarblesInsanity::StartRoundTrickster()
{

	std::uniform_int_distribution<> distrib(0, 3);
	std::uniform_int_distribution<> posDistrib(0, 2);
	posColor = posDistrib(game->getGen());
	dColor = { 0,0,0,0 };
	dColor[distrib(game->getGen())] = 1;
	createTricksterButtons();
	
	//Juego del trilero

	/*bool acertado = true;
	if (acertado) {
		//discardMarble(color);
		mInsanity = false;
	}*/
	
}



void MarblesInsanity::createTricksterButtons()
{
	trileroButtons.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> marbleColor = { 0, 0, 0, 0 };
		if (i ==posColor) {
			marbleColor = dColor;
			createButtonT(Game::WIN_WIDTH / 4 * i, Game::WIN_HEIGHT / 2, (int)(124.0 / 1920.0 * Game::WIN_WIDTH), (int)(124.0 / 1920.0 * Game::WIN_HEIGHT),
				game->getTexture(CANICASBUT), game->getTexture(CANICASBUT), true, marbleColor);
		}
		else {
			createButtonT(Game::WIN_WIDTH / 4 * i, Game::WIN_HEIGHT / 2, (int)(124.0 / 1920.0 * Game::WIN_WIDTH), (int)(124.0 / 1920.0 * Game::WIN_HEIGHT),
				game->getTexture(CANICASBUT), game->getTexture(CANICASBUT), false, marbleColor);
			

		}
		
			
	}
}

void MarblesInsanity::createButtonT(int x, int y, int widht, int height, Texture* texture, Texture* textureC, bool marble, std::vector<int> marbleColor)
{
	ButtonMarblesInsanity* btnTrickster = new ButtonMarblesInsanity(this, x, y, widht, height, texture, textureC, marble, marbleColor);
	trileroButtons.push_back(btnTrickster);
	addEventListener(btnTrickster);
	btnTrickster->connect([this,x,y,widht,height,marble,marbleColor]() { discardMarble(x,y, widht, height,marble,marbleColor); });

}

void MarblesInsanity::discardMarble(int x,int y,int widht,int height, bool marble,std::vector<int> color)
{
	if (marble) {
		SDL_Rect box;
		box.x = x;
		box.y = y;
		box.w = widht;
		box.h = height;
		for (int i= 0; i < color.size(); i++) {
			if (color[i] == 1) {
				CMarbles[i]->render(box);
			}
		}
		
		gameFinish = true;
	}
	else {
		//Has perdido
		gameFinish = true;
	}
	//mostar posicion de la canica
}


