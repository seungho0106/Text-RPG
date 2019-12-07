#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "health_potion.h"

#include "sim.h"
extern Sim *sim;

HealthPotion::HealthPotion() : ConsumableItem(HEALTH_POTION_SHAPE, HEALTH_POTION_NAME, HEALTH_POTION_PRICE, true, false) {
	hp = HEALTH_POTION_HP;
}

HealthPotion::HealthPotion(char shape, string name, int price, int hp) : ConsumableItem(shape, name, price, true, false) {
	this->hp = hp;
}

HealthPotion::~HealthPotion() {
}

void HealthPotion::printFullSpec(ostream &out) {
		ConsumableItem::printFullSpec(out);
}

bool HealthPotion::use(Unit *unit) {
    if (unit->getHp() == HERO_MAX_HP) {
        sim->systemMessage = "error: Already at max HP!";
        return false;
    }
    else {
	unit->incHp(hp);
	return true;
    }
}

Item *HealthPotion::clone() {
	return new HealthPotion();
}

void HealthPotion::save(ostream &out) {
    ConsumableItem::save(out);
    out << "#-------------------- class HealthPotion" << endl;
    out << "# hp" << endl;
    out << hp << endl;
}

void HealthPotion::load(istream &in) {
    ConsumableItem::load(in);
    char buf[250];
    //out << "#-------------------- class HealthPotion" << endl;
    in.getline(buf, 250);
    //out << "# hp" << endl;
    in.getline(buf, 250);
    //out << hp << endl;
    in >> hp >> buf[0];;
}

string HealthPotion::getClassTypeName() {
    return string("HealthPotion");
}
