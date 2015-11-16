#include <iostream>
#include "game.h"

/*
Author: David Ruiz Vallejo
Personal implementation in C++ of the known game "Zork"


*/
using namespace std;

int main() {
	Game *game = new Game();
	game->Start();

	return 0;
}

//TODO: Item class