#include "marblesInsanity.h"
#include "sdlUtils.h"
#include "UI.h"
#include "Game.h"	

MarblesInsanity::MarblesInsanity(Game* game) : GameState(game),  texture(game->getTexture(MARBLESBACK)), gameFinish(false), dColor({ 0,0,0,0 }) {
	CMarbles.push_back(game->getTexture(REDMARBLE));
	CMarbles.push_back(game->getTexture(GREENMARBLE));
	CMarbles.push_back(game->getTexture(BLUEMARBLE));
	CMarbles.push_back(game->getTexture(YELLOWMARBLE));
	uiI = new UIMarblesInsanity(this, game, this);
	wMarbleI = -1;
	wMarble = { 0,0,0,0 };
	wMarbleShow = false;
	gameFinish = false;
	posColor = -1;
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

	if(!gameFinish){
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
	static float elapsedTime = 0.0f;

	if (gameFinish) {
		float dt = SDLUtils::getDeltaTime();
		elapsedTime += dt;

		if (elapsedTime >= 3.0f) {
			elapsedTime = 0.0f;
			game->pop();
			game->push(new Marbles(game,dColor));
		}
	}
	else {
		elapsedTime = 0.0f;
		for (auto btn : trileroButtons) {
			btn->update();

		}
		uiI->update();
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
	
	
}



void MarblesInsanity::createTricksterButtons()
{
	trileroButtons.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> marbleColor = { 0, 0, 0, 0 };
		if (i ==posColor) {
			marbleColor = dColor;
			createButtonT((Game::WIN_WIDTH / 4 * i)+ (int)(300.0 / 1920.0 * Game::WIN_WIDTH), Game::WIN_HEIGHT / 2, (int)(211.0 / 1920.0 * Game::WIN_WIDTH), (int)(212.0 / 1080.0 * Game::WIN_HEIGHT),
				game->getTexture(CUP), game->getTexture(CUP), true, marbleColor);
		}
		else {
			
			createButtonT((Game::WIN_WIDTH / 4 * i) + (int)(300.0 / 1920.0 * Game::WIN_WIDTH), Game::WIN_HEIGHT / 2, (int)(211.0 / 1920.0 * Game::WIN_WIDTH), (int)(212.0 / 1080.0 * Game::WIN_HEIGHT),
				game->getTexture(CUP), game->getTexture(CUP), false, marbleColor);
			

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
		gameFinish = true;
	}
	else {
		dColor = { 0,0,0,0 };
		gameFinish = true;
	}
	
}


