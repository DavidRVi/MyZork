#ifndef _CORRIDOR_H_
#define _CORRIDOR_H_

#include "room.h"

class Corridor :public Room {
private:
	enum room_state {INITIAL, NO_HAMMER };
	room_state current_state;
public:
	Corridor();
	~Corridor(){};
	string toString() const;
	void changeState(const string itemName);
};

#endif