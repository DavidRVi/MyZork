#ifndef _UTILS_H_
#define _UTILS_H_

enum Directions { NORTH, SOUTH, WEST, EAST };

enum Actions {PICK, DROP, READ, QUIT};

typedef std::list<Actions> available_actions;		// will define a list of available actions for an item
typedef std::pair<std::string, available_actions> Item;	// an item is composed of its name and a list of available actions that can be made with it.

#endif