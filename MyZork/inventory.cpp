#include "inventory.h"

void Inventory::addItem(const Item anItem) {
	//if (items.find(anItem.first) == items.end())
	items.insert(anItem);
}

Item Inventory::getPickItem(const std::string itemName) const {
	Item result = Item("NOITEM", {});
	t_inventory::const_iterator it = items.find(itemName);
	if (it != items.end())
	{
		bool pickable = false;
		for (available_actions::const_iterator it2 = it->second.begin(); it2 != it->second.end() && !pickable; it2++)
		{
			if (*it2 == PICK)
				pickable = true;
		}
		if (pickable)
			result = *it;

	}
	
	return result;
}

Item Inventory::removeItem(const std::string itemName) {
	Item result = Item("NOITEM", {});
	t_inventory::iterator it = items.find(itemName);
	if (it != items.end())
	{
		result = *it;
		items.erase(itemName);
	}
		

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
	Item result = Item( "NOITEM", {} );
	if (items.find(itemName) != items.end())
		result = *(items).find(itemName);

	return result;
}