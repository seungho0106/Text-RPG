#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "item.h"
#include "equippable_item.h"
#include "unit.h"
#include "weapon.h"

Weapon::Weapon() : EquippableItem() {
	atk = 0;
	numHands = 0;
}

Weapon::Weapon(Weapon &other) : EquippableItem(other) {
	atk = other.atk;
	numHands = other.numHands;
}

Weapon::Weapon(char shape, string name, int price, bool disposable, bool removable, int durability, int atk, int numHands)
	: EquippableItem(shape, name, price, disposable, removable, durability) {
	this->atk = atk;
	this->numHands = numHands;
}

Weapon::~Weapon() {
}

void Weapon::printFullSpec(ostream &out) {
	if (this != NULL) {
		EquippableItem::printFullSpec(out);
		out << "atk(" << setw(6) << atk << ")";
	}
}

int Weapon::getAtk() {
	return atk;
}

int Weapon::getNumHands() {
	return numHands;
}

bool Weapon::isWeapon() {
	return true;
}

bool Weapon::use(Unit *unit) {
	if (unit == NULL) {
		cout << "Weapon::use(): if (unit == NULL) {" << endl;
		exit(1);
	}

	if (unit->equip(this)) {
		removed = true;
		return true;
	}
	else {
		return false;
	}

	return false;
}

Item *Weapon::clone() {
	return new Weapon(*this); // calling copy contructor to copy all the data from me
}

Weapon *createRandomWeapon() {
	int randNumHands = rand() % 2;

	return getRandomWeapon(randNumHands);
}

Weapon *getRandomWeaponByName(string name) {
	while (true) {
		Weapon *curWeapon = createRandomWeapon();
		if (curWeapon->getName() == name) {
			return curWeapon;
		}
		else {
			delete curWeapon;
		}
	}
	return NULL;
}


#define WEAPON_ONE_HAND_SHAPE '!'
#define WEAPON_TWO_HAND_SHAPE '?'
#define MAX_NUM_RANDOM_WEAPONS 8
Weapon *getRandomWeapon(int pNumHands) {
	char shape[MAX_NUM_RANDOM_WEAPONS] = { WEAPON_ONE_HAND_SHAPE, WEAPON_TWO_HAND_SHAPE,  WEAPON_ONE_HAND_SHAPE, WEAPON_TWO_HAND_SHAPE, WEAPON_ONE_HAND_SHAPE, WEAPON_TWO_HAND_SHAPE, WEAPON_ONE_HAND_SHAPE, WEAPON_TWO_HAND_SHAPE };
	char name[MAX_NUM_RANDOM_WEAPONS][80] = { "Longsword",          "Greatsword",           "Mythril Sword",         "Claymore",            "Dragon Sword",       "Deathbringer",          "Excalibur",            "Ragnarok" };
	int price[MAX_NUM_RANDOM_WEAPONS] = {       1000,                   2000,                  5000,                    8000,                 10000,                  15000,                  100000,                200000 };
	int durability[MAX_NUM_RANDOM_WEAPONS] = {  15,                     30,                    30,                      60,                   50,                     100,                    999,                   999 };
	int atk[MAX_NUM_RANDOM_WEAPONS] = {         5,                      8,                     15,                      25,                   30,                     50,                     99,                    150 };
	int numHands[MAX_NUM_RANDOM_WEAPONS] = {    1,                      2,                     1,                       2,                    1,                      2,                      1,                     2 };

	int randItemIndex = rand() % MAX_NUM_RANDOM_WEAPONS;
	if (pNumHands != -1) {
		for (int i = 0; i < RANDOM_EQUIPPABLE_ITEM_MAX_ITER && pNumHands != numHands[randItemIndex]; i++) {
			randItemIndex = rand() % MAX_NUM_RANDOM_WEAPONS;
		}
	}

	return new Weapon(shape[randItemIndex],
		name[randItemIndex],
		price[randItemIndex],
		false,
		true,
		durability[randItemIndex],
		atk[randItemIndex],
		numHands[randItemIndex]);
}

void Weapon::save(ostream &out) {
    EquippableItem::save(out);
    out << "#-------------------- class Weapon" << endl;
    out << "# atk" << endl;
    out << atk << endl;
    out << "# numHands" << endl;
    out << numHands << endl;
}

void Weapon::load(istream &in) {
    char buf[250];
    EquippableItem::load(in);
    //    out << "#-------------------- class Weapon" << endl;
    in.getline(buf, 250);
    //    out << "# atk" << endl;
    in.getline(buf, 250);
    //    out << atk << endl;
    in >> atk >> buf[0];
    //    out << "# numHands" << endl;
    in.getline(buf, 250);
    //    out << numHands << endl;
    in >> numHands >> buf[0];
}

string Weapon::getClassTypeName() {
    return string("Weapon");
}

