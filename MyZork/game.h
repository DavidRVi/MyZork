#ifndef _GAME_H_
#define _GAME_H_

#include "character.h"
#include "room.h"
#include <vector>

class Game {
private:
	vector<Room*> room_list;
	Character *player;
	int current_room;
	Actions current_action;
	string verb, object;
	bool gameActive;

	void initializeGame();								//creates rooms, items, doors and such
	void playGame();									//game loop
	void processUserInput(const string userInput);		//splits the user input in two words for the game to understand
	void doAction(const Actions action);				//execute a game action
	string describeRoom(const int roomIndex);			//Returns a string corresponding to the room description
	Directions getDirection(const string object);		//Get a Direction corresponding to a string describing the direction

	void doGo();
	void doQuit();
	void doPick();
	void doDrop();
	void doRead();
	void doBreak();
	void doSee();
	void doOpen();
	void doPut();
	void doUse();
	void doFill();
	void doNothing();

	void enterCode();									//Function that checks if the secret code is correct

	bool checkAction(const Item item, const Actions action);	//returns true if the given item can do the given action; false otherwise
public:
	Game();
	~Game();
	void Start();
};

#endif