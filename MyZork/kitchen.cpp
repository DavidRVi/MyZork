#include "kitchen.h"
#include <iostream>

Kitchen::Kitchen() {
	current_state = INITIAL;
	name = "Kitchen";
	description = "You're in a room covered in tiles,\n"
		"there are two doors, one in the west side, and another one in the north side. \n";
}

string Kitchen::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	switch (current_state) {
	case INITIAL: result += "In the east side there is a kitchen with an empty pot on it.\nYou look at the ceiling and notice there's a mirror.\n"; break;
	case KITCHEN_ON: result += "The kitchen is heating an empty pot.\nYou look at the ceiling and notice there's a mirror."; break;
	case WATER_POT: result += "In the east side there is a kitchen with a pot filled with water\n You look at the ceiling and notice there's a mirror.\n";  break;
	case VAPOR_ROOM: result += "The vapor produced by the boiling water lets you see a hidden message in the mirror placed in the ceiling.\n It says: \"KONAMI\""; break;
	default: break;
	}
	list<string> items = dropped_items.getItemsNames();
	for (list<string>::const_iterator it = items.begin(); it != items.end(); ++it)
		result += "There is a " + *it + " on the floor.\n";
	result += "\n\n";
	return result;
}

void Kitchen::changeState(string itemName) {
	switch (current_state){
	case INITIAL:
		if (itemName.compare("lighter") == 0)
			current_state = KITCHEN_ON;
		else if (itemName.compare("water") == 0)
			current_state = WATER_POT;
		break;
	case KITCHEN_ON:
		if (itemName.compare("water") == 0)
		{
			current_state = VAPOR_ROOM;
			std::cout << "The water begins to boil after waiting a bit... covering the room with vapor, \nYou can see the mirror in the ceiling is tarnished and hided a secret message:\n \"KONAMI\"\n";
			break;
		}
		break;
	case WATER_POT:
		if (itemName.compare("lighter") == 0)
		{
			current_state = VAPOR_ROOM;
			std::cout << "The water begins to boil after waiting a bit... covering the room with vapor, \nYou can see the mirror in the ceiling is tarnished and hided a secret message: \"KONAMI\"";
		}
		break;
	case VAPOR_ROOM: break;
	}
}