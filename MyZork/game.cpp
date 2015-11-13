#include "game.h"
#include <iostream>
#include <sstream>

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
	room_list.push_back(Room("Hall Room", 
		"You're in a room with white walls all around it, \n"
		"in the north wall you can see yourself reflected in a human-size mirror, \n"
		"there's a little table beneath the mirror with a note, \n"
		"you see an iron door in the east wall, \n"
		"and a wooden door in the south wall."));
	room_list[0].addItem(Item("Note", { PICK, DROP, READ }));
	room_list[0].addItem(Item("Mirror", { BREAK }));


	cout << "**********  Welcome to MyZork, version " << VERSION << "********** " << endl;
	cout << "\n";
}

void Game::playGame() {
	gameActive = true;

	string userInput;
	cout << describeRoom(current_room);

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
	case NOACTION: doNothing(); break;
	default: doNothing();
	}
}

void Game::doNothing() {
	cout << "Couldn't understand what you want to do: please use a verb that the game understands." << endl;
}

void Game::doQuit() {
	cout << "Goodbye, I hope you had some fun. Have a nice day." << endl;
	gameActive = false;
}

void Game::doGo() {

}

void Game::doPick() {

}

void Game::doDrop() {

}

void Game::doRead() {

}

void Game::doBreak() {

}

string Game::describeRoom(const int roomIndex){
	return room_list[current_room].toString();
}