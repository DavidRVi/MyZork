#include "corridor.h"

Corridor::Corridor() {
	name = "Corridor";
	description = "You're in a narrow corridor,\n"
		"In the east side you can see a door behind a curtain,\n"
		"there's another door at both sides of the corridor, north and south.\n"
		"There's a human skeleton in the west wall, \n"
		"as if this human's last moments were not desperate, it is sitting quietly.\n";
	current_state = INITIAL;
}

string Corridor::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	switch (current_state) {
	case INITIAL: result += "There's a rusty hammer in his right hand, \n"
		"but you think it is good enough to use once more.\n"; break;
	case NO_HAMMER: break;
	default: break;
	}

	return result;
}

void Corridor::changeState(const string itemName) {
	if (itemName.compare("hammer") == 0)
		current_state = NO_HAMMER;
}