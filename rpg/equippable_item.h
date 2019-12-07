#ifndef EQUIPPABLE_ITEM_H
#define EQUIPPABLE_ITEM_H

#include "item.h"

class EquippableItem : public Item {
protected:
	int durability;
public:
	EquippableItem();
	EquippableItem(char shape, string name, int price, bool disposable, bool removable, int durability);
	virtual ~EquippableItem();

	virtual void printFullSpec(ostream &out);

	bool isEquippable();

	virtual bool isArmor();
	virtual bool isWeapon();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
