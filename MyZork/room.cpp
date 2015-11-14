#include "room.h"

Room::Room(string aName)
{
	name = aName;
}

Room::Room(string aName, string aDescription)
{
	name = aName;
	description = aDescription;
}

void Room::setDescription(string aDescription) {
	description = aDescription;
}

void Room::addItem(const Item item) {
	room_inventory.addItem(item);
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

	result += name + "\n";
	result += description + "\n";
	result += "Objetos en la habitacion: \n";
	list<string> itemsNames = getItems();
	for (list<string>::const_iterator it = itemsNames.begin(); it != itemsNames.end(); ++it)
		result += *it + "\n";
	result += "Direcciones a las que puedes navegar: \n";
	for (list<Door>::const_iterator it = doors.begin(); it != doors.end(); ++it)
	{
		switch ((*it).first)
		{
		case(NORTH) : result += "Norte\n"; break;
		case(SOUTH) : result += "Sur\n"; break;
		case(EAST) : result += "Este\n"; break;
		case(WEST) : result += "Oeste\n"; break;
		}
	}

	return result;
}

Item Room::removeItem(const string itemName) {
	return room_inventory.removeItem(itemName);
}