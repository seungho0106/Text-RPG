#ifndef PROJECTILE_H
#define PROJECTILE_H

class Unit;

#include "unit.h"

class Projectile {
protected:
    char shape;
    
    int row;
    int col;
    
    int dir;
    int range;
    
    int mp;
    int atk;
    
    int distance;
    
    bool activated;
    
public:
    Projectile();
    Projectile(char shape, int range, int mp, int atk);
    void init(char shape, int row, int col, int dir, int range, int mp, int atk, int distance);
    virtual ~Projectile();
    
    void print();

    char getShape();

    int getRow();
    void setRow(int row);

    int getCol();
    void setCol(int col);

    void setDir(int dir);

    int getMp();

    int getAtk();
    
    virtual void activate();
    
    virtual bool isProjectile();
    virtual bool isActivated();
    virtual bool isBlocked(int nextRow, int nextCol);
    
    virtual void move();
    virtual void interact(Unit *unit);
};

class Shuriken : public Projectile {
protected:
public:
    Shuriken();
    Shuriken(int row, int col, int dir);
    virtual ~Shuriken();
    
};

class Fireball : public Projectile {
protected:
public:
    Fireball();
    Fireball(int row, int col, int dir);
    virtual ~Fireball();
    
};

#endif
