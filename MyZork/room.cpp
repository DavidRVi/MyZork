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

void Room::addDoor(Directions door) { 
	bool found = false;
	for (list<Directions>::iterator it = doors.begin(); it != doors.end() && !found; ++it)
	{
		if (door == *it)
			found = true;
	}

	if (!found)
		doors.push_back(door);
}

list<string> Room::getItems() const {
	return room_inventory.getItemsNames();
}

list<Directions> Room::getDoors() const {
	return doors;
}

string Room::toString() const {
	string result = "";

	result += name + "\n";
	result += description + "\n";
	result += "Objetos en la habitacion: \n";
	list<string> itemsNames = getItems();
	for (list<string>::const_iterator it = itemsNames.begin(); it != itemsNames.end(); ++it)
		result += *it + "\n";
	result += "Direcciones a las que NO puedes navegar: \n";
	for (list<Directions>::const_iterator it = doors.begin(); it != doors.end(); ++it)
	{
		switch (*it)
		{
		case(NORTH) : result += "Norte\n"; break;
		case(SOUTH) : result += "Sur\n"; break;
		case(EAST) : result += "Este\n"; break;
		case(WEST) : result += "Oeste\n"; break;
		}
	}

	return result;
}