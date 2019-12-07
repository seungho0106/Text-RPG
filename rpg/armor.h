#ifndef ARMOR_H
#define ARMOR_H

class Item;
class Unit;
#include "equippable_item.h"

class Armor : public EquippableItem {
protected:
	int def;
	int bodyPartID;
public:
	Armor();
	Armor(Armor &other);
	Armor(char shape, string name, int price, bool disposable, bool removable, int durability, int def, int bodyPartID);
	virtual ~Armor();

	virtual void printFullSpec(ostream &out);

	int getDef();
	int getBodyPartID();

	bool isArmor();

	bool use(Unit *unit);

	Item *clone();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

Armor *createRandomArmor();
Armor *getRandomArmorByName(string name);
Armor *getRandomArmor(int pBodyPartID);

#endif

