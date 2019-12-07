#ifndef HERO_H
#define HERO_H

#include "unit.h"
//class Unit;
class Item;
class Weapon;
class Armor;
class Inventory;
class Paperdoll;

class Hero : public Unit {
protected:
public:
    Inventory *slots;
    Paperdoll *paperdoll;
    
    int projectileIndex;
    char projectileIndexShape;
    
public:
	Hero();
	virtual ~Hero();

    void reset();
    
	void printStat();
	
	int getInventorySize();
    Inventory *getSlots();
	Item *getInventoryItemAt(int itemIndex);
    Item *removeInventoryItemAt(int itemIndex);

	bool isHero();
	bool isInventoryEmpty();
    bool isInventoryFull();

	void move(int dir);
	void interact(Unit *unit);
    void levelUp();

	void useItem(int itemIndex);
	void add(Item *itemToBuy);
	    
    bool equip(Item *itemToEquip);
    void unequip(int bodyPartID); // calling from main()
    
    int getProjectileIndex();
    void changeProjectileIndex();
//    void castMagic(int skillNumber);
//    void effect(Unit *waveUnit, Item *waveItem, Prop *waveProp, int skillNumber);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
