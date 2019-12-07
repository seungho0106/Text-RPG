#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "board.h"

#include "sim.h"
extern Sim *sim;

Unit::Unit() { // Default Constructor
    init('U', -1, -1, DIR_NONE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Unit::Unit(char shape, int row, int col, int dir, int range, int hp, int maxHp, int mp, int maxMp, int atk, int def, int gold, int exp, int expToLevelUp, int level) { // General Constructor
    init(shape, row, col, dir, range, hp, maxHp, mp, maxMp, atk, def, gold, exp, expToLevelUp, level);
}

void Unit::init(char shape, int row, int col, int dir, int range,
                int hp, int maxHp, int mp, int maxMp,
                int atk, int def, int gold, int exp, int expToLevelUp, int level) {
    this->shape = shape; // "this->"붙은 쪽이 member variable
    this->row = row;
    this->col = col;
    this->dir = dir;
    this->range = range;
    this->hp = hp;
    this->maxHp = maxHp;
    this->mp = mp;
    this->maxMp = maxMp;
    this->atk = atk;
    this->def = def;
    this->gold = gold;
    this->exp = exp;
    this->expToLevelUp = expToLevelUp;
    this->level = level;
    
    frozen = false;
    dead = false;
}

void Unit::reset() {
    row = -1;
    col = -1;
    
    hp = maxHp;
    mp = maxMp;
    
    dead = false;
    frozen = false;
}

Unit::~Unit() { // Destructor
}

void Unit::print() {
    cout << shape;
}

void Unit::printStat() {
    cout << shape << "(LV." << level << "): HP(" << hp << "/" << maxHp << ")";
}

char Unit::getShape() {
    return shape;
}

int Unit::getRow() {
    return row;
}

void Unit::setRow(int row) {
    this->row = row;
}

int Unit::getCol() {
    return col;
}

void Unit::setCol(int col) {
    this->col = col;
}

int Unit::getDir() {
    return dir;
}

void Unit::setDir(int dir) {
    this->dir = dir;
}

int Unit::getRange() {
    return range;
}

void Unit::setRange(int range) {
    this->range = range;
}

int Unit::getHp() {
    return hp;
}

bool Unit::incHp(int hpToInc) {
    if (hp >= maxHp) {
        return false;
    }
    
    if (hp + hpToInc < maxHp) {
        hp += hpToInc;
    }
    else {
        hp = maxHp;
    }
    
    return true;
}

void Unit::decHp(int hpToDec) {
    if (hpToDec <= 0) {
        hp -= 1;
        
        if (hp <= 0) {
            hp = 0;
            dead = true;
        }
    }
    else {
        hp -= hpToDec;
        
        if (hp <= 0) {
            hp = 0;
            dead = true;
        }
    }
}

int Unit::getMp() {
    return mp;
}

bool Unit::incMp(int mpToInc) {
    if (mp >= maxMp) {
        return false;
    }
    
    if (mp + mpToInc < maxMp) {
        mp += mpToInc;
    }
    else {
        mp = maxMp;
    }
    
    return true;
}

void Unit::decMp(int mpToDec) {
    if (mp - mpToDec > 0) {
        mp -= mpToDec;
    }
    else {
        mp = 0;
    }
}

int Unit::getAtk() {
    return atk;
}

void Unit::incAtk(int atkToInc) {
    atk += atkToInc;
}

void Unit::decAtk(int atkToDec) {
    atk -= atkToDec;
}

int Unit::getDef() {
    return def;
}

void Unit::incDef(int defToInc) {
    def += defToInc;
}

void Unit::decDef(int defToDec) {
    def -= defToDec;
}

int Unit::getGold() {
    return gold;
}

void Unit::incGold(int goldToInc) {
    gold += goldToInc;
}

void Unit::decGold(int goldToDec) {
    gold -= goldToDec;
}

int Unit::getExp() {
    return exp;
}

void Unit::incExp(int expToInc) {
    exp += expToInc;
    
    if (exp >= expToLevelUp) {
        levelUp();
    }
}

void Unit::levelUp() {
}

bool Unit::isFrozen() {
    return frozen;
}

void Unit::freeze() {
    frozen = true;
}

void Unit::unfreeze() {
    frozen = false;
}

bool Unit::isDead() {
    return dead;
}

bool Unit::isHero() { // fake body
    return false;
}

bool Unit::isPet() { // fake body
    return false;
}

bool Unit::isMonster() { // fake body
    return false;
}

bool Unit::isBoss() { // fake body
    return false;
}

bool Unit::isMerchant() {
	return false;
}

void Unit::move(int dir) {
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

    if (sim->board->getProp(nextRow, nextCol) == NULL &&
        sim->board->getUnit(nextRow, nextCol) == NULL) {
        sim->board->setUnit(row, col, NULL);
        sim->board->setUnit(nextRow, nextCol, this);
    }
}

void Unit::interact(Projectile *projectile){
}

void Unit::useItem(int itemIndex) { // fake body
}

bool Unit::equip(Item *itemToEquip) {
    return false;
}

void Unit::unequip(int bodyPartID) { // fake body
}

void Unit::effect(Unit *waveUnit, Item *waveItem, Prop *waveProp, int skillNumber) { // fake body
}

void Unit::save(ostream &out) {
    out << "#-------------------- class Unit" << endl;
    out << "# shape" << endl;
    out << shape << endl;
    out << "# row" << endl;
    out << row << endl;
    out << "# col" << endl;
    out << col << endl;
    out << "# dir" << endl;
    out << dir << endl;
    out << "# range" << endl;
    out << range << endl;
    out << "# hp" << endl;
    out << hp << endl;
    out << "# maxHp" << endl;
    out << maxHp << endl;
    out << "# mp" << endl;
    out << mp << endl;
    out << "# maxMp" << endl;
    out << maxMp << endl;
    out << "# atk" << endl;
    out << atk << endl;
    out << "# def" << endl;
    out << def << endl;
    out << "# gold" << endl;
    out << gold << endl;
    out << "# exp" << endl;
    out << exp << endl;
    out << "# frozen" << endl;
    out << frozen << endl;
    out << "# dead" << endl;
    out << dead << endl;
}

void Unit::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class Unit" << endl;
    in.getline(buf, 250);
//    out << "# shape" << endl;
    in.getline(buf, 250);
//    out << shape << endl;
    in >> shape >> buf[0];
//    out << "# row" << endl;
    in.getline(buf, 250);
//    out << row << endl;
    in >> row >> buf[0];
//    out << "# col" << endl;
    in.getline(buf, 250);
//    out << col << endl;
    in >> col >> buf[0];
//    out << "# dir" << endl;
    in.getline(buf, 250);
//    out << dir << endl;
    in >> dir >> buf[0];
//    out << "# range" << endl;
    in.getline(buf, 250);
//    out << range << endl;
    in >> range >> buf[0];
//    out << "# hp" << endl;
    in.getline(buf, 250);
//    out << hp << endl;
    in >> hp >> buf[0];
//    out << "# maxHp" << endl;
    in.getline(buf, 250);
//    out << maxHp << endl;
    in >> maxHp >> buf[0];
//    out << "# mp" << endl;
    in.getline(buf, 250);
//    out << mp << endl;
    in >> mp >> buf[0];
//    out << "# maxMp" << endl;
    in.getline(buf, 250);
//    out << maxMp << endl;
    in >> maxMp >> buf[0];
//    out << "# atk" << endl;
    in.getline(buf, 250);
//    out << atk << endl;
    in >> atk >> buf[0];
//    out << "# def" << endl;
    in.getline(buf, 250);
//    out << def << endl;
    in >> def >> buf[0];
//    out << "# gold" << endl;
    in.getline(buf, 250);
//    out << gold << endl;
    in >> gold >> buf[0];
//    out << "# exp" << endl;
    in.getline(buf, 250);
//    out << exp << endl;
    in >> exp >> buf[0];
//    out << "# frozen" << endl;
    in.getline(buf, 250);
//    out << frozen << endl;
    in >> frozen >> buf[0];
//    out << "# dead" << endl;
    in.getline(buf, 250);
//    out << dead << endl;
    in >> dead >> buf[0];
}
