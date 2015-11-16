#include "character.h"

Character::Character() { }

Character::~Character() { }

const std::list<std::string> Character::getInventoryList() const {
	return c_inventory.getItemsNames();
}

void Character::pickItem(const Item anItem) {
	c_inventory.addItem(anItem);
}

Item Character::dropItem(const std::string itemName) {
	Item result = c_inventory.getItem(itemName);
	if (result.first != "NOITEM")
		c_inventory.removeItem(itemName);
	
	return result;
}

const std::string Character::readItem(const std::string itemName) const {
	Item result = c_inventory.getItem(itemName);
	if (result.first != "NOITEM")
	{
		bool readable = false;
		for (available_actions::const_iterator it = result.second.begin(); it != result.second.end() && !readable; ++it)
		{
			if (*it == READ)
				readable = true;
		}

		if (readable)
			return result.first;
	}
	else return "";

}

Item Character::getItem(const std::string itemName) const {
	return c_inventory.getItem(itemName);
}
