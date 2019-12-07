#ifndef MONSTER_H
#define MONSTER_H

class Unit;
class Projectile;

class Monster : public Unit { // child class of class Unit
protected:
    bool engaged;
    
public:
	Monster();
    Monster(char shape, int row, int col, int dir, int range, int hp, int maxHp, int mp, int maxMp, int atk, int def, int gold, int exp, int level);
	virtual ~Monster();
    
    virtual void reset();

	bool isMonster();
    bool isEngaged();

	virtual void move(int dir);
	virtual void interact(Unit *unit);
    virtual void interact(Projectile *projectile);
    
    virtual bool isDirStuck(int curDir, int curRow, int curCol);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
