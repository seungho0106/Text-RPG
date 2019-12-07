#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "equippable_item.h"
#include "armor.h"
#include "weapon.h"

EquippableItem::EquippableItem() {
	durability = 0;
}

EquippableItem::EquippableItem(char shape, string name, int price, bool disposable, bool removable, int durability) : Item(shape, name, price, disposable, removable) { // general constructor
	this->durability = durability;
}

EquippableItem::~EquippableItem() {
}

void EquippableItem::printFullSpec(ostream &out) {
		Item::printFullSpec(out);
}

bool EquippableItem::isEquippable() {
	return true;
}

bool EquippableItem::isArmor() {
	return false;
}

bool EquippableItem::isWeapon() {
	return false;
}

void EquippableItem::save(ostream &out) {
    Item::save(out);
    out << "#-------------------- class EquippableItem" << endl;
    out << "# durability" << endl;
    out << durability << endl;
}

void EquippableItem::load(istream &in) {
    Item::load(in);
    char buf[250];
    //out << "#-------------------- class EquippableItem" << endl;
    in.getline(buf, 250);
//    out << "# durability" << endl;
    in.getline(buf, 250);
//    out << durability << endl;
    in >> durability >> buf[0];
}
