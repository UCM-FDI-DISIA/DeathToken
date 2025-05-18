#include "marbles.h"
#include "marblesInsanity.h"
#include "SoundManager.h"
#include "game.h"
#include "sdlUtils.h"

Marbles::Marbles(Game* game, std::vector<int> blockedMarble, bool insanity) : GameState(game),blockedMarble(blockedMarble), texture(game->getTexture(MARBLESBACK)),
	marbles({ 0,0,0,0 }),
	RMarbles({ game->getTexture(REDMARBLEREAL),game->getTexture(GREENMARBLEREAL),
	game->getTexture(BLUEMARBLEREAL),
	game->getTexture(YELLOWMARBLEREAL) }),
	tube(game->getTexture(MARBLESTUBE)),
	slot(game->getTexture(MARBLESLOT)),
	insanity (insanity)
{
	tubeRect = SDL_Rect((int)(584.0f / 1920.0f * Game::WIN_WIDTH), (int)(-155.0f / 1080.0f * Game::WIN_HEIGHT),
						(int)(150.0f / 1920.0f * Game::WIN_WIDTH), (int)(155.0f / 1080.0f * Game::WIN_HEIGHT));
	auto& soundManager = SoundManager::obtenerInstancia();
	soundManager.reproducirMusica("CanicasDT");
	for (int i = 0; i < 3; i++)
	{
		slotRects[i] = SDL_Rect((int)(593.0f + (300 * i) / 1920.0f * Game::WIN_WIDTH), (int)(235.0f / 1080.0f * Game::WIN_HEIGHT),
								(int)(132.0f / 1920.0f * Game::WIN_WIDTH), (int)(82.0f / 1080.0f * Game::WIN_HEIGHT));
	}
	ui = new UIMarbles(this, game, this);
	Marbles::marblesButtonCreation();
	hud = new HUDBet(this, false);
}

Marbles::~Marbles() {
	
	delete ui;
	HUDManager::popGame();
}

void  Marbles::generateMarbles() {
	//En un vector voy metiendo aleatoriamente +1, representando ROJO/VERDE/AZUL/AMARILLO
	tubeRect = SDL_Rect((int)(584.0f / 1920.0f * Game::WIN_WIDTH), (int)(-155.0f / 1080.0f * Game::WIN_HEIGHT),
		(int)(150.0f / 1920.0f * Game::WIN_WIDTH), (int)(155.0f / 1080.0f * Game::WIN_HEIGHT));
	animPhase = 1;
	marbles = { 0,0,0,0 };
	drawnMarbles.clear();

	std::vector<int> validColors;

	for (int i = 0; i < blockedMarble.size(); i++) {
		if (blockedMarble[i] == 0) {
			validColors.push_back(i);
		}
	}

	int pos = 1;

	std::uniform_int_distribution<>distrib(0,(int) validColors.size() - 1);

	for (int i = 0; i < 3; i++) {
		int color = validColors[distrib(game->getGen())];

		marbleRects[i] = SDL_Rect((int)(606.0f + (300 * i) / 1920.0f * Game::WIN_WIDTH), (int)(75.0f / 1080.0f * Game::WIN_HEIGHT),
								  (int)(107.0f / 1920.0f * Game::WIN_WIDTH), (int)(107.0f / 1080.0f * Game::WIN_HEIGHT));
		marbles[color]++;
		
		drawnMarbles.push_back({ RMarbles[color], marbleRects[i]});
		pos++;
	}
	pos = 0;
	ui->setOnBet(true);
}
void Marbles::marblesAnim()
{
	if (ui->getOnBet())
	{
		float dt = SDLUtils::getDeltaTime();
		switch (animPhase)
		{
		case 1:
		{
			static int height = 0;

			int maxHeight = 150;

			if (height < maxHeight)
			{
				int aux = 350 * dt;
				tubeRect.y += aux;
				height += aux;
			}
			else {
				height = 0;
				tubeRect.y = (int)(-5.0f / 1080.0f * Game::WIN_HEIGHT);
				animPhase++;
			}
		}
		break;
		case 2:
		{
			static int height = 0;

			int maxHeight = 100;

			if (height < maxHeight)
			{
				int aux = 300 * dt;
				marbleRects[0].y += aux;
				height += aux;
			}
			else {
				height = 0;
				marbleRects[0].y = (int)(175.0f / 1080.0f * Game::WIN_HEIGHT);
				animPhase++;
			}
		}
			break;
		case 3:
		{
			static int move = 0;

			int maxMove = 300;

			if (move < maxMove)
			{
				int aux = 350 * dt;
				tubeRect.x += aux;
				move += aux;
			}
			else {
				move = 0;
				(int)((593.0f + (300 * 1)) / 1920.0f * Game::WIN_WIDTH);
				animPhase++;
			}
		}
			break;
		case 4:
		{
			static int height = 0;

			int maxHeight = 100;

			if (height < maxHeight)
			{
				int aux = 300 * dt;
				marbleRects[1].y += aux;
				height += aux;
			}
			else {
				height = 0;
				marbleRects[1].y = (int)(175.0f / 1080.0f * Game::WIN_HEIGHT);
				animPhase++;
			}
		}
			break;
		case 5:
		{
			static int move = 0;

			int maxMove = 300;

			if (move < maxMove)
			{
				int aux = 350 * dt;
				tubeRect.x += aux;
				move += aux;
			}
			else {
				move = 0;
				tubeRect.x = (int)((593.0f + (300 * 2)) / 1920.0f * Game::WIN_WIDTH);
				animPhase++;
			}
		}
			break;
		case 6:
		{
			static int height = 0;

			int maxHeight = 100;

			if (height < maxHeight)
			{
				int aux = 300 * dt;
				marbleRects[2].y += aux;
				height += aux;
			}
			else {
				height = 0;
				marbleRects[2].y = (int)(175.0f / 1080.0f * Game::WIN_HEIGHT);
				animPhase++;
			}
		}
			break;
		case 7:
		{
			static int height = 0;

			int maxHeight = -155;

			if (height > maxHeight)
			{
				int aux = -350 * dt;
				tubeRect.y += aux;
				height += aux;
			}
			else {
				height = 0;
				betManagement();
				ui->setOnBet(false);
			}
		}
			break;
		default:
			break;
		}
	}
}
void Marbles::betManagement()
{
	long long moneyWin = checkBets();//Comparar canicas con apuesta
	//Segun la apuesta porX al dinero metido

	if (moneyWin > 0) {
		game->push(new Award(game, (GameState*)this, turnMoneyBet, moneyWin, insanity));
	}
	else {
		PlayerEconomy::setBet(0);
		hud->refresh();
	}

	blockedMarble = { 0,0,0,0 };
	betsHistory = bets;
	clearBetsHistory();
	betDone = true;
}
int  Marbles::checkBets() {
	int moneyWin = 0;
	turnMoneyBet = 0;

	//Cuando se hagan los botones cada apuesta hecha se metera en un map indicando que apuesta 
	//hecha en un vector y el multi que da si gana

	for (const auto& [key, typeBet] : bets) { //Recorremos el mapa
		bool won = true;
		bool wonTriple = false;

		if (typeBet.typeOfBet == std::vector<int>{3, 3, 3, 3}) {// Si apuesta a cualquier triple
			for (int i = 0; i < typeBet.typeOfBet.size(); i++) { //recorremos el vector de la apuesta hecha
				if (marbles[i] == 3) {// si has salido 3 canicas del mismo color entra en true
					wonTriple = true;
					break;
				}
			}
		}


		for (int i = 0; i < typeBet.typeOfBet.size(); i++) {
			if (marbles[i] < typeBet.typeOfBet[i]) {//Si hay  mas canicas apostadas que canicas sacadas, le jugador pierde
				won = false;
				break;
			}
		}
		
		if (won|| wonTriple) {
			moneyWin += (int) typeBet.moneyBet * typeBet.multiplier;
		}
		turnMoneyBet += typeBet.moneyBet;
	}

	return moneyWin;
}

void Marbles::startRound() {
	generateMarbles();//Se generar las canicas aleatorias
}
void Marbles::update() {
	GameState::update();
	
	if (betDone && insanity)
	{
		if (PlayerEconomy::getInsanity() > 0)
		{
			render();
			SDL_RenderPresent(game->getRenderer());
			SDL_Delay(2000);
			game->pop();
			game->push(new MarblesInsanity(game));
		}
		else
		{
			render();
			SDL_RenderPresent(game->getRenderer());
			SDL_Delay(2000);
			game->pop();
			game->push(new Marbles(game, {0, 0, 0, 0}, false));
		}
	}
	marblesAnim();
	
}

void Marbles::render() const {
	texture->render();
	GameState::render();
	for (int i = 0; i < (animPhase / 2); i++) {
		drawnMarbles[i].first->render(drawnMarbles[i].second);
	}
	for (int i = 0; i < 3; i++)
	{
		slot->render(slotRects[i]);
	}
	tube->render(tubeRect);

}
void  Marbles::marblesButtonCreation() {

	//Botones cuadrados para las apuestas de 1 color / BUTTONMARBLES1
	
	//ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1 - marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - 2 * marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 1,0,0,0 });
	//VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1 - marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,1,0,0 });
	//AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - 2 * marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,0,1,0 });
	//AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW1), (int)(PosPH1), game->getTexture(BUTTONMARBLES1), game->getTexture(BUTTONMARBLES1CLCK), 1, { 0,0,0,1 });
	
	//Botones rectangulares para las apuestas de 2 colores /BUTTONMARBLES2

	//ROJO/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 3 * PosPW2 - PosPW1 - 4 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,1,0,0 });
	//ROJO/ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 2,0,0,0 });
	//VERDE/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW2 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,2,0,0 });
	//ROJO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,0,0,1 });
	//VERDE/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW2 - PosPW1 - 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,1,1,0 });
	//ROJO/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 1,0,1,0 });
	//VERDE/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,1,0,1 });
	//AZUL/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH2 - 2 * marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,2,0 });
	//AMARILLO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW2 + PosPW1 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,0,2 });
	//AMARILLO/AZUL	
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + 2 * PosPW2 + PosPW1 + 4 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH2 - PosPH2 - marginH), (int)(PosPW2), (int)(PosPH2), game->getTexture(BUTTONMARBLES2), game->getTexture(BUTTONMARBLES2CLCK), 2, { 0,0,1,1 });
	
	//Botones rectangulares para las apuestas individuales de 3 mismos colores /	BUTTONMARBLES
	
	//ROJO/ROJO/ROJO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - 2 * PosPW3 - PosPW1 - 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH), (int)(PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 3,0,0,0 });
	//VERDE/VERDE/VERDE
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW3 - PosPW1 - 2 * marginW),(int)( Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH),(int)( PosPW3),(int)( PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,3,0,0 });
	//AZUL/AZUL/AZUL
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW1 + 2 * marginW),(int)( Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH),(int)( PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,0,3,0 });
	//AMARILLO/AMARILLO/AMARILLO
	createMarbleButton((int)(Game::WIN_WIDTH / 2 + PosPW3 + PosPW4 / 2 + 3 * marginW), (int)(Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - 2 * PosPH1 - (PosPH4 - PosPH4 / 4) - 3 * marginH), (int)(PosPW3), (int)(PosPH3), game->getTexture(BUTTONMARBLES3), game->getTexture(BUTTONMARBLES3CLCK), 3, { 0,0,0,3 });
	
	//Boton cuadrado para la apuesta de todos los posibles combianciones de tres mismos colores / BUTTONMAARBLES4
	
	createMarbleButton((int)(Game::WIN_WIDTH / 2 - PosPW1),(int) (Game::WIN_HEIGHT - Game::WIN_HEIGHT / 4 - PosPH1 - PosPH1 - PosPH4 - 3 * marginH),(int) PosPW4, (int)PosPH4, game->getTexture(BUTTONMARBLES4), game->getTexture(BUTTONMARBLES4CLCK), 4, { 3,3,3,3 });
}

void
Marbles::createMarbleButton(int x, int y, int width, int height, Texture* texture, Texture* textureC, int type, std::vector<int> NCMarbles) {
	
	int multiplier = 0;


	switch (type) {
	case 1:
		multiplier = 2;
		break;
	case 2:
	case 4:
		multiplier = 5;
		break;
	case 3:
		multiplier = 20;
		break;
	}
	bool bloqueado = false;
	for (int i = 0; i < NCMarbles.size(); i++) {
		if (NCMarbles[i] > 0 && blockedMarble[i] == 1) {
			bloqueado = true;
			break;
		}
	}

	if (!bloqueado) {
		ButtonMarbles* btnMarbles = new ButtonMarbles(this, game, ui, x, y, width, height, texture, textureC, type, NCMarbles);
		marbleButtons.push_back(btnMarbles);
		addObjects(marbleButtons.back());
		addEventListener(marbleButtons.back());
		btnMarbles->connect([this, NCMarbles, multiplier, btnMarbles]() {
			if(!ui->getOnBet())
				newBet(NCMarbles, multiplier, moneyBet, btnMarbles);
			});
	}
	
}

void Marbles::newBet(std::vector<int> typeOfBet, int multiplier, long long moneyBet, ButtonMarbles* btnMarbles) {
	
	moneyBet = ui->currentChipValue();

	bets[clave] = { typeOfBet, multiplier, moneyBet };
	clave++;

}

void Marbles::clearBets() {
	bets.clear();
	for (auto i : marbleButtons)
	{
		i->clear();
	}
}

void Marbles::clearBetsHistory()
{
	bets.clear();
	for (auto i : marbleButtons)
	{
		i->setBetHistory(i->getBet());
		i->clear();
	}
}

void Marbles::repeat()
{
	bets = betsHistory;
	for (auto i : marbleButtons)
	{
		i->repeat();
	}
	hud->refresh();
}

void Marbles::setBlockedMarble(std::vector<int> blocked)
{
	blockedMarble = blocked;
}
