#include <iostream>
#include "room.h"
#include "character.h"
using namespace std;

int main() {
	Room *r1 = new Room("Habitacion Test");
	r1->setDescription("Testing pick & drop, try to pick and drop some things!");

	Character *player = new Character();
	bool game_exit = false;
	int n;
	string inputstr = "";
	cout << "Welcome to MyZork, version 0.15" << endl;
	r1->addItem(Item("Mazo", { PICK, DROP }));
	r1->addItem(Item("Adefesio", { PICK, DROP }));
	r1->addItem(Item("Nota", { PICK, DROP, READ }));
	do 
	{
		string habitacion = r1->toString();
		cout << habitacion << endl;
		cout << ">";
		getline(cin, inputstr);
		if (inputstr.find("quit") != string::npos)
			game_exit = true;
		if (inputstr.find("pick") != string::npos)
		{
			Item toPick = r1->removeItem("Adefesio");
			player->pickItem(toPick);
		}
		if (inputstr.find("inventory") != string::npos)
		{
			list<string> player_inventory = player->getInventoryList();
			for (list<string>::const_iterator it = player_inventory.begin(); it != player_inventory.end(); ++it)
				cout << *it << endl;
		}
		


		
		inputstr == "";
	} while (!game_exit);


	return 0;
}

//TODO: Pick & drop functionality