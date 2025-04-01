#include "marblesInsanity.h"

MarblesInsanity::MarblesInsanity(Game* game) : Marbles(game), texture(game->getTexture(MARBLESBACK)), mInsanity(true), dColor({ 0,0,0,0 }) {
	hud = new HUDBet(this);
	StartRoundTrickster();

	//Desctivar el render de Marbles y solo habilitar el del trilero hasta que se haga el juego del trilero y se le pase el color
	//Crear 3 botones en ellos solo habra uno con win el cual se le pasara el color a  --
	// llega el color y tengo que marbles::marbles render cambiarlo y desactivar los botones con ese color

	//OBS->> creo que lo suyo es que el color se guarde como {",",","} dependiendo de como toque
}

MarblesInsanity::~MarblesInsanity()
{
}




void MarblesInsanity::render() const
{
	texture->render();
	if (!mInsanity) {

		Marbles::render();
		for (int i = 0; i < 4; i++) {
			if (dColor[i]) {

			}
		}
	}
	else {
		//render del trilero
		for (auto btn : trileroButtons) {
			btn->render();
		}
		
	}
}

void MarblesInsanity::update()
{
	GameState::update();
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

void MarblesInsanity::discardMarble(int color)
{
	//mostar posicion de la canica
}

void MarblesInsanity::createTricksterButtons()
{
	trileroButtons.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> marbleColor = { 0, 0, 0, 0 };
		if (i ==posColor) {
			marbleColor = dColor;
		}
		else {
			std::uniform_int_distribution<> distrib(0, 3);

			marbleColor[distrib(game->getGen())] = 1;
		}
		
			ButtonMarblesInsanity*  btnTrickster =  new ButtonMarblesInsanity(this,
			Game::WIN_WIDTH / 4 * i, Game::WIN_HEIGHT / 6, (int)(124.0 / 1920.0 * Game::WIN_WIDTH), (int)(124.0 / 1920.0 * Game::WIN_HEIGHT),
				game->getTexture(CANICASBUT), game->getTexture(CANICASBUT), true, marbleColor);
			trileroButtons.push_back(btnTrickster);
			addObjects(btnTrickster);
			addEventListener(btnTrickster);
			//btnTrickster->connect([]() { discardMarble() };
	}
}



