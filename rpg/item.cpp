#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "consumable_item.h"
#include "health_potion.h"
#include "mana_potion.h"
#include "magic_scroll.h"
#include "armor.h"
#include "weapon.h"
#include "inventory.h"

//==============================================================================
// class ItemWrapper
//==============================================================================
ItemWrapper::ItemWrapper() {
    item = NULL;
}

ItemWrapper::ItemWrapper(Item *item) {
    this->item = item;
}

ItemWrapper::~ItemWrapper() {
//    if (item != NULL) {
//        delete item;
//        item = NULL;
//    }
}

void ItemWrapper::printFullSpec(ostream &out) {
    if (item != NULL) {
        item->printFullSpec(out);
    }
}

bool ItemWrapper::operator<(const ItemWrapper &other) {
    if (item == NULL) {
        return false;
    }
    return item->getPrice() < other.item->getPrice();
}

bool ItemWrapper::operator<=(const ItemWrapper &other) {
    if (item == NULL) {
        return false;
    }
    return item->getPrice() <= other.item->getPrice();
}

bool ItemWrapper::operator>(const ItemWrapper &other) {
    if (item == NULL) {
        return false;
    }
    return item->getPrice() > other.item->getPrice();
}

bool ItemWrapper::operator>=(const ItemWrapper &other) {
    if (item == NULL) {
        return false;
    }
    return item->getPrice() >= other.item->getPrice();
}

bool ItemWrapper::operator==(const ItemWrapper &other) {
    if (item == NULL) {
        return false;
    }
    return item->getName() == other.item->getName();
}

ostream &operator<<(ostream &out, const ItemWrapper &obj) {
    if (obj.item == NULL) {
        return out;
    }
    out << *(obj.item);
    return out;
}

void ItemWrapper::save(ostream &out) {
    out << "#-------------------- class ItemWrapper" << endl;
    if (item != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        out << "# Item ID" << endl;
        out << item->getClassTypeName() << endl;
        item->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
}

void ItemWrapper::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class ItemWrapper" << endl;
    in.getline(buf, 250);
//    if (item != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        out << "# Item ID" << endl;
//        out << item->getClassTypeName() << endl;
//        item->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        in.getline(buf, 250);
        string classTypeName = "";
        in >> classTypeName >> buf[0];
        item = Item::createItemByID(classTypeName);
        item->load(in);
    }
    else {
        item = NULL;
    }
}


Item::Item() {
    shape = 'P';    
    name = "";
    price = 0;
    
    disposable = false;
    removable = false;
    
    removed = false;
}

Item::Item(char shape, string name, int price, bool disposable, bool removable) {
    this->shape = shape;
    
    this->name = name;
    this->price = price;
    
    this->disposable = disposable;
    this->removable = removable;
    
    removed = false;
}

Item::~Item() {
}

void Item::print() {
    cout << shape;
}

void Item::printFullSpec(ostream &out) {
	if (this != NULL) {
		out << shape << ":" << setw(30) << left << name << right << setw(7) << price << "g ";
	}
}

char Item::getShape() {
    return shape;
}

string Item::getName() {
    return name;
}

int Item::getPrice() {
    return price;
}

bool Item::isDisposable() {
    return disposable;
}

bool Item::isRemovable() {
    return removable;
}

bool Item::isRemoved() {
    return removed;
}

bool Item::isConsumable() {
    return false;
}

bool Item::isEquippable() {
    return false;
}

void Item::save(ostream &out) {
    out << "#-------------------- class Item" << endl;
    out << "# shape" << endl;
    out << shape << endl;
    out << "# name" << endl;
    out << name << endl;
    out << "# price" << endl;
    out << price << endl;
}

void Item::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class Item" << endl;
    in.getline(buf, 250);
//    out << "# shape" << endl;
    in.getline(buf, 250);
//    out << shape << endl;
    in >> shape >> buf[0];
//    out << "# name" << endl;
    in.getline(buf, 250);
//    out << name << endl;
    in.getline(buf, 250);
    name = buf;
//    out << "# price" << endl;
    in.getline(buf, 250);
//    out << price << endl;
    in >> price >> buf[0];
}

ostream &operator<<(ostream &out, const Item &obj) {
    out << obj.shape;
    return out;
}

#define ITEM_TYPE_WEAPON 0
#define ITEM_TYPE_ARMOR (ITEM_TYPE_WEAPON+1)
#define ITEM_TYPE_CONSUMABLE (ITEM_TYPE_ARMOR+1)

#define NUM_ITEM_TYPES (ITEM_TYPE_CONSUMABLE+1)

Item *Item::createRandomItem() {
    int randType = rand() % NUM_ITEM_TYPES;
    if (randType == ITEM_TYPE_CONSUMABLE) {
        return ConsumableItem::createRandomConsumable();
    }
    else if (randType == ITEM_TYPE_ARMOR) {
        return createRandomArmor();
    }
    else if (randType == ITEM_TYPE_WEAPON) {
        return createRandomWeapon();
    }
    
    return NULL;
}

Item *Item::createItemByID(string classTypeName) {
    if (classTypeName == "Armor") {
        return new Armor();
    }
    else if (classTypeName == "Weapon") {
        return new Weapon();
    }
    else if (classTypeName == "HealthPotion") {
        return new HealthPotion();
    }
    else if (classTypeName == "ManaPotion") {
        return new ManaPotion();
    }
    else if (classTypeName == "MagicScroll") {
        return new MagicScroll();
    }
    
    cout << "Item::createItemByID(): error - unknown class type name: " << classTypeName << endl;
    exit(1);
    return NULL;
}
