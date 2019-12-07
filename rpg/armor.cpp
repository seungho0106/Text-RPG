#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "equippable_item.h"
#include "armor.h"

Armor::Armor() : EquippableItem() {
	def = 0;
	bodyPartID = ARMOR_BODYPART_ID_NONE;
}

Armor::Armor(Armor &other) : EquippableItem(other) {
	def = other.def;
	bodyPartID = other.bodyPartID;
}

Armor::Armor(char shape, string name, int price, bool disposable, bool removable, int durability, int def, int bodyPartID)
	: EquippableItem(shape, name, price, disposable, removable, durability) {
	this->def = def;
	this->bodyPartID = bodyPartID;
}

Armor::~Armor() {
}

void Armor::printFullSpec(ostream &out) {
		EquippableItem::printFullSpec(out);
		out << "def(" << setw(6) << def << ")";
}

int Armor::getDef() {
	return def;
}

int Armor::getBodyPartID() {
	return bodyPartID;
}

bool Armor::isArmor() {
	return true;
}

bool Armor::use(Unit *unit) {
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

Armor *createRandomArmor() {
	int randBodyPartID = rand() % (WEAPON_BODYPART_ID_LEFT_HAND + 1);
	return getRandomArmor(randBodyPartID);
}

Armor *getRandomArmorByName(string name) {
	while (true) {
		Armor *curArmor = createRandomArmor();
		if (curArmor->getName() == name) {
			return curArmor;
		}
		else {
			delete curArmor;
		}
	}
	return NULL;
}

// post-condition: id there is no such body part then random item will be return.
Armor *getRandomArmor(int pBodyPartID) {
	char shape[MAX_NUM_RANDOM_ARMORS] = { ARMOR_HEAD_SHAPE,			ARMOR_CHEST_SHAPE,		ARMOR_GLOVES_SHAPE,			ARMOR_BACK_SHAPE,		ARMOR_LEGS_SHAPE,		ARMOR_FEET_SHAPE,		ARMOR_HEAD_SHAPE,		ARMOR_CHEST_SHAPE,		ARMOR_GLOVES_SHAPE,			ARMOR_BACK_SHAPE,		ARMOR_LEGS_SHAPE,		ARMOR_FEET_SHAPE,	ARMOR_HEAD_SHAPE,		ARMOR_CHEST_SHAPE,			ARMOR_BACK_SHAPE,	ARMOR_GLOVES_SHAPE,			ARMOR_LEGS_SHAPE,		ARMOR_FEET_SHAPE, };
	char name[MAX_NUM_RANDOM_ARMORS][80] = { "Leather Cap",				"Leather Armor",		"Leather Gloves",			"Cloth Cape",			"Leather Pants",		"Leather Boots",		"Chain Helm",			"Chain Mail",			"Chain Gloves",				"Silk Cape",			"Chain Leggings",		"Chain Greaves",	"Diamond Helm",			"Diamond Plate",			"Elf Robe",			"Diamond Gauntlets",		"Diamond Leggings",		"Diamond Boots", };
	int price[MAX_NUM_RANDOM_ARMORS] = { 800,							1200,					650,						800,					900,					750,					2400,					4000,					1800,						3000,					3600,					2000,				9000,					15000,						10000,				7000,						12000,					8000, };
	int durability[MAX_NUM_RANDOM_ARMORS] = { 8,							15,						6,							10,						10,						8,						30,						50,						25,							40,						40,						30,					60,						90,							100,				45,							70,						45, };
	int def[MAX_NUM_RANDOM_ARMORS] = { 1,							2,						1,							1,						2,						1,						4,						8,						4,							3,						7,						5,					18,						24,							10,					12,							20,						15, };
	int bodyPartID[MAX_NUM_RANDOM_ARMORS] = { ARMOR_BODYPART_ID_HEAD, ARMOR_BODYPART_ID_CHEST, ARMOR_BODYPART_ID_GLOVES, ARMOR_BODYPART_ID_BACK, ARMOR_BODYPART_ID_LEGS, ARMOR_BODYPART_ID_FEET, ARMOR_BODYPART_ID_HEAD, ARMOR_BODYPART_ID_CHEST, ARMOR_BODYPART_ID_GLOVES, ARMOR_BODYPART_ID_BACK, ARMOR_BODYPART_ID_LEGS, ARMOR_BODYPART_ID_FEET, ARMOR_BODYPART_ID_HEAD, ARMOR_BODYPART_ID_CHEST, ARMOR_BODYPART_ID_BACK, ARMOR_BODYPART_ID_GLOVES, ARMOR_BODYPART_ID_LEGS,  ARMOR_BODYPART_ID_LEGS, };

	int randItemIndex = rand() % MAX_NUM_RANDOM_ARMORS;

	if (pBodyPartID != -1) {
		for (int i = 0; i < RANDOM_EQUIPPABLE_ITEM_MAX_ITER && pBodyPartID != bodyPartID[randItemIndex]; i++) {
			randItemIndex = rand() % MAX_NUM_RANDOM_ARMORS;
		}
	}

	return new Armor(shape[randItemIndex],
		name[randItemIndex],
		price[randItemIndex],
		false,
		true,
		durability[randItemIndex],
		def[randItemIndex],
		bodyPartID[randItemIndex]);
}

Item *Armor::clone() {
	return new Armor(*this); // calling copy contructor to copy all the data from me
}

void Armor::save(ostream &out) {
    EquippableItem::save(out);
    out << "#-------------------- class Armor" << endl;
    out << "# def" << endl;
    out << def << endl;
    out << "# bodyPartID" << endl;
    out << bodyPartID << endl;
}

void Armor::load(istream &in) {
    char buf[250];
    EquippableItem::load(in);
//    out << "#-------------------- class Armor" << endl;
    in.getline(buf, 250);
//    out << "# def" << endl;
    in.getline(buf, 250);
//    out << def << endl;
    in >> def >> buf[0];
//    out << "# bodyPartID" << endl;
    in.getline(buf, 250);
//    out << bodyPartID << endl;
    in >> bodyPartID >> buf[0];
}

string Armor::getClassTypeName() {
    return string("Armor");
}
