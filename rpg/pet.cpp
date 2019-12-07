#include <iostream>

using namespace std;

#include "main.h"
#include "board.h"
#include "unit.h"
#include "hero.h"
#include "pet.h"
#include "consumable_item.h"
#include "prop.h"
#include "inventory.h"

#include "sim.h"
extern Sim *sim;

Pet::Pet() : Unit(PET_SHAPE, PET_START_ROW, PET_START_COL, DIR_NONE, PET_DEFAULT_RANGE, PET_MAX_HP, PET_MAX_HP, PET_MAX_MP, PET_MAX_MP, PET_DEFAULT_ATK, PET_DEFAULT_DEF, PET_DEFAULT_GOLD, PET_DEFAULT_EXP, 0, PET_DEFAULT_LVL) {

}

Pet::~Pet() {
}

bool Pet::isPet() {
    return true;
}

void Pet::move(int dir) {
    bool heroFound = false;
    bool enemyFound = false;
    bool itemFound = false;
    Hero *hero = NULL;
    Monster *enemy = NULL;
    ConsumableItem *item = NULL;
    int heroRow = -1;
    int heroCol = -1;
    int enemyRow = -1;
    int enemyCol = -1;
    int itemRow = -1;
    int itemCol = -1;
    
    for (int i = row-range; i <= row+range && !heroFound; i++) { // Hero Tracking
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
    
    if (!heroFound) {
        for (int i = sim->hero->getRow()-range; i <= sim->hero->getRow()+range && !heroFound; i++) {
            for (int j = sim->hero->getCol()-range; j <= sim->hero->getCol()+range && !heroFound; i++) {
                if (sim->board->validate(i, j) &&
                    sim->board->getUnit(i, j) == NULL &&
                    sim->board->getProp(i, j) == NULL) {
                    heroFound = true;
                    sim->board->setUnit(row, col, NULL);
                    sim->board->setUnit(i, j, this);
                }
            }
        }
    }
    
    for (int i = row-range; i <= row+range && !enemyFound; i++) { // Enemy Tracking
        for (int j = col-range; j <= col+range && !enemyFound; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                sim->board->getUnit(i, j)->isMonster()) {
                enemyFound = true;
                enemy = (Monster *)sim->board->getUnit(i, j);
                enemyRow = i;
                enemyCol = j;
            }
        }
    }
    
    for (int i = row-range; i <= row+range && !itemFound; i++) { // Item Tracking
        for (int j = col-range; j <= col+range && !itemFound; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getItem(i, j) != NULL &&
                sim->board->getItem(i, j)->isConsumable()) {
                itemFound = true;
                item = (ConsumableItem *)sim->board->getItem(i, j);
                itemRow = i;
                itemCol = j;
            }
        }
    }
    
    if (heroFound && !enemyFound && !itemFound) {
        if (row == heroRow) {
            if (col > heroCol) { // left?
                if (col-1 == heroCol) { // adjacent?
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_W;
                }
            }
            else { // right?
                if (col+1 == heroCol) { // adjacent?
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
                    dir = DIR_NONE;
                }
                else {
                    dir = DIR_N;
                }
            }
            else { // down?
                if (row+1 == heroRow) { // adjacent?
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
            if (heroRow < row && col < heroCol) { //NE
                if (diffCol < diffRow) {
                    dir = DIR_N;
                }
                else {
                    dir = DIR_E;
                }
            }
            if (row < heroRow && heroCol < col) { //SW
                if (diffCol < diffRow) {
                    dir = DIR_S;
                }
                else {
                    dir = DIR_W;
                }
            }
            if (row < heroRow && col < heroCol) { //SE
                if (diffCol < diffRow) {
                    dir = DIR_S;
                }
                else {
                    dir = DIR_E;
                }
            }
        }
        
    }
    
    
    bool moved = false;
    
    int prevRow = row;
    int prevCol = col;
    
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
        }
    
    // freeze/unfreeze monsters
    if (moved) {
        for (int i = prevRow - 1; i <= prevRow + 1; i++) {
            for (int j = prevCol - 1; j <= prevCol + 1; j++) {
                if (sim->board->getUnit(i, j) != NULL &&
                    sim->board->getUnit(i, j)->isMonster()) {
                    sim->board->getUnit(i, j)->unfreeze();
                }
            }
        }
        
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (sim->board->getUnit(i, j) != NULL &&
                    sim->board->getUnit(i, j)->isMonster()) {
                    sim->board->getUnit(i, j)->freeze();
                }
            }
        }
    }
    
    // pick up an item
    if (moved) {
        if (sim->board->getItem(row, col) != NULL) {
            if (!sim->hero->getSlots()->isFull()) {
                sim->hero->getSlots()->add(sim->board->getItem(row, col));
                sim->board->setItem(row, col, NULL);
            }
        }
    }
}

void Pet::interact(Unit *unit) {
}

bool Pet::isDirStuck(int curRow, int curCol, int curDir) {
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
