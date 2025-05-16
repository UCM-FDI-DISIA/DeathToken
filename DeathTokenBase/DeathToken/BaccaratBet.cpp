#include "baccaratBet.h"
#include "SDLUtils.h"

BaccaratBet::BaccaratBet(Game* game) : Baccarat(game, true), intro(game->getTexture(BET)) {
	btnBaccarattie = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 + 10, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8);
	bacButtons.push_back(btnBaccarattie);
	addObjects(bacButtons.back());
	addEventListener(bacButtons.back());
	btnBaccarattie->connect([this]() {
		if (!betOnPlayer && !betOnBanker)
		{
			newBet(8, 0, btnBaccarattie); betOnTie = true;
			btnBaccaratbanker->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccaratplayer->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });

		btnBaccaratbanker = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 6);
		bacButtons.push_back(btnBaccaratbanker);
		addObjects(bacButtons.back());
		addEventListener(bacButtons.back());
		btnBaccaratbanker->connect([this]() { if (!betOnPlayer && !betOnTie) {
			newBet(2, 1, btnBaccaratbanker); betOnBanker = true;
			btnBaccarattie->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccaratplayer->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });

		btnBaccaratplayer = new ButtonBaccarat(this, game, ui, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200, Game::WIN_WIDTH / 4 - 30, Game::WIN_HEIGHT / 8);
		bacButtons.push_back(btnBaccaratplayer);
		addObjects(bacButtons.back());
		addEventListener(bacButtons.back());
		btnBaccaratplayer->connect([this]() { if (!betOnTie && !betOnBanker) {
			newBet(2, 2, btnBaccaratplayer); betOnPlayer = true;
			btnBaccaratbanker->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
			btnBaccarattie->setPos(-Game::WIN_WIDTH, -Game::WIN_HEIGHT);
		} });
}

void BaccaratBet::repeatBet() {
		for (int i = 0; i < betsHistory.size(); i++)
			bets[i] = { betsHistory[i].multiplier * 2, betsHistory[i].moneyBet * betsHistory[i].multiplier, betsHistory[i].betType };
		int currentBet = 0;
		for (int i = 0; i < bets.size(); i++) {
			currentBet += bets[i].moneyBet;
		}
		for (auto i : bacButtons)
		{
			i->repeatDoubleBet();
		}
		HUDManager::applyBet(currentBet);

		startRound();

		if (!hasWon) {
			didntWin();
		}
}

void BaccaratBet::didntWin() {
	buttonsOn = false;
	for (int i = 0; i < betsHistory.size(); i++) {
		if (betsHistory[i].betType == 0) {
			betsHistory[i].multiplier = 8;
		}
		else {
			betsHistory[i].multiplier = 2;
		}
	}
}

void BaccaratBet::startRound()
{
	if (!animOn)
	{
		Baccarat::startRound();
	}
}

void BaccaratBet::acumulate() {
	if (!buttonsOn) {
		int xBut = (int)(Game::WIN_WIDTH * 7.07 / 8), yBut = (int)(Game::WIN_HEIGHT * 4.5 / 7), wBut = (int)Game::WIN_WIDTH / 18, hBut = (int)Game::WIN_WIDTH / 18;
		bet = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(TICK));
		addObjects(bet);
		addEventListener(bet);
		bet->connect([this]() { repeatBet(); });
		yBut = (int)(Game::WIN_HEIGHT * 4.5 / 9);
		stop = new Button(this, xBut, yBut, wBut, hBut, game->getTexture(CROSS));
		addObjects(stop);
		addEventListener(stop);
		stop->connect([this]() { didntWin(); });
	}
}

void BaccaratBet::update() {
	if (mat.player.size() == 0 && mat.player.size() == 0)
		GameState::update();
	if (cardAnim && SDL_GetTicks() - animTime > 75.0f && frame < 9)
	{
		frame++;
		animTime = SDL_GetTicks();
		if (frame == 7) {
			if (animInCard == 0)
			{
				player1->frame = mat.player[0];
				if (mat.player[0] > 9)
					ctFrame = 0;
				else
					ctFrame = mat.player[0];
			}
			else if (animInCard == 1)
			{
				banker1->frame = mat.banker[0];
				if (mat.banker[0] > 9)
					ctFrameB = 0;
				else
					ctFrameB = mat.banker[0];
			}
			else if (animInCard == 2)
			{
				player2->frame = mat.player[1];
				if (mat.player[1] <= 9)
				{
					ctFrame += mat.player[1];
					ctFrame = ctFrame % 10;
				}
			}
			else if (animInCard == 3)
			{
				banker2->frame = mat.banker[1];
				if (mat.banker[1] <= 9)
				{
					ctFrameB += mat.banker[1];
					ctFrameB = ctFrameB % 10;
				}
			}
		}
		if (frame == 9 && animInCard < 3) {
			frame = 0;
			if (animInCard == 0)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
			else if (animInCard == 1)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
			else if (animInCard == 2)
			{
				animInCard++;
				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
			}
		}
	}
	if (frame == 9) {
		handThird();//reparte tercera
		cardAnim = false;
		frame = 0;
		animInCard = 0;
		sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
	}
	if (thirdPlayerMove) {
		player3->setPos(player3->position() - Vector2D(5, 0));
		if (player3->position().getX() <= (int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81))
		{
			thirdPlayerMove = false;
			if (mat.player[2] <= 9)
			{
				ctFrame += mat.player[2];
				ctFrame = ctFrame % 10;
			}
			goForWin = true;
		}
	}
	if (thirdBankerMove) {
		banker3->setPos(banker3->position() + Vector2D(5, 0));
		if (banker3->position().getX() >= (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5))
		{
			thirdBankerMove = false;
			if (mat.banker[2] <= 9)
			{
				ctFrameB += mat.banker[2];
				ctFrameB = ctFrameB % 10;
			}
			goForWin = true;
		}
	}
	if (goForWin)
	{
		btnBaccaratbanker->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 15);
		btnBaccarattie->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 3 + 10);
		btnBaccaratplayer->setPos(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 8, Game::WIN_HEIGHT / 2 + 200);
		betOnPlayer = false;
		betOnBanker = false;
		betOnTie = false;
		win();
		goForWin = false;
	}
	if (bet != nullptr && stop != nullptr && !buttonsOn) {
		bet = nullptr;
		stop = nullptr;
		eventHandlers.pop_back();
		eventHandlers.pop_back();
		gameObjects.pop_back();
		gameObjects.pop_back();
	}
	title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
	if (width < Game::WIN_WIDTH && height < Game::WIN_HEIGHT && animOn) {
		width += Game::WIN_WIDTH / 50;
		height += Game::WIN_HEIGHT / 50;

	}
	else {
		float dt = SDLUtils::getDeltaTime();
		time += dt;
		if (time - actual > 1)
		{
			animOn = false;
			width = 0;
			height = 0;
		}
	}
	if (timeForWin) {
		float dt = SDLUtils::getDeltaTime();
		tiempo += dt;
		if (tiempo > 3)
		{
			if (hasWon) {
				acumulate();
				buttonsOn = true;
				hasWon = false;
			}
			timeForWin = false;
			tiempo = 0;
			playerBet = false;
			bankerBet = false;
			tieBet = false;
			player1->frame = 0;
			player2->frame = 0;
			banker1->frame = 0;
			banker2->frame = 0;
			banker3->frame = 14;
			player3->frame = 14;
			ctFrame = 14;
			ctFrameB = 14;
			clearDeck();
		}
	}
}

void BaccaratBet::render() const
{
	Baccarat::render();
	if (animOn)
	{
		SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
		SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
		SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
		SDL_RenderFillRect(game->getRenderer(), &black);
		intro->render(title);
	}
}


//BACCARAT FLIP CON TIMER Y NUMEROS
//#include "BaccaratFlip.h"
//#include "sdlUtils.h"
//
//BaccaratFlip::BaccaratFlip(Game* game) : Baccarat(game), text(game->getTexture(FLIPCARD)), intro(game->getTexture(FLIP)) {
//	addCards();
//
//}
//
////anade las tres cartas extra
//void BaccaratFlip::addCards()
//{
//	Baccarat::addCards();
//	extra1 = createCard(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14); // frame 14 = invisible
//	extra2 = createCard(Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14);
//	extra3 = createCard(Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3, 0, 14);//a
//}
////crea las tres cartas extra
//void BaccaratFlip::handleExtraCards()
//{
//	// Generar 3 cartas aleatorias
//	extraVals.clear();
//	for (int i = 0; i < 3; ++i) {
//		int val = generateRnd();
//		extraVals.push_back(val);
//	}
//}
//
//void BaccaratFlip::startRound()
//{
//	if (mat.player.size() == 0 && mat.player.size() == 0)
//	{
//		if (!animOn)
//		{
//			extra1->setPos({ Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 }); // frame 14 = invisible
//			extra2->setPos({ Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 });
//			extra3->setPos({ Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 });//a
//			cardButton();
//			active = true;//ACORDARME PONER EN FALSE EN EL CLEAR DECK
//			handleExtraCards();
//			extra1->frame = 0;
//			extra2->frame = 0;
//			extra3->frame = 0;
//			tercera = extraVals[2];
//			segunda = extraVals[1];
//			primera = extraVals[0];
//			Baccarat::startRound();
//		}
//	}
//}
////crea los botonees para llas cartas
//void BaccaratFlip::cardButton()
//{
//	carta1 = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
//	addObjects(carta1);
//	addEventListener(carta1);
//	carta1->connect([this] {if (active && flips < 2) { extra1->frame = extraVals[0]; flips++; deckButton(); } chosen = 0;  });
//
//	carta2 = new Button(this, Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
//	addObjects(carta2);
//	addEventListener(carta2);
//	carta2->connect([this] {if (active && flips < 2) { extra2->frame = extraVals[1]; flips++; deckButton(); }chosen = 1; });
//
//	carta3 = new Button(this, Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20, Game::WIN_HEIGHT / 8, text);
//	addObjects(carta3);
//	addEventListener(carta3);
//	carta3->connect([this] {if (active && flips < 2) { extra3->frame = extraVals[2]; flips++; deckButton(); } chosen = 2; });
//	//Resetear flips en clear deck!!!!!!!!!!!!!!
//
//}
//
//void BaccaratFlip::deckButton()
//{
//	if (flips == 2) {
//		player = new Button(this, Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 90, Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20 * 2.72, Game::WIN_HEIGHT / 8, text);
//		addObjects(player);
//		addEventListener(player);
//		player->connect([this] {
//			if (extraVals[chosen] != -1 && extraP < 2) {
//				mat.player.push_back(extraVals[chosen]);
//				extraVals[chosen] = -1; // Marca como usada
//				int a = flips;
//				extraP++;
//				if (chosen == 0) {
//					extra1->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta1);
//					deleteSpecificGO(carta1);
//					chosen = 1;
//
//				}
//				else if (chosen == 1) {
//					extra2->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta2);
//					deleteSpecificGO(carta2);
//					chosen = 2;
//
//				}
//				else if (chosen == 2) {
//					extra3->setPos({ (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 20), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta3);
//					deleteSpecificGO(carta3);
//					chosen = 0;
//				}
//			}
//
//			});
//
//		banker = new Button(this, Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42, Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8, Game::WIN_WIDTH / 20 * 2.72, Game::WIN_HEIGHT / 8, text);
//		addObjects(banker);
//		addEventListener(banker);
//		banker->connect([this] {
//			if (extraVals[chosen] != -1 && extraB < 2) {
//
//				mat.banker.push_back(extraVals[chosen]);
//				extraVals[chosen] = -1; // Marca como usada
//				extraB++;
//
//				if (chosen == 0) {
//					extra1->setPos({ (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta1);
//					deleteSpecificGO(carta1);
//					//chosen = 1;
//				}
//				else if (chosen == 1) {
//					extra2->setPos({ (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42 + Game::WIN_WIDTH / 20), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta2);
//					deleteSpecificGO(carta2);
//					chosen = 2;
//
//				}
//				else if (chosen == 2) {
//					extra3->setPos({ (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42 + Game::WIN_WIDTH / 10), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 32) });
//					deleteSpecificEH(carta3);
//					deleteSpecificGO(carta3);
//					chosen = 0;
//				}
//			}
//
//			});
//
//
//	}
//}
//
//void BaccaratFlip::clearDeck()
//{
//	Baccarat::clearDeck();
//	flips = 0;
//	active = false;
//	extraB = 0;
//	extraP = 0;
//
//	deleteSpecificGO(carta1);
//	deleteSpecificEH(carta1);
//	deleteSpecificGO(carta2);
//	deleteSpecificEH(carta2);
//	deleteSpecificGO(carta3);
//	deleteSpecificEH(carta3);
//	deleteSpecificGO(player);
//	deleteSpecificEH(player);
//	deleteSpecificGO(banker);
//	deleteSpecificEH(banker);
//	delete carta1;
//	delete carta2;
//	delete carta3;
//	delete player;
//	delete banker;
//}
//
//void BaccaratFlip::render() const {
//	Baccarat::render();
//	if (animOn)
//	{
//		SDL_Rect black(0, 0, Game::WIN_WIDTH, Game::WIN_HEIGHT);
//		SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_MUL);
//		SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 170);
//		SDL_RenderFillRect(game->getRenderer(), &black);
//		intro->render(title);
//	}
//}
//
//void BaccaratFlip::update()
//{
//	if (mat.player.size() == 0 && mat.player.size() == 0)
//		GameState::update();
//	if (cardAnim && SDL_GetTicks() - animTime > 75.0f && frame < 9)
//	{
//		frame++;
//		animTime = SDL_GetTicks();
//		if (frame == 7) {
//			if (animInCard == 0)
//			{
//				player1->frame = mat.player[0];
//				if (mat.player[0] > 9)
//					ctFrame = 0;
//				else
//					ctFrame = mat.player[0];
//			}
//			else if (animInCard == 1)
//			{
//				banker1->frame = mat.banker[0];
//				if (mat.banker[0] > 9)
//					ctFrameB = 0;
//				else
//					ctFrameB = mat.banker[0];
//			}
//			else if (animInCard == 2)
//			{
//				player2->frame = mat.player[1];
//				if (mat.player[1] <= 9)
//				{
//					ctFrame += mat.player[1];
//					ctFrame = ctFrame % 10;
//				}
//			}
//			else if (animInCard == 3)
//			{
//				banker2->frame = mat.banker[1];
//				if (mat.banker[1] <= 9)
//				{
//					ctFrameB += mat.banker[1];
//					ctFrameB = ctFrameB % 10;
//				}
//			}
//		}
//		if (frame == 9 && animInCard < 3) {
//			frame = 0;
//			if (animInCard == 0)
//			{
//				animInCard++;
//				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.42 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
//			}
//			else if (animInCard == 1)
//			{
//				animInCard++;
//				sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 20.70 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
//			}
//			else if (animInCard == 2)
//			{
//				animInCard++;
//				sm = { (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 6.38 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.32 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
//			}
//		}
//	}
//	if (frame == 9) {
//		handThird();//reparte tercera
//		cardAnim = false;
//		frame = 0;
//		animInCard = 0;
//		sm = { (int)(Game::WIN_WIDTH / 3 + Game::WIN_WIDTH / 10.3 - Game::WIN_WIDTH / 40), (int)(Game::WIN_HEIGHT / 5.33 - Game::WIN_HEIGHT / 8 - Game::WIN_HEIGHT / 16), Game::WIN_WIDTH / 10, Game::WIN_HEIGHT / 4 };
//	}
//	if (thirdPlayerMove) {
//		player3->setPos(player3->position() - Vector2D(5, 0));
//		if (player3->position().getX() <= (int)(Game::WIN_WIDTH / 3 - Game::WIN_WIDTH / 81))
//		{
//			thirdPlayerMove = false;
//			if (mat.player[2] <= 9)
//			{
//				ctFrame += mat.player[2];
//				ctFrame = ctFrame % 10;
//			}
//			goForWin = true;
//		}
//	}
//	if (thirdBankerMove) {
//		banker3->setPos(banker3->position() + Vector2D(5, 0));
//		if (banker3->position().getX() >= (int)(Game::WIN_WIDTH * 2 / 3 - Game::WIN_WIDTH / 20.5))
//		{
//			thirdBankerMove = false;
//			if (mat.banker[2] <= 9)
//			{
//				ctFrameB += mat.banker[2];
//				ctFrameB = ctFrameB % 10;
//			}
//			goForWin = true;
//		}
//	}
//	if ((extraB + extraP == 3))
//	{
//		if (extra3->frame == 0) {
//			extra3->frame = tercera;
//		}
//		else if (extra2->frame == 0) {
//			extra2->frame = segunda;
//		}
//		else if (extra1->frame == 0) {
//			extra1->frame = primera;
//		}
//		ctFrame = 0;
//		ctFrameB = 0;
//		for (int p : mat.player) {
//			ctFrame += p;
//		}
//		for (int p : mat.banker) {
//			ctFrameB += p;
//		}
//		ctFrame = ctFrame % 10;
//		ctFrameB = ctFrameB % 10;
//		win();
//		goForWin = false;
//
//
//	}
//	title = { Game::WIN_WIDTH / 2 - width / 2, Game::WIN_HEIGHT / 2 - height / 2,width,height };
//	if (width < Game::WIN_WIDTH && height < Game::WIN_HEIGHT && animOn) {
//		width += Game::WIN_WIDTH / 50;
//		height += Game::WIN_HEIGHT / 50;
//		actual = time;
//	}
//	else {
//		float dt = SDLUtils::getDeltaTime();
//		time += dt;
//		if (time - actual > 1)
//		{
//			animOn = false;
//			width = 0;
//			height = 0;
//		}
//	}
//	if (timeForWin) {
//		float dt = SDLUtils::getDeltaTime();
//		tiempo += dt;
//		if (tiempo > 3)
//		{
//			timeForWin = false;
//			tiempo = 0;
//			playerBet = false;
//			bankerBet = false;
//			tieBet = false;
//			player1->frame = 0;
//			player2->frame = 0;
//			banker1->frame = 0;
//			banker2->frame = 0;
//			banker3->frame = 14;
//			player3->frame = 14;
//			ctFrame = 14;
//			ctFrameB = 14;
//			extra1->setPos({ Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 10 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 }); // frame 14 = invisible
//			extra2->setPos({ Game::WIN_WIDTH / 2 - Game::WIN_WIDTH / 40 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 });
//			extra3->setPos({ Game::WIN_WIDTH / 2 + Game::WIN_WIDTH / 20 - Game::WIN_WIDTH / 240, Game::WIN_HEIGHT / 3 });//a
//			extra1->frame = 0;
//			extra2->frame = 0;
//			extra3->frame = 0;
//			clearDeck();
//		}
//	}
//}
