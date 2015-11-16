#ifndef _UTILS_H_
#define _UTILS_H_

enum Directions { NORTH, SOUTH, WEST, EAST, NODIRECTION };

enum Actions { GO, PICK, DROP, READ, BREAK, SEE, QUIT, NOACTION };

typedef std::list<Actions> available_actions;		// will define a list of available actions for an item
typedef std::pair<std::string, available_actions> Item;	// an item is composed of its name and a list of available actions that can be made with it.
typedef std::pair<Directions, int> Door;			// A door will be a pair composef of a direction that it leads to and the index of the room he leads to.

#endif