#include <iostream>
#include <cmath>

using namespace std;

#include "main.h"
#include "board.h"
#include "unit.h"
#include "hero.h"
#include "monster.h"
#include "prop.h"
#include "projectile.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

Monster::Monster() : Unit(MONSTER_SHAPE, -1, -1, DIR_NONE, MONSTER_DEFAULT_RANGE, MONSTER_MAX_HP, MONSTER_MAX_HP, MONSTER_MAX_MP, MONSTER_MAX_MP, MONSTER_DEFAULT_ATK, MONSTER_DEFAULT_DEF, MONSTER_DEFAULT_GOLD, MONSTER_DEFAULT_EXP, 0, MONSTER_DEFAULT_LVL) { // default cons
    engaged = false;
}

Monster::Monster(char shape, int row, int col, int dir, int range, int hp, int maxHp, int mp, int maxMp, int atk, int def, int gold, int exp, int level)
    : Unit(shape, row, col, dir, range, hp, maxHp, mp, maxMp, atk, def, gold, exp, 0, level) {
        engaged = false;
}

Monster::~Monster() { // destructor
}

void Monster::reset() {
    Unit::reset();
}

bool Monster::isMonster() {
	return true;
}

bool Monster::isEngaged() {
    return engaged;
}

void Monster::move(int dir) {
    if (frozen || dead) {
        return;
    }
    
    // Hero Tracking
    bool heroFound = false;
    Hero *hero = NULL;
    int heroRow = -1;
    int heroCol = -1;
    
    for (int i = row-range; i <= row+range && !heroFound; i++) {
        for (int j = col-range; j <= col+range && !heroFound; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                sim->board->getUnit(i, j)->isHero()) {
                heroFound = true;
                hero = (Hero *)sim->board->getUnit(i, j);
                heroRow = i;
                heroCol = j;
            }
        }
    }
    
    if (heroFound) {
        // 같은 horz 라인에 있을 경우.
        if (row == heroRow) {
            if (col > heroCol) { // left?
                if (col-1 == heroCol) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_W;
                }
            }
            else { // right?
                if (col+1 == heroCol) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_E;
                }
            }
        }
        // 같은 vert 라인에 있을 경우.
        else if (col == heroCol) {
            if (row > heroRow) { // up?
                if (row-1 == heroRow) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_N;
                }
            }
            else { // down?
                if (row+1 == heroRow) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_S;
                }
            }
        }
        // NW/NE/SW/SE 4개의 블럭중 한개에 있다.
        else {
            int diffRow = abs(row - heroRow);
            int diffCol = abs(col - heroCol);
            
            if (heroRow < row && heroCol < col) { //NW
                if (diffCol < diffRow) {
                    dir = DIR_N;
                }
                else {
                    dir = DIR_W;
                }
            }
            else if (heroRow < row && col < heroCol) { //NE
                if (diffCol < diffRow) {
                    dir = DIR_N;
                }
                else {
                    dir = DIR_E;
                }
            }
            else if (row < heroRow && heroCol < col) { //SW
                if (diffCol < diffRow) {
                    dir = DIR_S;
                }
                else {
                    dir = DIR_W;
                }
            }
            else if (row < heroRow && col < heroCol) { //SE
                if (diffCol < diffRow) {
                    dir = DIR_S;
                }
                else {
                    dir = DIR_E;
                }
            }
        }
    }
    else { // hero not found?
        engaged = false;
    }
    
    // Unstuck monster
    while (isDirStuck(dir, row, col)) {
        dir = rand() % NUM_DIRS;
    }

    Unit::move(dir);
}

void Monster::interact(Unit *unit) {
    if (dead) {
        return;
    }
    
    engaged = true;
    int dmg = (unit->getAtk()*(100 + rand() % 50)/100) - (def*(100+rand() % 20)/100);
    
    decHp(dmg);
    
    if (dead) {
        engaged = false;
        sim->systemMessage = "Monster has died!";
        unit->incGold(gold);
        unit->incExp(exp);

#ifdef STATISTICS_ON
        sim->stat->numMonsKilled++;
#endif
    }
}

void Monster::interact(Projectile *projectile) {
    engaged = true;
    int dmg = (projectile->getAtk()*(100 + rand() % 50)/100) - (def*(100+rand() % 20)/100);
    
    decHp(dmg);
    
    if (dead) {
        engaged = false;
        sim->systemMessage = "Monster has died!";
        sim->hero->incGold(gold);
        sim->hero->incExp(exp);
    }
}

bool Monster::isDirStuck(int curDir, int curRow, int curCol) {
    if (curDir == DIR_N) {
        return (sim->board->getProp(curRow-1, curCol) != NULL && !sim->board->getProp(curRow-1, curCol)->isClimbable());
    }
    else if (curDir == DIR_E) {
        return (sim->board->getProp(curRow, curCol+1) != NULL && !sim->board->getProp(curRow, curCol+1)->isClimbable());
    }
    else if (curDir == DIR_S) {
        return (sim->board->getProp(curRow+1, curCol) != NULL && !sim->board->getProp(curRow+1, curCol)->isClimbable());
    }
    else if (curDir == DIR_W) {
        return (sim->board->getProp(curRow, curCol-1) != NULL && !sim->board->getProp(curRow, curCol-1)->isClimbable());
    }
    
    return false;
}

void Monster::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Monster" << endl;
}

void Monster::load(istream &in) {
    char buf[250];
    Unit::load(in);
//    out << "#-------------------- class Monster" << endl;
    in.getline(buf, 250);
}
