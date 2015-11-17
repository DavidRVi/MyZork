#ifndef _LOCKERROOM_H_
#define _LOCKERROOM_H_

#include "room.h"
class LockerRoom :public Room {
private:
	enum room_state{ INITIAL, OPEN_LOCKER, NO_LIGHTER, NO_PAPER, FULL};
	room_state current_state;
public:
	LockerRoom();
	~LockerRoom(){};
	string toString() const;
	void changeState(const string itemName);
};

#endif