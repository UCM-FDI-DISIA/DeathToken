#include <iostream>
#include "checkML.h"

#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game* game = new Game();
		game->run();
		delete game;
	}
	catch (const std::string& msg) {
#if DEBUG
		cerr << "Error: " << msg << endl;
#endif
	}
	return 0;
}