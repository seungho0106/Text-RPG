#ifndef MANA_POTION_H
#define MANA_POTION_H

class Item;
class Unit;
#include "consumable_item.h"

class ManaPotion : public ConsumableItem {
protected:
    int mp;
    
public:
    ManaPotion();
    ManaPotion(char shape, string name, int price, int mp);
    virtual ~ManaPotion();
    
    virtual void printFullSpec(ostream &out);
    
    virtual bool use(Unit *unit);
    
    Item *clone();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

#endif
