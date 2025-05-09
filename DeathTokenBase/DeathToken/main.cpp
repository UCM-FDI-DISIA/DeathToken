
#include <iostream>
#include "checkML.h"

#include "game.h"

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