#ifndef CONSUMABLE_ITEM_H
#define CONSUMABLE_ITEM_H

#include "main.h"
#include "item.h"

class ConsumableItem : public Item {
public:
	ConsumableItem();
	ConsumableItem(char shape, string name, int price, bool disposable, bool removable);
	virtual ~ConsumableItem();

	virtual void printFullSpec(ostream &out);

	bool isConsumable();
    
    static Item *createRandomConsumable();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
