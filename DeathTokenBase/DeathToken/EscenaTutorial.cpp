#include "EscenaTutorial.h"
#include "Menu.h"
#include "button.h"
#include "texture.h"
#include "game.h"
#include "sdlutils.h"

EscenaTutorial::EscenaTutorial(Game* g) : GameState(g), _g(g), picked(false), startGame(false), resultado(false), inDialog(false), inState(false), index(-1), fases(0), bet(0), a(0) {
	float x = Game::WIN_WIDTH * (600.0f / 1920.0f);
	float y = Game::WIN_HEIGHT * (680.0f / 1080.0f);
	float cartaW = Game::WIN_WIDTH * (110.0f / 1920.0f);
	float cartaH = Game::WIN_HEIGHT * (210.0f / 1920.0f);
	//Botones juego
	Button* piedra = new Button(this, (int)(x), (int)(y), (int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	piedra->connect([this] {
		if (!picked && startGame) {
			setIndex(0);
			picked = true;
		}
		});
	addObjects(piedra);
	addEventListener(piedra);

	x = Game::WIN_WIDTH * (900.0f / 1920.0f);
	Button* papel = new Button(this, (int)x, (int)y, (int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	papel->connect([this] {
		if (!picked && startGame) {
			setIndex(1);
			picked = true;
		}
		});
	addObjects(papel);
	addEventListener(papel);

	x = Game::WIN_WIDTH * (1200.0f / 1920.0f);
	Button* tijera = new Button(this, (int)x, (int)y, (int)cartaW, (int)cartaH, game->getTexture(BTNSLOT), game->getTexture(BTNSLOTCLICK));
	tijera->connect([this] {
		if (!picked && startGame) {
			setIndex(2);
			picked = true;
		}
		});
	addObjects(tijera);
	addEventListener(tijera);
	//Interfaz

	_dialog = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog);
	_dialog->setX(Game::WIN_WIDTH * (100.0f / 1920.0f));
	_dialog->setY(Game::WIN_HEIGHT * (100.0f / 1080.0f));
	_dialog->setWidth(Game::WIN_WIDTH / 3);


	eco = new PlayerEconomy();
	eco->EconomyInitialize();
	_ui = new UIEscenaTutorial(this, g, this);
	_hud = new HUDBet(this);

	float w = Game::WIN_WIDTH * (200.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (200.0f / 1080.0f);
	float _x = (350.0f / 1920.0f) * Game::WIN_WIDTH;
	float _y = (400.0f / 1080.0f) * Game::WIN_HEIGHT;
	_bet = new ButtonTutorial(this, game, _ui, (int)_x, (int)_y, (int)w, (int)h, game->getTexture(BETSLOTS), this);
	addObjects(_bet);
	addEventListener(_bet);


}
EscenaTutorial::~EscenaTutorial() {
	delete eco;
}
void
EscenaTutorial::render() const {
	SDL_Rect background;
	background.x = background.y = 0;
	background.w = Game::WIN_WIDTH / 1920.0f;
	background.h = Game::WIN_HEIGHT / 1080.0f;
	game->getTexture(BLACKFOND)->render(background);

	GameState::render();



	SDL_Rect flechaUP;
	SDL_Rect flechaDown;

	flechaUP.w = Game::WIN_WIDTH * (140 / 1920.0f);
	flechaUP.h = Game::WIN_HEIGHT * (140 / 1080.0f);

	flechaDown.w = Game::WIN_WIDTH * (140 / 1920.0f);
	flechaDown.h = Game::WIN_HEIGHT * (140 / 1080.0f);

	if (fases == 1) {
		flechaDown.x = (340.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (785.0f / 1080.0f) * Game::WIN_HEIGHT;
		flechaUP.x = (420.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (500.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 2) {
		flechaDown.x = (1720.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (800.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 3) {
		flechaDown.x = (600.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (630.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (900.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (630.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (1200.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (630.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}
	else if (fases == 4) {
		flechaUP.x = (1500.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (200.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);
	}
	else if (fases == 5) {
		SDL_Rect info;
		info.x = (1377.0f / 1920.0f) * Game::WIN_WIDTH;
		info.y = (905.0f / 1080.0f) * Game::WIN_HEIGHT;
		info.w = Game::WIN_WIDTH * (126.0f / 1980.0f);
		info.h = Game::WIN_HEIGHT * (126.0f / 1080.0f);
		game->getTexture(UIINFO)->render(info);

		flechaDown.x = (1377.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (630.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);
	}

	_dialog->render();

	SDL_Rect player;
	player.x = (720.0f / 1920.0f) * Game::WIN_WIDTH;
	player.y = (400.0f / 1080.0f) * Game::WIN_HEIGHT;
	player.h = (210.0f / 1080.0f) * Game::WIN_HEIGHT;
	player.w = (210.0f / 1920.0f) * Game::WIN_WIDTH;

	SDL_Rect enemy;
	enemy.x = Game::WIN_WIDTH * (1020.0f / 1920.0f);
	enemy.y = Game::WIN_HEIGHT * (400.0f / 1080.0f);
	enemy.h = Game::WIN_HEIGHT * (210.0f / 1080.0f);
	enemy.w = Game::WIN_WIDTH * (210.0f / 1920.0f);
	if (!picked) {
		game->getTexture(SLOTSBUT)->render(player);
		game->getTexture(SLOTSBUT)->render(enemy);

	}
	else {
		game->getTexture(ICONOPPT)->renderFrame(player, 0, index);
		if (resultado && picked) {
			if (index == 0) {
				game->getTexture(ICONOPPT)->renderFrame(enemy, 0, 2);
			}
			else {
				game->getTexture(ICONOPPT)->renderFrame(enemy, 0, index - 1);
			}

		}
	}
}
void EscenaTutorial::update() {
	GameState::update();

	uint currentTime = SDL_GetTicks();
	float aux = SDLUtils::getDeltaTime();
	_dialog->update(currentTime - a);

	if (fases == 0 && !inState)
	{		
		_dialog->showMessage("Bienvenido a DeathToken,en este casino infernal jugarás para poderte salvar.");
		_dialog->showMessage("Antes de empezar vamos a darte unas pocas direcciones para que lo comprendas mejor.");
		_dialog->showMessage("Como puedes ver ahora estás jugando y tienes distintos elementos que puede que no entiendas, no te preocupes lo entenderás.");
		_dialog->update(currentTime - a);
		a = currentTime;
		fases++;
	}
	else if (fases == 1 && !inState)
	{		
		if (!inDialog) {
			inDialog = true;
			_dialog->update(currentTime - a);
			_dialog->showMessage("Como puedes ver tenemos las fichas con las que vas a apostar,si la spierdes todas se acabará todo.");
			_dialog->showMessage("¡Pero no te preocupes! Podrás llevar la cuenta de tus apuestas y lo que etés llevando en el momento.");
			_dialog->showMessage("Esas fichas las podrás canjear en una ruleta donde ganarás muchos premios y recompensas,te recomiendo que tires mucho de ella.");
			_dialog->showMessage("Dentro de esta ruleta podrás volverte LOCO y la cosa cambiará la cosa,mejor no deigo más.Ya lo descubrirás.");
			_dialog->showMessage("A lo que iba con las fichas. Estás tendrás que arrastrarlas a los lugares de apuesta para poder empezar a jugar. ¡Intentalo!");
			_dialog->update(currentTime - a);
			a = currentTime;
		}
		else {
			_dialog->hideMessage();
		}
		if (hasChip) {
			fases++;
			inDialog = false;
		}
	}
	else if (fases == 2 && !inState)
	{
		if (!inDialog) {
			inDialog = true;

			_dialog->update(currentTime - a);
			_dialog->showMessage("¡Genial! Ya podemos empezar a probar esto de los juegos.");
			_dialog->showMessage("Ahora simplemente dale a empezar la partida con el boton 'GO'");
			_dialog->update(currentTime - a);
			a = currentTime;
		}
		else {
			_dialog->hideMessage();
		}
		if (startGame) {
			fases++;
			inDialog = false;
		}
	}
	else if (fases == 3 && !inState)
	{
		cout << "En fase:" << fases << "\n";
		_dialog->update(currentTime - a);
		if (!inDialog) {
			inDialog = true;

			_dialog->showMessage("¡Perfecto! Este juego es un simple piedra, papel o tijera.");
			_dialog->showMessage("Para ganar tendrás que pulsar alguno de estos tres botones para elegir alguna de lass figuras.");
			_dialog->showMessage("Luego elegiré yo y veremos quien ganas,si ganas conseguirás el doble de lo apostado. Genial, ¿no te parece?");
			_dialog->showMessage("Adelante escoge alguno");
		}
		else {
			_dialog->hideMessage();
		}
		if (picked && fases == 3) {
			counter += aux;
			if (counter >= 2) {
				counter = 0;
				resultado = true;
				game->push(new Award(game, (GameState*)this, bet, bet * 2));
				clear();
				inDialog = false;
			}
			fases++;
		}
	}
	else if (fases == 4 && !inState)
	{
		_dialog->update(currentTime - a);
		_dialog->showMessage("¡¿Me has gando?! Pensaba que habia escogido mejor.");
		_dialog->showMessage("Bueno, no pasa nada, como has visto has conseguido más de dinero del que tenías y se te ha sumado");
		fases++;
	}
	else if (fases == 5 && !inState)
	{
		cout << "En fase:" << fases << "\n";
		_dialog->update(currentTime - a);
		_dialog->showMessage("Con esto no tengo nada más que aclarar,solo decirte que si tienes alguna duda dentro de los juego tendrás este botón y te enseñará lo que necesites.");
		_dialog->showMessage("¡Ostras,casi se me olvida decirtelo! Para moverte tendrás que usar las teclas: 'W' 'A' 'S' 'D' o cruceta ('->', '<-' ,etc.), y para entrar a los juegos es con la tecla 'E'.");
		_dialog->showMessage("Lo dicho,mucha suerte y que tengas una buena partida.¡Suete! La necesitarás >:)");
		
		_dialog->resetHistory();
		_g->push(new Menu(_g));
	}
	_dialog->update(static_cast<float>(currentTime - a));
	a = currentTime;


}
void EscenaTutorial::fase0(uint currentTime) {

}
void EscenaTutorial::fase1(uint currentTime) {

}
void EscenaTutorial::fase2(uint currentTime) {

}
void EscenaTutorial::fase3(uint currentTime) {

}
void EscenaTutorial::fase4(uint currentTime) {

}
void EscenaTutorial::fase5(uint currentTime) {

}