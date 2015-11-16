#include "hallRoom.h"

HallRoom::HallRoom() {
	current_state = INITIAL;
}

HallRoom::HallRoom(const string aName){
	HallRoom();
	name = aName;
}

HallRoom::HallRoom(const string aName, const string aDescription) {
	HallRoom();
	name = aName;
	description = aDescription;
}


string HallRoom::toString() const {
	string result = "";


	return result;
}