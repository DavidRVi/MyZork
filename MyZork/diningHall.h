#ifndef _DININGHALL_H_
#define _DININGHALL_H_

#include "room.h"
class DiningHall :public Room {
private:
	enum room_state{INITIAL, NO_BOTTLE};
	room_state current_state;
public:
	DiningHall();
	~DiningHall(){};
	string toString() const;
	void changeState(const string itemName);
};

#endif