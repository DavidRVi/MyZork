#include "game.h"
#include "corridor.h"
#include "hallRoom.h"
#include "diningHall.h"
#include "lockerRoom.h";
#include <iostream>
#include <sstream>
#include <list>

#define VERSION 0.4

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
	room_list.push_back(new Corridor());
	room_list.push_back(new Room("Garden", "You think you're out of the manor because you see a bright sky \nand happy trees in the distance,\n"
		"but on closer look, you notice that they're painted in the walls,\n with such skill that it seems real.\n"
		"There is a water spring in the middle of the room with fresh water,\n"
		"and a door on the west"));
	room_list.push_back(new DiningHall());
	room_list.push_back(new LockerRoom());

	room_list[0]->addDoor(Door(SOUTH, 1));
	room_list[0]->addDoor(Door(EAST, 2));

	room_list[1]->addDoor(Door(NORTH, 0));
	room_list[1]->addDoor(Door(EAST, 3));
	room_list[1]->addDoor(Door(SOUTH, 4));

	room_list[2]->addDoor(Door(WEST, 0));

	room_list[3]->addDoor(Door(WEST, 1));
	room_list[3]->addDoor(Door(SOUTH, 5));
	room_list[3]->addDoor(Door(EAST, 6));

	room_list[4]->addDoor(Door(NORTH, 1));
	room_list[4]->addDoor(Door(EAST, 5));

	room_list[0]->addItem(Item("note", { PICK, DROP, READ }));
	room_list[0]->addItem(Item("mirror", { BREAK }));

	room_list[1]->addItem(Item("hammer", { PICK, DROP, BREAK }));
	
	room_list[2]->addItem(Item("water", { FILL }));
	
	room_list[3]->addItem(Item("bottle", { PICK, DROP, FILL }));

	room_list[4]->addItem(Item("locker", { OPEN }));


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
	else if (verb == "open") current_action = OPEN;
	else if (verb == "fill") current_action = FILL;
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
	case OPEN: doOpen(); break;
	case FILL: doFill(); break;
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

void Game::doOpen() {
	if (object != verb)
	{
		Item toOpen = room_list[current_room]->getItem(object);
		if (toOpen.first != "NOITEM")
		{
			if (checkAction(toOpen, OPEN))
			{
				if (toOpen.first.compare("locker") == 0)
				{
					room_list[current_room]->changeState(object);
					cout << "You opened the locker.\n There's a small lighter and a rugged paper inside it.\n" << endl;
				}
			}
			else cout << "You can't open that" << endl;
		}
		else cout << "You don't see a " << object << endl;
	}
	else {
		cout << "What do you want to open?" << endl;
		cout << ">";
		getline(cin, object);
		doRead();
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
			cout << "These are the items in your inventory: " << endl;
			for (list<string>::const_iterator it = inv.begin(); it != inv.end(); ++it)
				cout << *it << endl;
		}
		else if (object.compare("room") == 0)
		{
			cout << "These are the items you can see in the room: " << endl;
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
	if (object != verb)
	{
		Item toRead = player->getItem(object);
		if (toRead.first != "NOITEM")
		{
			if(checkAction(toRead, READ))
			{
				if (toRead.first.compare("note") == 0)
				{
					cout << "Hi there, \n"
						"Maybe you're wondering why you're here, maybe not.\n"
						"Or Maybe this is all a dream and maybe, just maybe, you're trapped \n"
						"inside a manor and need to find your own way out.\n"
						"Good Luck.\n" << endl;
				}
				else if (toRead.first.compare("paper") == 0) cout << "Sometimes, vapor can help you see through things you don't see otherwise.\n";
			}
			else cout << "You can't read that" << endl;
		}
		else cout << "You don't have a " << object << endl;
	}
	else {
		cout << "What do you want to read?" << endl;
		cout << ">";
		getline(cin, object);
		doRead();
	}
}

void Game::doBreak() {
	if (object != verb)
	{
		Item toBreak = room_list[current_room]->getItem(object);
		if (toBreak.first != "NOITEM")
		{
			if (checkAction(toBreak, BREAK))
			{
				cout << "What do you want to break the " << object << " with?" << endl;
				cout << ">";
				getline(cin, object);
				Item result = player->getItem(object);

				if (checkAction(result, BREAK))
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
			else cout << "You can't break a " << toBreak.first << endl;
			
		}
		else cout << "You don't have a " << object << endl;
	}
	else {
		cout << "What do you want to break?" << endl;
		cout << ">";
		getline(cin, object);
		doBreak();
	}
}

void Game::doFill() {
	if (object != verb)
	{
		Item toFill = player->getItem(object);
		if (toFill.first != "NOITEM")
		{
			if (checkAction(toFill, FILL))
			{
				cout << "What do you want to fill the " << object << " with?" << endl;
				cout << ">";
				getline(cin, object);
				Item result = room_list[current_room]->getItem(object);

				if (checkAction(result, FILL))
				{
					room_list[current_room]->changeState(toFill.first);
					cout << "You filled the " << toFill.first << " with " << object << endl;
				}
				else
				{
					cout << "You can't fill the " << toFill.first << " with a " << object << endl;
					return;
				}
			}
			else cout << "You can't fill a " << toFill.first << endl;
			
		}
		else cout << "You don't have a " << object << endl;
	}
	else {
		cout << "What do you want to fill?" << endl;
		cout << ">";
		getline(cin, object);
		doBreak();
	}
}

string Game::describeRoom(const int roomIndex){
	return room_list[current_room]->toString();
}

bool Game::checkAction(const Item item, const Actions action)
{
	bool canAction = false;
	for (available_actions::const_iterator it = item.second.begin(); it != item.second.end() && !canAction; ++it)
	{
		if (*it == action)
			canAction = true;
	}

	return canAction;
}