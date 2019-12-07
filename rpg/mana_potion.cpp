#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "mana_potion.h"

#include "sim.h"
extern Sim *sim;

ManaPotion::ManaPotion() : ConsumableItem(MANA_POTION_SHAPE, MANA_POTION_NAME, MANA_POTION_PRICE, true, false) {
    mp = MANA_POTION_MP;
}

ManaPotion::ManaPotion(char shape, string name, int price, int mp) : ConsumableItem(shape, name, price, true, false) {
    this->mp = mp;
}

ManaPotion::~ManaPotion() {
}

void ManaPotion::printFullSpec(ostream &out) {
    ConsumableItem::printFullSpec(out);
}

bool ManaPotion::use(Unit *unit) {
    if (unit->getMp() == HERO_MAX_MP) {
        sim->systemMessage = "error: Already at max MP!";
        return false;
    }
    else {
        unit->incMp(mp);
        return true;
    }
}

Item *ManaPotion::clone() {
    return new ManaPotion();
}

void ManaPotion::save(ostream &out) {
    ConsumableItem::save(out);
    out << "#-------------------- class ManaPotion" << endl;
    out << "# mp" << endl;
    out << mp << endl;
}

void ManaPotion::load(istream &in) {
    ConsumableItem::load(in);
    char buf[250];
    //out << "#-------------------- class ManaPotion" << endl;
    in.getline(buf, 250);
    //out << "# mp" << endl;
    in.getline(buf, 250);
    //out << mp << endl;
    in >> mp >> buf[0];;
}

string ManaPotion::getClassTypeName() {
    return string("ManaPotion");
}
