#include "marblesInsanity.h"
#include "sdlUtils.h"
#include "UI.h"


MarblesInsanity::MarblesInsanity(Game* game) : Marbles(game), texture(game->getTexture(MARBLESBACK)), mInsanity(true), gameFinish(false), dColor({ 0,0,0,0 }) {
	CMarbles.push_back(game->getTexture(REDMARBLE));
	CMarbles.push_back(game->getTexture(GREENMARBLE));
	CMarbles.push_back(game->getTexture(BLUEMARBLE));
	CMarbles.push_back(game->getTexture(YELLOWMARBLE));
	uiI = new UIMarblesInsanity(this, game, this);

	//StartRoundTrickster();
}

MarblesInsanity::~MarblesInsanity()
{
	for (auto btn : trileroButtons) {
		delete btn;
	}
	delete uiI;
}

void MarblesInsanity::render() const
{

	//texture->render();
	if (!mInsanity) {
		Marbles::render();
		
	}
	else if(!gameFinish){
		//render del trilero
		texture->render();
		for (auto btn : trileroButtons) {
			btn->render();
			
		}
		uiI->render();
	}
	else {

	texture->render();
	if (wMarbleShow) {
		CMarbles[wMarbleI]->render(wMarble);
	}
	}
}

void MarblesInsanity::update()
{
	if (!mInsanity) {
		Marbles::update();

	}
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
		uiI->update();
	}
	
}

void MarblesInsanity::StartRoundTrickster()
{
	Marbles::setbInsanity(true);
	wMarbleI = -1;
	wMarble = {0,0,0,0};
	wMarbleShow = false;
	gameFinish = false;
	mInsanity = true;
	std::uniform_int_distribution<> distrib(0, 3);
	std::uniform_int_distribution<> posDistrib(0, 2);
	posColor = posDistrib(game->getGen());
	dColor = { 0,0,0,0 };
	dColor[distrib(game->getGen())] = 1;
	createTricksterButtons();
	
	
}



void MarblesInsanity::createTricksterButtons()
{
	trileroButtons.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> marbleColor = { 0, 0, 0, 0 };
		if (i ==posColor) {
			marbleColor = dColor;
			createButtonT((Game::WIN_WIDTH / 4 * i)+ (int)(300.0 / 1920.0 * Game::WIN_WIDTH), Game::WIN_HEIGHT / 2, (int)(124.0 / 1920.0 * Game::WIN_WIDTH), (int)(124.0 / 1920.0 * Game::WIN_HEIGHT),
				game->getTexture(CANICASBUT), game->getTexture(CANICASBUT), true, marbleColor);
		}
		else {
			
			createButtonT((Game::WIN_WIDTH / 4 * i) + (int)(300.0 / 1920.0 * Game::WIN_WIDTH), Game::WIN_HEIGHT / 2, (int)(124.0 / 1920.0 * Game::WIN_WIDTH), (int)(124.0 / 1920.0 * Game::WIN_HEIGHT),
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
		wMarbleShow = true;
		wMarble.x = x;
		wMarble.y = y;
		wMarble.w = widht;
		wMarble.h = height;
		for (int i= 0; i < color.size(); i++) {
			if (color[i] == 1) {
				wMarbleI = i;
			}
		}
		Marbles::setBlockedMarble(color);
		gameFinish = true;
	}
	else {
		
		gameFinish = true;
	}
	
}


