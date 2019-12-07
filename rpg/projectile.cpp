#include <iostream>

using namespace std;

#include "main.h"
#include "prop.h"
#include "projectile.h"
#include "board.h"

#include "sim.h"
extern Sim* sim;

Projectile::Projectile() {
    init('-', -1, -1, DIR_NONE, 0, 0, 0, 0);
}

Projectile::Projectile(char shape, int range, int mp, int atk) {
    init(shape, -1, -1, DIR_NONE, range, mp, atk, 0);
}

void Projectile::init(char shape, int row, int col, int dir, int range, int mp, int atk, int distance) {
    this->shape = shape; // "this->"붙은 쪽이 member variable
    this->row = row;
    this->col = col;
    this->dir = dir;
    this->range = range;
    this->mp = mp;
    this->atk = atk;
    this->distance = distance;
    
    activated = false;
}

Projectile::~Projectile() {
}

void Projectile::print() {
    cout << shape;
}

char Projectile::getShape() {
    return shape;
}

int Projectile::getRow() {
    return row;
}

void Projectile::setRow(int row) {
    this->row = row;
}

int Projectile::getCol() {
    return col;
}

void Projectile::setCol(int col) {
    this->col = col;
}

void Projectile::setDir(int dir) {
    this->dir = dir;
}

int Projectile::getMp() {
    return mp;
}

int Projectile::getAtk() {
    return atk;
}

void Projectile::activate() {
    activated = true;
}

bool Projectile::isProjectile() {
    return true;
}

bool Projectile::isActivated() {
    return activated;
}

/**
 * Returns true when this projectile is blocked, or false.
 * @param nextRow the next row
 * @param nextCol the next column
 * @return true when this projectile is blocked, or false.
 */
bool Projectile::isBlocked(int nextRow, int nextCol) {
    return (!sim->board->validate(nextRow, nextCol) || (sim->board->getUnit(nextRow, nextCol) != NULL && !sim->board->getUnit(nextRow, nextCol)->isHero()) ||
            (sim->board->getProp(nextRow, nextCol) != NULL && !sim->board->getProp(nextRow, nextCol)->isClimbable()));
}

void Projectile::move() {
    bool blocked = false;
    
    if (activated) {
        if (distance <= range) {
            int nextRow = row;
            int nextCol = col;
            
            if (dir == DIR_N) {
                nextRow--;
            }
            else if (dir == DIR_E) {
                nextCol++;
            }
            else if (dir == DIR_S) {
                nextRow++;
            }
            else if (dir == DIR_W) {
                nextCol--;
            }

            if (isBlocked(nextRow, nextCol)) {
                if (sim->board->getUnit(nextRow, nextCol) != NULL && sim->board->getUnit(nextRow, nextCol)->isMonster()) {
                    sim->board->getUnit(nextRow, nextCol)->interact(this);
                }
                blocked = true;
            }
            else {
                sim->board->setProjectile(row, col, NULL);
                sim->board->setProjectile(nextRow, nextCol, this);
            }
            distance++;
        }
        if (distance > range || blocked) { // done?
            sim->board->setProjectile(row, col, NULL);
            row = -1;
            col = -1;
            dir = DIR_NONE;
            distance = 0;
            activated = false;
        }
    }
}

void Projectile::interact(Unit *unit) {
}

Shuriken::Shuriken() : Projectile(PROJECTILE_SHURIKEN_SHAPE, PROJECTILE_SHURIKEN_RANGE, PROJECTILE_SHURIKEN_MP, PROJECTILE_SHURIKEN_ATK) {
}

Shuriken::~Shuriken() {
}

Fireball::Fireball() : Projectile(PROJECTILE_FIREBALL_SHAPE, PROJECTILE_FIREBALL_RANGE, PROJECTILE_FIREBALL_MP, PROJECTILE_FIREBALL_ATK) {
}

Fireball::~Fireball() {
}

