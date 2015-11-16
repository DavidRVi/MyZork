#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <list>
#include "utils.h"
#include "inventory.h"

using namespace std;

class Room
{
protected:
	string name;
	string description;

	Inventory room_inventory;
	list<Door> doors;
public:
	Room(){};
	Room(const string aName);
	Room(const string aName, const string aDescription);
	void setDescription(const string aDescription);
	void addItem(const Item item);		//Add a given item
	void addDoor(const Door door); //Add a door in a direction, and check there's no door before in that direction
	list<string> getItems() const;
	list<Door> getDoors() const;
	virtual string toString() const;
	Item removeItem(const string itemName); //Removes an item from room inventory and return it.
	int isDoor(const Directions dir) const; //Returns the index of the room that is in the given Direction if there's a door in that direction
};

#endif