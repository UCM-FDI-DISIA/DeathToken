#include "marblesInsanity.h"
#include "SoundManager.h"
#include "sdlUtils.h"
#include "ui.h"
#include "game.h"	

MarblesInsanity::MarblesInsanity(Game* game) : GameState(game),  texture(game->getTexture(MARBLESBACK)), gameFinish(false), dColor({ 0,0,0,0 }) {
	CMarbles.push_back(game->getTexture(REDMARBLEREAL));
	CMarbles.push_back(game->getTexture(GREENMARBLEREAL));
	CMarbles.push_back(game->getTexture(BLUEMARBLEREAL));
	CMarbles.push_back(game->getTexture(YELLOWMARBLEREAL));
	auto& soundManager = SoundManager::obtenerInstancia();
	soundManager.reproducirMusica("CanicasDT");
	uiI = new UIMarblesInsanity(this, game, this);
	guideText = new Text(this, this->getGame()->getTypo(GRAND_CASINO1), Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 2,
						(int)(3.0f / 1920.0f * Game::WIN_WIDTH), Text::CENTRO);
	guideText->setMessage("Pulsa en GO para empezar ronda con locura");
	addObjectsUI(guideText);
	wMarbleI = -1;
	wMarble = { 0,0,0,0 };
	wMarbleShow = false;
	gameFinish = false;
	posColor = -1;

	hud = new HUDBet(this, false);
}

MarblesInsanity::~MarblesInsanity()
{
	for (auto btn : trileroButtons) {
		delete btn;
	}
	HUDManager::popGame();
	delete uiI;
	uiI = nullptr;
}

void MarblesInsanity::render() const
{
	if (!gameFinish) {
		//render del trilero
		texture->render();
		for (auto btn : trileroButtons) {
			btn->render();

		}
		uiI->render();
	}
	else {
		texture->render();
		CMarbles[wMarbleI]->render(wMarble);
		for (auto btn : trileroButtons) {
			btn->render();

		}
		uiI->render();
	}
	hud->render();
	guideText->render();
}

void MarblesInsanity::update()
{
	static float elapsedTime = 0.0f;
	static int height = 0;

	int maxHeight = -100;

	if (gameFinish) {
		float dt = SDLUtils::getDeltaTime();
		elapsedTime += dt;

		if (elapsedTime >= 4.0f) {
			elapsedTime = 0.0f;
			game->pop();
			game->push(new Marbles(game,dColor, true));
		}
		else
		{
			if (height > maxHeight)
			{
				int aux = (int)(dt * -100);
				for (auto i : trileroButtons)
				{
					i->movePos(0, aux);
				}
				height += aux;

			}
			
		}
	}
	else {
		elapsedTime = 0.0f;
		height = 0;
		for (auto btn : trileroButtons) {
			btn->update();

		}
		uiI->update();
	}
	
}

void MarblesInsanity::StartRoundTrickster()
{
	guideText->setMessage(" ");
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
			createButtonT((Game::WIN_WIDTH / 4 * i)+ (int)(300.0 / 1920.0 * Game::WIN_WIDTH), (int)(400.0 / 1080.0 * Game::WIN_HEIGHT), (int)(211.0 / 1920.0 * Game::WIN_WIDTH), (int)(212.0 / 1080.0 * Game::WIN_HEIGHT),
				game->getTexture(CUP), game->getTexture(CUP), true, marbleColor);
		}
		else {
			
			createButtonT((Game::WIN_WIDTH / 4 * i) + (int)(300.0 / 1920.0 * Game::WIN_WIDTH), (int)(400.0 / 1080.0 * Game::WIN_HEIGHT), (int)(211.0 / 1920.0 * Game::WIN_WIDTH), (int)(212.0 / 1080.0 * Game::WIN_HEIGHT),
				game->getTexture(CUP), game->getTexture(CUP), false, marbleColor);
		}
	}
}

void MarblesInsanity::createButtonT(int x, int y, int width, int height, Texture* texture, Texture* textureC, bool marble, std::vector<int> marbleColor)
{
	ButtonMarblesInsanity* btnTrickster = new ButtonMarblesInsanity(this, x, y, width, height, texture, textureC, marble, marbleColor);
	trileroButtons.push_back(btnTrickster);
	addEventListener(btnTrickster);
	btnTrickster->connect([this,x,y,width,height,marble,marbleColor]() { discardMarble(marble); });
	if (marble)
	{
		wMarble.x = x + (int)(52.0 / 1920.0 * Game::WIN_WIDTH);
		wMarble.y = y + (int)(95.0 / 1080.0 * Game::WIN_HEIGHT);
		wMarble.w = (int)(107.0 / 1920.0 * Game::WIN_WIDTH);
		wMarble.h = (int)(107.0 / 1080.0 * Game::WIN_HEIGHT);
		for (int i = 0; i < marbleColor.size(); i++) {
			if (marbleColor[i] == 1) {
				wMarbleI = i;
			}
		}
	}

}

void MarblesInsanity::discardMarble(bool marble)
{
	if (!marble) {
		dColor = { 0,0,0,0 };
	}
	gameFinish = true;
}


