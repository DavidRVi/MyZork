#include "inventory.h"

void Inventory::addItem(const Item anItem) {
	if (items.find(anItem.first) == items.end())
		items.insert(anItem);
}

Item Inventory::removeItem(const std::string itemName) {
	Item result = *(items.find(itemName));
	items.erase(itemName);
	return result;
}

const std::list<std::string> Inventory::getItemsNames() const {
	std::list<std::string> result;
	for (t_inventory::const_iterator it = items.begin(); it != items.end(); ++it)
		result.push_back(it->first);

	return result;
}

const available_actions Inventory::getAvailableActions(const std::string itemName) const {
	available_actions result;
	t_inventory::const_iterator p = items.find(itemName);
	if (p != items.end())
		result = p->second;
	
	return result;
}

Item Inventory::getItem(const std::string itemName) const {
	return *(items.find(itemName));
}