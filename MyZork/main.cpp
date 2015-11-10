#include <iostream>
#include "room.h"
using namespace std;

int main() {
	Room *r1 = new Room("Habitacion Test");
	r1->setDescription("Una habitacion perfectamente vacia");

	bool game_exit = false;
	int n;
	while (!game_exit)
	{
		cout << "Bienvenido a MyZork, version 0.1" << endl;
		string habitacion = r1->toString();
		cout << habitacion;
		cin >> n;
		if (n == -1)
			game_exit = true;
	}


	return 0;
}