// Javier G�mez Z��iga
// Ismael Ortega S�nchez
// 2�GDV TPV

#include <iostream>
#include "checkML.h"

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}
	return 0;
}