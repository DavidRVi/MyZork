#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <map>
#include <list>
#include <string>
#include "utils.h"

struct cmpitems{
	bool operator()(const std::string s1, const std::string s2) const {
		return s1 == s2;
	}
};

typedef std::multimap<const std::string, const available_actions, cmpitems> t_inventory;

class Inventory {
private:
	t_inventory items;

public:
	Inventory(){  };
	~Inventory(){ };
	void addItem(const Item anItem);
	void removeItem(const std::string itemName);
	const std::list<std::string> getItemsNames() const;
	const available_actions getAvailableActions(const std::string itemName) const;

};

#endif