#ifndef MERCHANT_H
#define MERCHANT_H

class Unit;
class ItemWrapper;
#include "backpack.h"

class Merchant : public Unit { // child class of class Unit
protected:
	Backpack<ItemWrapper> *itemsToSell;
    int numItemsToSell;
	Backpack<ItemWrapper> *itemsBought;
    int numItemsBought;

public:
	Merchant();
	virtual ~Merchant();
	
	bool isMerchant();

	void move(int dir);
    void interact(Unit *unit);
    
	void add(Item *itemSold);
    void buy();
    void sell();
    
    int atoi(string input);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
