#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <list>
#include "utils.h"
#include "inventory.h"
//Nota: no poner tildes.
using namespace std;

class Room
{
private:
	string name;
	string description;

	Inventory room_inventory;
	list<Directions> doors;

public:
	Room(string aName);
	Room(string aName, string aDescription);
	void setDescription(const string aDescription);
	void addItem(const Item item);		//Add a given item
	void addDoor(const Directions door); //Add a door in a direction, and check there's no door before in that direction
	list<string> getItems() const;
	list<Directions> getDoors() const;
	string toString() const;
	Item removeItem(const string itemName); //Removes an item from room inventory and return it.
};

#endif