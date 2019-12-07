#ifndef WEAPON_H
#define WEAPON_H

class Item;
class Unit;
#include "equippable_item.h"

class Weapon : public EquippableItem {
protected:
	int atk;
	int numHands;
public:
	Weapon();
	Weapon(Weapon &other);
	Weapon(char shape, string name, int price, bool disposable, bool removable, int durability, int atk, int numHands);
	virtual ~Weapon();

	virtual void printFullSpec(ostream &out);

	int getAtk();
	int getNumHands();

	bool isWeapon();

	bool use(Unit *unit);

	Item *clone();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

Weapon *createRandomWeapon();
Weapon *getRandomWeaponByName(string name);
Weapon *getRandomWeapon(int pNumHands);

#endif
