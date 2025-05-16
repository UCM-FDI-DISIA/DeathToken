#include "EscenaTutorial.h"
#include "Menu.h"
#include "button.h"
#include "texture.h"
#include "game.h"
#include "sdlutils.h"

EscenaTutorial::EscenaTutorial(Game* g) : GameState(g), _g(g), picked(false), startGame(false), hasChip(false), resultado(false), inState(false), dialog(true), index(-1), fases(0), bet(0), a(0) {
	
	float x = Game::WIN_WIDTH * (600.0f / 1920.0f);
	float y = Game::WIN_HEIGHT * (600.0f / 1080.0f);
	float cartaW = Game::WIN_WIDTH * (300.0f / 1920.0f);
	float cartaH = Game::WIN_HEIGHT * (300.0f / 1080.0f);
	//Botones juego
	Button* piedra = new Button(this, (int)(x), (int)(y), (int)cartaW, (int)cartaH, game->getTexture(ICONOPPT), nullptr, 0);
	piedra->connect([this] {
		if (!picked && startGame && !itIsInDIalog()) {
			setIndex(0);
			picked = true;
		}
		});
	addObjects(piedra);
	addEventListener(piedra);

	x = Game::WIN_WIDTH * (900.0f / 1920.0f);
	Button* papel = new Button(this, (int)x, (int)y, (int)cartaW, (int)cartaH, game->getTexture(ICONOPPT), nullptr, 1);
	papel->connect([this] {
		if (!picked && startGame && !itIsInDIalog()) {
			setIndex(1);
			picked = true;
		}
		});
	addObjects(papel);
	addEventListener(papel);

	x = Game::WIN_WIDTH * (1200.0f / 1920.0f);
	Button* tijera = new Button(this, (int)x, (int)y, (int)cartaW, (int)cartaH, game->getTexture(ICONOPPT), nullptr, 2);
	tijera->connect([this] {
		if (!picked && startGame && !itIsInDIalog()) {
			setIndex(2);
			picked = true;
		}
		});
	addObjects(tijera);
	addEventListener(tijera);

	//Interfaz
	_dialog1 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog1);
	_dialog1->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog1->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog1->setWidth(Game::WIN_WIDTH / 4);

	_dialog2 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog2);
	_dialog2->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog2->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog2->setWidth(Game::WIN_WIDTH / 4);

	_dialog3 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog3);
	_dialog3->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog3->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog3->setWidth(Game::WIN_WIDTH / 4);

	_dialog4 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog4);
	_dialog4->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog4->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog4->setWidth(Game::WIN_WIDTH / 4);

	_dialog5 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog5);
	_dialog5->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog5->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog5->setWidth(Game::WIN_WIDTH / 4);

	_dialog6 = new DialogueBox(game->getRenderer(), game->getTypo(FIGHTS_SMALL), static_cast<int>((25.0f / 1920.0f)) * Game::WIN_WIDTH, static_cast<int>((870.0f / 1080.0f)) * Game::WIN_HEIGHT,
		true, false, 400, 180);
	addEventListener((EventHandler*)_dialog6);
	_dialog6->setX(Game::WIN_WIDTH * (1300.0f / 1920.0f));
	_dialog6->setY(Game::WIN_HEIGHT * (400.0f / 1080.0f));
	_dialog6->setWidth(Game::WIN_WIDTH / 4);


	saldo = PlayerEconomy::getBlueSouls();
	PlayerEconomy::setBlueSouls(500);

	_ui = new UIEscenaTutorial(this, g, this);

	_hud = new HUDBet(this, false);

	float w = Game::WIN_WIDTH * (200.0f / 1920.0f);
	float h = Game::WIN_HEIGHT * (200.0f / 1080.0f);
	float _x = (350.0f / 1920.0f) * Game::WIN_WIDTH;
	float _y = (400.0f / 1080.0f) * Game::WIN_HEIGHT;
	_bet = new ButtonTutorial(this, game, _ui, (int)_x, (int)_y, (int)w, (int)h, game->getTexture(BETSLOTS), this);
	addObjects(_bet);
	addEventListener(_bet);

	showDialog1();
	showDialog2();
	showDialog3();
	showDialog4();
	showDialog5();
	showDialog6();
}
EscenaTutorial::~EscenaTutorial() {
	_dialog1 = nullptr;
	_dialog2 = nullptr;
	_dialog3 = nullptr;
	_dialog4 = nullptr;
	_dialog5 = nullptr;
	_dialog6 = nullptr;
	_g = nullptr;
}
void
EscenaTutorial::render() const {
	SDL_Rect r;
	r.x = r.y = 0;
	r.h = Game::WIN_HEIGHT;
	r.w = Game::WIN_WIDTH;
	game->getTexture(MARBLESBACK)->render(r);

	GameState::render();

	SDL_Rect flechaUP;
	SDL_Rect flechaDown;

	flechaUP.w = Game::WIN_WIDTH * (140 / 1920.0f);
	flechaUP.h = Game::WIN_HEIGHT * (140 / 1080.0f);

	flechaDown.w = Game::WIN_WIDTH * (140 / 1920.0f);
	flechaDown.h = Game::WIN_HEIGHT * (140 / 1080.0f);

	if (fases == 0)
	{
		_dialog1->render();
		if (_dialog1->shouldAdvanceState()) {
			_dialog1->resetDialogStateFlag();
			_dialog1->resetHistory();
		}
	}
	else if (fases == 1) {
		flechaDown.x = (340.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (785.0f / 1080.0f) * Game::WIN_HEIGHT;
		flechaUP.x = (420.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (500.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		_dialog2->render();
		if (_dialog2->shouldAdvanceState()) {
			if (hasChip) {
				_dialog2->resetDialogStateFlag();
				_dialog2->resetHistory();
			}
			else
			{
				_dialog2->hideMessage();
			}
		}
	}
	else if (fases == 2) {
		flechaDown.x = (1720.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (800.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		_dialog3->render();
		if (_dialog3->shouldAdvanceState()) {
			if (startGame)
			{
				_dialog3->resetDialogStateFlag();
				_dialog3->resetHistory();
			}
			else {
				_dialog3->hideMessage();
			}
		}
	}
	else if (fases == 3) {
		flechaDown.x = (600.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (600.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (900.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (600.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (1200.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (600.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		_dialog4->render();
		if (_dialog4->shouldAdvanceState()) {
			if (picked)
			{
				_dialog4->resetDialogStateFlag();
				_dialog4->resetHistory();
			}
			else {
				_dialog4->hideMessage();
			}
		}
	}
	else if (fases == 4) {
		flechaUP.x = (1500.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaUP.y = (200.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaUP, 0, 0);

		_dialog5->render();
		if (_dialog5->shouldAdvanceState()) {
			_dialog5->resetDialogStateFlag();
			_dialog5->resetHistory();
		}
	}
	else if (fases == 5) {
		SDL_Rect info;
		info.x = (1370.0f / 1920.0f) * Game::WIN_WIDTH;
		info.y = (905.0f / 1080.0f) * Game::WIN_HEIGHT;
		info.w = Game::WIN_WIDTH * (126.0f / 1980.0f);
		info.h = Game::WIN_HEIGHT * (126.0f / 1080.0f);
		game->getTexture(UIINFO)->render(info);

		SDL_Rect erase;
		erase.x = (1270.0f / 1920.0f) * Game::WIN_WIDTH;
		erase.y = (905.0f / 1080.0f) * Game::WIN_HEIGHT;
		erase.w = Game::WIN_WIDTH * (126.0f / 1980.0f);
		erase.h = Game::WIN_HEIGHT * (126.0f / 1080.0f);
		game->getTexture(UIERASE)->render(erase);

		SDL_Rect repeat;
		repeat.x = (1170.0f / 1920.0f) * Game::WIN_WIDTH;
		repeat.y = (905.0f / 1080.0f) * Game::WIN_HEIGHT;
		repeat.w = Game::WIN_WIDTH * (126.0f / 1980.0f);
		repeat.h = Game::WIN_HEIGHT * (126.0f / 1080.0f);
		game->getTexture(UIREPEAT)->render(repeat);

		flechaDown.x = (1377.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (830.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (1270.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (830.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		flechaDown.x = (1170.0f / 1920.0f) * Game::WIN_WIDTH;
		flechaDown.y = (830.0f / 1080.0f) * Game::WIN_HEIGHT;
		game->getTexture(MANOS)->renderFrame(flechaDown, 0, 1);

		_dialog6->render();
		if (_dialog6->shouldAdvanceState()) {
			_dialog6->resetDialogStateFlag();
			_dialog6->resetHistory();
		}
	}

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

	if (picked) {
		game->getTexture(ICONOPPT)->renderFrame(player, 0, index);
		if (resultado) {
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

	switch (fases) {
	case 0:
		_dialog1->update(currentTime - a);
		if (_dialog1->shouldAdvanceState()) {
			outDialog();
			++fases;
		}
		else {
			inDialog();
		}
		_dialog1->update(static_cast<float>(currentTime - a));
		break;
	case 1:
		_dialog2->update(currentTime - a);
		if (_dialog2->shouldAdvanceState()) {
			outDialog();
			if (hasChip && !dialog)
			{
				++fases;
			}
		}
		else {
			inDialog();
		}
		_dialog2->update(static_cast<float>(currentTime - a));
		break;
	case 2:
		_dialog3->update(currentTime - a);
		if (_dialog3->shouldAdvanceState()) {
			outDialog();
			if (startGame && !dialog) {
				++fases;
			}
		}
		else {
			inDialog();
		}
		_dialog3->update(static_cast<float>(currentTime - a));
		break;
	case 3:
		_dialog4->update(currentTime - a);
		if (_dialog4->shouldAdvanceState()) {
			outDialog();
			if (picked && !dialog)
			{
				game->push(new Award(game, (GameState*)this, bet, bet * 2));
				clear();
				resultado = true;
				++fases;
			}
		}
		else {
			inDialog();
		}
		_dialog4->update(static_cast<float>(currentTime - a));
		break;
	case 4:
		_dialog5->update(currentTime - a);
		if (_dialog5->shouldAdvanceState()) {
			outDialog();
			++fases;
		}
		else {
			inDialog();
		}
		_dialog5->update(static_cast<float>(currentTime - a));
		break;
	case 5:
		_dialog6->update(currentTime - a);
		if (_dialog6->shouldAdvanceState()) {
			outDialog();
			clear();
			PlayerEconomy::setBlueSouls(saldo);
			game->pop();
		}
		else {
			inDialog();
		}
		break;
	}

	a = currentTime;
}

void EscenaTutorial::showDialog1() const {

	_dialog1->showMessage("¡Te doy la bienvenida a Death Token!");
	_dialog1->showMessage("Antes de nada me presento: soy el TUTORIAL, aqui te enseñaré todo lo necesario para que empieces a jugar.");
	_dialog1->showMessage("Antes de empezar vamos a darte unas pocas direcciones para que lo comprendas mejor.");
	_dialog1->showMessage("No te preocupes pasaremos por todos los aspectos necesarios para que puedas disfrutar.");
	_dialog1->showMessage("Si no me quieres escuchar puedes dar a la tecla: 'ENTER' y saltaré el dialogo.");
	_dialog1->showMessage("Si quieres que vaya maas rapido pulsa la tecla: 'ESPACIO' e iré más rápido.");
	_dialog1->showMessage("Eso si, me pondré triste :(");

}
void EscenaTutorial::showDialog2() const {

	_dialog2->showMessage("Bueno empezemos por las cosas que estás viendo ahora en pantalla...");
	_dialog2->showMessage("Como puedes ver tenemos las fichas con las que vas a apostar, si las pierdes todas se acabará todo.");
	_dialog2->showMessage("Esperemos que eso no suceda,ya a ocurrido antes y te lo aseguro...¡MEJOR EVITARLO!");
	_dialog2->showMessage("¡Pero no te preocupes! Podrás llevar la cuenta de tus apuestas y lo que estes llevando en el momento.");
	_dialog2->showMessage("Esas fichas las podrás canjear en una ruleta donde ganarás muchos premios y recompensas, muy recomendable si quieres ganar.");
	_dialog2->showMessage("En ella se encuentra la GUADAÑA tu OBJETIVO, pero la podrás COMPRAR si tienes el dinero suficiente");
	_dialog2->showMessage("Dentro de esta ruleta podrás volverte LOCO y la cosa cambiará, mejor no digo más. Ya lo descubrirás.");
	_dialog2->showMessage("A lo que iba con las fichas. Estás tendrás que arrastrarlas a los lugares de apuesta para poder empezar a jugar.");
	_dialog2->showMessage("No podrás apostar más de lo que tienes, eso es una tontería.");
	_dialog2->showMessage("Además tienes varias secciones de fichas donde tendrás cifras más altas, las podrás ver si das a las flechas amarillas.");
	_dialog2->showMessage("¡Vamos, inténtalo!");

}
void EscenaTutorial::showDialog3() const {

	_dialog3->showMessage("¡Genial! Ya podemos empezar a probar esto de los juegos.");
	_dialog3->showMessage("Ahora simplemente dale a empezar la partida con el boton 'GO'");
	_dialog3->showMessage("La mayoría de juegos empezarán así: primero apuesta, luego 'GO'.");

}
void EscenaTutorial::showDialog4() const {
	_dialog4->showMessage("Bien una vez hecha la apuesta e iniciado el juego, podremos hacer una partida de prueba. ¡¡¡Por fin!!!");
	_dialog4->showMessage("Ahora vamos a jugar a un simple piedra, papel y tijera.");
	_dialog4->showMessage("Tu elegirás primero y luego yo.Luego revelaremos nuestras elecciones para ver quien gana");
	_dialog4->showMessage("Tendrás que elegir alguno de estos tres botones para elegir alguno de estos.");
	_dialog4->showMessage("Cuando quieras. Yo tengo todo el tiempo del mundo :)");

}
void EscenaTutorial::showDialog5() const {

	_dialog5->showMessage("¡¿Me has gando?! Pensaba que habia escogido mejor.");
	_dialog5->showMessage("Bueno, no pasa nada, como has visto has conseguido más de dinero del que tenías y se te ha sumado");
	_dialog5->showMessage("Asi funcionan las apuestas: tu pones el dinero inicial y luego si ganas podrás ganar en fucnión de un multiplicador.");
	_dialog5->showMessage("Cada juego tiene sus propios multiplicadores lo cual suponen distintas maneras de jugar");
}
void EscenaTutorial::showDialog6()const {
	_dialog6->showMessage("Con esto no tengo nada más que aclarar,solo decirte que si tienes alguna duda dentro de los juego tendrás este botón y te enseñará lo que necesites.");
	_dialog6->showMessage("¡Ostras,casi se me olvida decirtelo! Para moverte tendrás que usar las teclas: 'W' 'A' 'S' 'D' o cruceta ('->', '<-' ,etc.)");
	_dialog6->showMessage(", y para entrar a los juegos es con la tecla 'E'.Con la 'P' podrás poner pausa.");
	_dialog6->showMessage("Además de que en varios juegos encontrarás botones como estos.");
	_dialog6->showMessage("Tendrás uno de borrar apuesta,otro de información y un último donde puedes repetir de nuevo la partida");
	_dialog6->showMessage("Lo dicho,mucha suerte y que tengas una buena partida.¡Suerte! La necesitarás >:)");
}