#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "health_potion.h"
#include "mana_potion.h"
#include "magic_scroll.h"
#include "consumable_item.h"


ConsumableItem::ConsumableItem() { // default constructor
}

ConsumableItem::ConsumableItem(char shape, string name, int price, bool disposable, bool removable) : Item(shape, name, price, disposable, removable) { // general constructor
}

ConsumableItem::~ConsumableItem() {
}

void ConsumableItem::printFullSpec(ostream &out) {
		Item::printFullSpec(out);
}

bool ConsumableItem::isConsumable() {
	return true;
}

#define ITEM_TYPE_CONSUMABLE_HEALTH_POTION 0
#define ITEM_TYPE_CONSUMABLE_MANA_POTION 1
#define ITEM_TYPE_CONSUMABLE_MAGIC_SCROLL 2

#define NUM_CONSUMABLE_ITEM_TYPES (ITEM_TYPE_CONSUMABLE_MAGIC_SCROLL+1)

Item *ConsumableItem::createRandomConsumable() {
    int randType = rand() % NUM_CONSUMABLE_ITEM_TYPES;
    if (randType == ITEM_TYPE_CONSUMABLE_HEALTH_POTION) {
        return new HealthPotion();
    }
    else if (randType == ITEM_TYPE_CONSUMABLE_MANA_POTION) {
        return new ManaPotion();
    }
    else if (randType == ITEM_TYPE_CONSUMABLE_MAGIC_SCROLL) {
        return new MagicScroll();
    }
    
    return NULL;
}

void ConsumableItem::save(ostream &out) {
    Item::save(out);
    out << "#-------------------- class ConsumableItem" << endl;
}

void ConsumableItem::load(istream &in) {
    Item::load(in);
    char buf[250];
    //out << "#-------------------- class ConsumableItem" << endl;
    in.getline(buf, 250);
}

