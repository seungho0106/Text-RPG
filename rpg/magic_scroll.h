#ifndef MAGICSCROLL_H
#define MAGICSCROLL_H

class Item;
class Unit;
#include "consumable_item.h"

class MagicScroll : public ConsumableItem {
protected:
public:
    MagicScroll();
    virtual ~MagicScroll();
    
    virtual void printFullSpec(ostream &out);
    
    virtual bool use(Unit *unit);
    
    Item *clone();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

#endif
