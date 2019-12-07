#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

class Item;
class Unit;
#include "consumable_item.h"

class HealthPotion : public ConsumableItem {
protected:
	int hp;

public:
	HealthPotion();
	HealthPotion(char shape, string name, int price, int hp);
	virtual ~HealthPotion();

	virtual void printFullSpec(ostream &out);

	virtual bool use(Unit *unit);

	Item *clone();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

#endif
