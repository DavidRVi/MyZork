#ifndef _GAME_H_
#define _GAME_H_

#include "character.h"
#include "room.h"
#include <vector>

class Game {
private:
	vector<Room> room_list;
	Character *player;
	int current_room;
	Actions current_action;
	string verb, object;
	bool gameActive;

	void initializeGame();
	void playGame();
	void processUserInput(const string userInput);
	void doAction(const Actions action);
	string describeRoom(const int roomIndex);

	void doGo();
	void doQuit();
	void doPick();
	void doDrop();
	void doRead();
	void doBreak();
	void doNothing();
public:
	Game();
	~Game();
	void Start();
};

#endif