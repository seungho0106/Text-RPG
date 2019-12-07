#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "board.h"
#include "item.h"
#include "armor.h"
#include "weapon.h"
#include "health_potion.h"
#include "prop.h"
#include "inventory.h"
#include "paperdoll.h"
#include "projectile.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

Hero::Hero() : Unit(HERO_SHAPE, HERO_START_ROW, HERO_START_COL, DIR_NONE, 0, HERO_MAX_HP, HERO_MAX_HP, HERO_MAX_MP, HERO_MAX_MP, HERO_DEFAULT_ATK, HERO_DEFAULT_DEF, HERO_DEFAULT_GOLD, HERO_DEFAULT_EXP, HERO_DEFAULT_EXP_TO_LVL_UP, HERO_DEFAULT_LVL) {
	slots = new Inventory();
    paperdoll = new Paperdoll();
    
    projectileIndex = PROJECTILE_SHURIKEN;
    projectileIndexShape = PROJECTILE_SHURIKEN_SHAPE;
}

Hero::~Hero() {    
    delete slots;
    delete paperdoll;
}

void Hero::reset() {
    Unit::reset();
}

int Hero::getInventorySize() {
	return slots->capacity();
}

Inventory *Hero::getSlots() {
    return slots;
}

Item *Hero::getInventoryItemAt(int itemIndex) {
	return slots->getItemAt(itemIndex);
}

Item *Hero::removeInventoryItemAt(int itemIndex) {
    return slots->removeItemAt(itemIndex);
}

void Hero::printStat() {
	Unit::printStat();
    cout << " MP(" << mp << "/" << maxMp;
    cout << ") ATK(" << atk;
    cout << ") DEF(" << def;
    cout << ") GOLD(" << gold;
    cout << ") EXP(" << exp;
    cout << ") PROJECTILE(" << projectileIndexShape << ")";
	cout << endl;

    cout << "Slots: ";
    slots->print();
    cout << endl;

    paperdoll->print();
}

bool Hero::isHero() {
	return true;
}

bool Hero::isInventoryEmpty() {
	return slots->isEmpty();
}

bool Hero::isInventoryFull() {
    return slots->isFull();
}

void Hero::move(int dir) {
	bool moved = false;

	int nextRow = row;
	int nextCol = col;

	if (dir == DIR_N && row > 0) {
		nextRow--;
	}
	else if (dir == DIR_E && col < sim->board->getColSize() - 1) {
		nextCol++;
	}
	else if (dir == DIR_S && row < sim->board->getRowSize() - 1) {
		nextRow++;
	}
	else if (dir == DIR_W && col > 0) {
		nextCol--;
	}

	if (sim->board->getUnit(nextRow, nextCol) == NULL &&
        (sim->board->getProp(nextRow, nextCol) == NULL ||
         sim->board->getProp(nextRow, nextCol)->isClimbable())) {
		sim->board->setUnit(row, col, NULL);
		sim->board->setUnit(nextRow, nextCol, this);
        this->dir = dir;
		moved = true;

#ifdef STATISTICS_ON
        sim->stat->totalNumStepsHero++;
#endif
	}

	// battle/buy/sell/pet
	if (!moved) {
		if (sim->board->getUnit(nextRow, nextCol) != NULL &&
			sim->board->getUnit(nextRow, nextCol)->isMonster()) {
			sim->board->getUnit(nextRow, nextCol)->interact(this);
//            engaged = true;
		}
		if (sim->board->getUnit(nextRow, nextCol) != NULL &&
			sim->board->getUnit(nextRow, nextCol)->isMerchant()) {
			sim->board->getUnit(nextRow, nextCol)->interact(this);
		}
	}

    // pick up an item
	if (moved) {
		if (sim->board->getItem(row, col) != NULL) {
			if (!slots->isFull()) {
				slots->add(sim->board->getItem(row, col));
				sim->board->setItem(row, col, NULL);
			}
		}
	}

    // trigger a prop
    if (moved) {
        if (sim->board->getProp(row, col) != NULL) {
            sim->board->getProp(row, col)->trigger(this);
        }
    }
}

void Hero::interact(Unit *unit) {
    int dmg = (unit->getAtk()*(100 + rand() % 50)/100) - (def*(100+rand() % 20)/100);

    decHp(dmg);
}

void Hero::levelUp() {
    if (level < HERO_MAX_LEVEL) {
        hp += (HERO_MAX_HP/10)+(level*10);
        maxHp += (HERO_MAX_HP/10)+(level*10);
        
        mp += (HERO_MAX_MP/10)+(level*10);
        maxMp += (HERO_MAX_MP/10)+(level*10);
        
        atk += (HERO_DEFAULT_ATK/2)+(level*2);
        def += (HERO_DEFAULT_ATK/2)+(level*2);
        
        expToLevelUp += HERO_DEFAULT_EXP_TO_LVL_UP*level;
        
        level++;
    }
}

void Hero::useItem(int itemIndex) {
    if (itemIndex >= 0 && itemIndex < slots->capacity()) {
        slots->useItem(itemIndex, this);
    }
}

void Hero::add(Item *itemToBuy) {
	slots->add(itemToBuy);
}

bool Hero::equip(Item *itemToEquip) {
    return paperdoll->equip(itemToEquip, this);
}

void Hero::unequip(int bodyPartID) {
    if (slots->isFull()) {
        cout << "Hero::unequip(): error = the slots is full!!!" << endl;
        return;
    }
    
    Item *unequippedItem = paperdoll->unequip(bodyPartID, this);
    if (unequippedItem != NULL) {
        slots->add(unequippedItem);
    }
}

int Hero::getProjectileIndex() {
    return projectileIndex;
}

void Hero::changeProjectileIndex() {
    projectileIndex++;
    if (projectileIndex == PROJECTILE_NUM_TYPES) {
        projectileIndex = PROJECTILE_SHURIKEN;
        projectileIndexShape = PROJECTILE_SHURIKEN_SHAPE;
    }
    else if (projectileIndex == PROJECTILE_FIREBALL) {
        projectileIndexShape = PROJECTILE_FIREBALL_SHAPE;
    }
}

//void Hero::castMagic(int skillNumber) {
//    char shockwaveShape = '@';
//    if (skillNumber == MAGIC_FROZEN) {
//        shockwaveShape = MAGIC_FROZEN_SHAPE;
//    }
//    sim->board->startWave(this, NULL, NULL,
//                     row, col,
//                     5,
//                     2,
//                     shockwaveShape,
//                     skillNumber);
//}
//
//void Hero::effect(Unit *waveUnit, Item *waveItem, Prop *waveProp, int skillNumber) {
//    if (skillNumber == MAGIC_FROZEN) {
//        if (waveUnit != NULL) {
//            if (waveUnit->isMonster()) {
//                waveUnit->freeze();
//            }
//        }
//    }
//}

void Hero::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Hero" << endl;
    out << "#==================== slots" << endl;
    slots->save(out);
    out << "#==================== paperdoll" << endl;
    paperdoll->save(out);
    out << "# projectileIndex" << endl;
    out << projectileIndex << endl;
    out << "# projectileIndexShape" << endl;
    out << projectileIndexShape << endl;
}

void Hero::load(istream &in) {
    char buf[250];
    Unit::load(in);
//    out << "# -------------------------- Hero" << endl;
    in.getline(buf, 250);
//    out << "# slots" << endl;
    in.getline(buf, 250);
//    slots->save(out);
    slots->load(in);
//    out << "# paperdoll" << endl;
    in.getline(buf, 250);
//    paperdoll->save(out);
    paperdoll->load(in);
//    out << "# projectileIndex" << endl;
    in.getline(buf, 250);
//    out << projectileIndex << endl;
    in >> projectileIndex >> buf[0];
//    out << "# projectileIndexShape" << endl;
    in.getline(buf, 250);
//    out << projectileIndexShape << endl;
    in >> projectileIndexShape >> buf[0];
}
