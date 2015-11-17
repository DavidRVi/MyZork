#include "lockerRoom.h"

LockerRoom::LockerRoom() {
	name = "Locker Room";
	description = "You see three rows of lockers, and another 2 on the side walls.\n"
		"There are 2 doors, one on the north side and one on the east side.\n";
	current_state = INITIAL;
}

string LockerRoom::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	switch (current_state) {
	case INITIAL: result += "You can see an ajar locker in the middle row.\n"; break;
	case OPEN_LOCKER: result += "There's a small lighter and a rugged paper inside the opened locker.\n"; break;
	case NO_LIGHTER: result += "There's a rugged paper inside the opened locker.\n";  break;
	case NO_PAPER: result += "There's a small lighter inside the opened locker.\n"; break;
	case FULL: result += "There's an opened locker.\n"; break;
	default: break;
	}
	list<string> items = dropped_items.getItemsNames();
	for (list<string>::const_iterator it = items.begin(); it != items.end(); ++it)
		result += "There is a " + *it + " on the floor.\n";
	result += "\n\n";
	return result;
}

void LockerRoom::changeState(const string itemName) {
	switch (current_state){
	case INITIAL:
		if (itemName.compare("locker") == 0)
		{
			current_state = OPEN_LOCKER;
			removeItem("locker");
			addItem(Item("lighter", { PICK, DROP, USE }));
			addItem(Item("paper", { PICK, DROP, READ }));
		}
		break;
	case OPEN_LOCKER:
		if (itemName.compare("lighter")==0)
			current_state = NO_LIGHTER;
		if (itemName.compare("paper") == 0)
			current_state = NO_PAPER;
		break;
	case NO_LIGHTER:
		if (itemName.compare("paper") == 0)
			current_state = FULL;
		break;
	case NO_PAPER:
		if (itemName.compare("lighter") == 0)
			current_state = FULL;
		break;
	case FULL: break;
	}
}