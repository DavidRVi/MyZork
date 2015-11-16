#ifndef _HALLROOM_H_
#define _HALLROOM_H_

#include "room.h"

class HallRoom : public Room {
private:
	enum room_state {INITIAL, NO_NOTE, BROKEN_MIRROR, FULL};
	room_state current_state;

public:
	HallRoom();
	HallRoom(const string aName);
	HallRoom(const string aName, const string aDescription);
	~HallRoom(){};
	string toString() const;
	void changeState(const string itemName);
};

#endif