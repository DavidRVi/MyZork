#include "hallRoom.h"
#include <iostream>

HallRoom::HallRoom() {
	current_state = INITIAL;
	name = "Hall Room";
	description = "You're in a room with white walls all around it.\n"
		"You see an iron door in the east wall, \n"
		"and a wooden door in the south wall.\n";
}

HallRoom::HallRoom(const string aName){
	name = aName;
}

HallRoom::HallRoom(const string aName, const string aDescription) {
	name = aName;
	description = aDescription;
}


string HallRoom::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	switch (current_state) {
	case INITIAL: result += "There's a small table beneath the mirror with a note, \n"
		"in the north wall you can see yourself reflected in a human-sized mirror.\n"; break;
	case NO_NOTE: result += "in the north wall you can see yourself reflected in a human-sized mirror.\n"; break;
	case BROKEN_MIRROR: result += "The small table broke along with the mirror, you can still reach the note. \n"
		"You can see the broken glasses of the mirror lying around the floor,\n"
		"in the wall where the mirror was supposed to be,\n"
		"carved in the wall, you can read:\n"
		"\"BDownUpLeftLeftRightA... I CAN'T STAND THIS ANYMORE!\n"
		"If only I had some way to look for it...\"\n"; break;
	case FULL: result += "The small table broke along with the mirror. \n"
		"You can see the broken glasses of the mirror lying around the floor,\n"
		"in the wall where the mirror was supposed to be,\n"
		"carved in the wall, you can read:\n"
		"\"UpDownDownRightLeftB... I CAN'T STAND THIS ANYMORE!\n"
		"If only I had some way to look for it...\"\n"; break;
	default: break;
	}
	list<string> items = dropped_items.getItemsNames();
	for (list<string>::const_iterator it = items.begin(); it != items.end(); ++it)
		result += "There is a " + *it + " on the floor.\n";
	result += "\n\n";
	return result;
}

void HallRoom::changeState(const string itemName) {
	if (itemName.compare("note") == 0)
	{
		if (current_state == BROKEN_MIRROR)
			current_state = FULL;
		else current_state = NO_NOTE;
	}
	else if (itemName.compare("mirror") == 0)
	{
		if (current_state == NO_NOTE)
		{
			current_state = FULL;
			std::cout << "The small table broke along with the mirror. \n"
				"You can see the broken glasses of the mirror lying around the floor,\n"
				"in the wall where the mirror was supposed to be,\n"
				"carved in the wall, you can read:\n"
				"\"UpDownDownRightLeftB... I CAN'T STAND THIS ANYMORE!\n"
				"If only I had some way to look for it...\"\n";
		} 
		else{
			current_state = BROKEN_MIRROR;
			std::cout << "The small table broke along with the mirror, you can still reach the note. \n"
				"You can see the broken glasses of the mirror lying around the floor,\n"
				"in the wall where the mirror was supposed to be,\n"
				"carved in the wall, you can read:\n"
				"\"UpDownDownRightLeftB... I CAN'T STAND THIS ANYMORE!\n"
				"If only I had some way to look for it...\"\n";
		}
	}
}