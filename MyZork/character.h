#ifndef _CHARACTER_H_
#define _CHARACTER_H_


#include "inventory.h"
class Character{
private:
	Inventory c_inventory;
public:
	Character();
	~Character();
	const std::list<std::string> getInventoryList() const;
	void pickItem(const Item anItem);
	Item dropItem(const std::string itemName);
};

#endif