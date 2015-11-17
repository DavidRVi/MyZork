#include "diningHall.h"

DiningHall::DiningHall() {
	name = "Dining Hall";
	description = "You're in a big room full of tables covered by a white mantle.\n"
		"In a corner there's a pile of wooden chairs. There are three doors \n"
		"that lead to west, south and east respectively.\n";
	current_state = INITIAL;
}

string DiningHall::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	switch (current_state) {
	case INITIAL: result += "You can see an empty glass bottle standing in a table in the center of the room.\n"; break;
	case NO_BOTTLE: break;
	default: break;
	}
	list<string> items = dropped_items.getItemsNames();
	for (list<string>::const_iterator it = items.begin(); it != items.end(); ++it)
		result += "There is a " + *it + " on the floor.\n";
	result += "\n\n";
	return result;
}

void DiningHall::changeState(const string itemName) {
	if (itemName.compare("bottle") == 0)
		current_state = NO_BOTTLE;
}