#include "room.h"

Room::Room(const string aName)
{
	name = aName;
}

Room::Room(const string aName, const string aDescription)
{
	name = aName;
	description = aDescription;
}

void Room::setDescription(const string aDescription) {
	description = aDescription;
}

void Room::addItem(const Item item) {
	room_inventory.addItem(item);
}

void Room::dropItem(const Item item) {
	dropped_items.addItem(item);
}

void Room::addDoor(Door door) { 
	bool found = false;
	for (list<Door>::const_iterator it = doors.begin(); it != doors.end() && !found; ++it)
	{
		if (door.first == it->first)
			found = true;
	}

	if (!found)
		doors.push_back(door);
}

list<string> Room::getItems() const {
	return room_inventory.getItemsNames();
}

list<string> Room::getDroppedItems() const {
	return dropped_items.getItemsNames();
}
list<Door> Room::getDoors() const {
	return doors;
}

int Room::isDoor(Directions dir) const {
	bool exists = false;
	int roomIndex = -1;
	for (list<Door>::const_iterator it = doors.begin(); it != doors.end() && !exists; it++)
	{
		if (it->first == dir)
		{
			exists = true;
			roomIndex = it->second;
		}
	}

	if (exists)
		return roomIndex;
	else return roomIndex;
}


string Room::toString() const {
	string result = "";
	result += "======== " + name + " ========\n";
	result += description;
	list<string> items = dropped_items.getItemsNames();
	for (list<string>::const_iterator it = items.begin(); it != items.end(); ++it)
		result += "There is a " + *it + " on the floor.\n";
	result += "\n\n";
	return result;
}

void Room::changeState(const string itemName) {}

Item Room::removeItem(const string itemName) {
	if (room_inventory.getItem(itemName).first != "NOITEM")
		return room_inventory.removeItem(itemName);
	else return dropped_items.removeItem(itemName);
}

Item Room::getItem(const string itemName) const{
	if (room_inventory.getItem(itemName).first != "NOITEM")
		return room_inventory.getItem(itemName);
	else return dropped_items.getItem(itemName);
}

Item Room::getPickItem(const string itemName) const{
	return room_inventory.getPickItem(itemName);
}