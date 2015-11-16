#include "game.h"
#include "corridor.h"
#include "hallRoom.h"
#include <iostream>
#include <sstream>
#include <list>

#define VERSION 0.2

Game::Game(){

}

Game::~Game() {
	delete player;
}

void Game::Start() {
	initializeGame();
	playGame();
}

void Game::initializeGame() {
	gameActive = false;
	current_room = 0;
	player = new Character();
	room_list.push_back(new HallRoom());
	room_list[0]->addItem(Item("note", { PICK, DROP, READ }));
	room_list[0]->addItem(Item("mirror", { BREAK }));

	room_list[0]->addDoor(Door(SOUTH, 1));
	room_list.push_back(new Corridor());
	room_list[1]->addDoor(Door(NORTH, 0));
	room_list[1]->addItem(Item("hammer", { PICK, DROP, BREAK }));


	cout << "**********  Welcome to MyZork, version " << VERSION << " ********** \n\n";
}

void Game::playGame() {
	gameActive = true;

	string userInput;
	cout << describeRoom(current_room) << endl;

	//----------- GAME LOOP -----------------
	do{
		cout << ">";
		getline(cin, userInput);
		processUserInput(userInput);
		doAction(current_action);
	} while (gameActive);
	//------------------------------------

	system("pause");
}

void Game::processUserInput(const string userInput) {
	verb = object = "";
	stringstream ss(userInput);
	string word;
	current_action = NOACTION;
	getline(ss, word, ' ');
	if (!word.empty())
		verb = word;
	getline(ss, word, ' ');
	if (!word.empty())
		object = word;

	if (verb == "go")
		current_action = GO;
	else if (verb == "pick") current_action = PICK;
	else if (verb == "drop") current_action = DROP;
	else if (verb == "see") current_action = SEE;
	else if (verb == "read") current_action = READ;
	else if (verb == "break") current_action = BREAK;
	else if (verb == "quit") current_action = QUIT;
}

void Game::doAction(const Actions action) {
	switch (action)
	{
	case GO: doGo(); break;
	case QUIT: doQuit(); break;
	case PICK: doPick(); break;
	case DROP: doDrop(); break;
	case READ: doRead(); break;
	case BREAK: doBreak(); break;
	case SEE: doSee(); break;
	case NOACTION: doNothing(); break;
	default: doNothing();
	}
}

void Game::doNothing() {
	cout << "Couldn't understand what you want to do: \n"
		"please use a verb that the game understands." << endl;
}

void Game::doQuit() {
	cout << "Goodbye, I hope you had some fun. Have a nice day." << endl;
	gameActive = false;
}

void Game::doGo() {
	Directions directionToGo;
	if (object != verb)
	{
		directionToGo = getDirection(object);

		int toRoom = room_list[current_room]->isDoor(directionToGo);
		if (toRoom >= 0)
		{
			current_room = toRoom;
			cout << "\n" << describeRoom(current_room) << endl;
		}
		else cout << "You can't go to that direction." << endl;
	}
	else
	{
		cout << "\nWhich direction do you want to go to?\n" << endl;
		cout << ">";
		getline(cin, object);
		doGo();
	}
	
}

Directions Game::getDirection(const string object)
{
	Directions directionToGo = NODIRECTION;
	if (!object.empty())
	{
		if (object == "north") directionToGo = NORTH;
		else if (object == "east") directionToGo = EAST;
		else if (object == "west") directionToGo = WEST;
		else if (object == "south") directionToGo = SOUTH;
	}

	return directionToGo;
}

void Game::doPick() {
	if (object != verb)
	{
		Item toPick = room_list[current_room]->getPickItem(object);
		if (toPick.first != "NOITEM")
		{
			toPick = room_list[current_room]->removeItem(object);
			player->pickItem(toPick);
			room_list[current_room]->changeState(toPick.first);
			cout << "You picked the " << toPick.first << "." << endl;
		}
		else cout << "You can't pick that item" << endl;
	}
	else {
		cout << "Which item do you want to pick?" << endl;
		cout << ">";
		getline(cin, object);
		doPick();
	}
}

void Game::doDrop() {
	if (object != verb)
	{
		Item toDrop = player->dropItem(object);
		if (toDrop.first != "NOITEM")
			room_list[current_room]->addItem(toDrop);
		else cout << "You can't drop that item";
	}
	else {
		cout << "Which item do you want to drop?" << endl;
		cout << ">";
		getline(cin, object);
		doDrop();
	}
}

void Game::doSee() {
	if (object != verb)
	{
		if (object.compare("inventory") == 0)
		{
			list<string> inv = player->getInventoryList();
			for (list<string>::const_iterator it = inv.begin(); it != inv.end(); ++it)
				cout << *it << endl;
		}
		else if (object.compare("room") == 0)
		{
			list<string> inv = room_list[current_room]->getItems();
			for (list<string>::const_iterator it = inv.begin(); it != inv.end(); ++it)
				cout << *it << endl;
		}
		else cout << "You can't do that" << endl;

	}
	else {
		cout << "Which item do you want to see?" << endl;
		cout << ">";
		getline(cin, object);
		doSee();
	}
}

void Game::doRead() {
	/*if (object != verb)
	{
		Item toRead = player->
	}
	else {
		cout << "What do you want to read?" << endl;
		cout << ">";
		getline(cin, object);
		doRead();
	}*/
}

void Game::doBreak() {
	if (object != verb)
	{
		Item toBreak = room_list[current_room]->getItem(object);
		if (toBreak.first != "NOITEM")
		{
			cout << "What do you want to break the " << object << " with?" << endl;
			cout << ">";
			getline(cin, object);
			Item result = player->getItem(object);
			bool found = false;
			for (available_actions::const_iterator it = result.second.begin(); it != result.second.end() && !found; ++it)
			{
				if (*it == BREAK)
					found = true;
			}

			if (found)
			{
				room_list[current_room]->changeState(toBreak.first);
				room_list[current_room]->removeItem(toBreak.first);
				cout << "You broke the " << toBreak.first << " with the " << object << endl;
			}
			else
			{
				cout << "You can't break the " << toBreak.first << " with a " << object << endl;
				return;
			}
		}
		else cout << "You can't break the " << object << endl;
	}
	else {
		cout << "What do you want to break?" << endl;
		cout << ">";
		getline(cin, object);
		doBreak();
	}
}

string Game::describeRoom(const int roomIndex){
	return room_list[current_room]->toString();
}