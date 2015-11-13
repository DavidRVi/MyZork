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
	return c_inventory.getItem(itemName);
}
