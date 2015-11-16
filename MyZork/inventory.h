#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <map>
#include <list>
#include <string>
#include "utils.h"

typedef std::map<const std::string, const available_actions> t_inventory;

class Inventory {
private:
	t_inventory items;

public:
	Inventory(){  };
	~Inventory(){ };
	void addItem(const Item anItem);
	Item removeItem(const std::string itemName);
	Item getPickItem(const std::string itemName) const;
	const std::list<std::string> getItemsNames() const;
	const available_actions getAvailableActions(const std::string itemName) const;
	Item getItem(const std::string itemName) const;
};

#endif