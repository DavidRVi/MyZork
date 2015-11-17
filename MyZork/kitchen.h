#ifndef _KITCHEN_H_
#define _KITCHEN_H_

#include "room.h"

class Kitchen :public Room {
private:
	enum room_state {INITIAL, KITCHEN_ON, WATER_POT, VAPOR_ROOM};
	room_state current_state;
public:
	Kitchen();
	~Kitchen();
	std::string toString() const;
	void changeState(const string itemName);
};

#endif