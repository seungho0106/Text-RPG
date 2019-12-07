#ifndef UNIT_H
#define UNIT_H

class Item;
class Prop;
class Board;
class Projectile;

class Unit { // parent class of class Hero/Monster/Merchant
protected:
    char shape;
    
    int row;
    int col;
    
    int dir;
    int range;
    
    int hp;
    int maxHp;

    int mp;
    int maxMp;
    
    int atk;
    int def;
    
    int gold;
    int exp;
    
    int expToLevelUp;
    int level;

    bool frozen;
    bool dead;
    
public:
    Unit();
    Unit(char shape, int row, int col, int dir, int range, int hp, int maxHp, int mp, int maxMp, int atk, int def, int gold, int exp, int expToLevelUp, int level);
    void init(char shape, int row, int col, int dir, int range, int hp, int maxHp, int mp, int maxMp, int atk, int def, int gold, int exp, int expToLevelUp, int level);

    virtual void reset();
    
    virtual ~Unit();
    
    void print();
    virtual void printStat();
    
    char getShape();

    int getRow();
    void setRow(int row);

    int getCol();
    void setCol(int col);
    
    int getDir();
    void setDir(int dir);
    
    int getRange();
    void setRange(int range);
    
    int getHp();
    bool incHp(int hpToInc);
    void decHp(int enemyAtk); // Takes enemy atk & unit def into calculation

    int getMp();
    bool incMp(int mpToInc);
    void decMp(int mpToDec);

    int getAtk();
    void incAtk(int atkToInc);
    void decAtk(int atkToDec);

    int getDef();
    void incDef(int defToInc);
    void decDef(int defToDec);

    int getGold();
    void incGold(int goldToInc);
    void decGold(int goldToDec);

    int getExp();
    void incExp(int expToInc);
    virtual void levelUp();

    bool isFrozen();
    void freeze();
    void unfreeze();

    bool isDead();

    virtual bool isHero();
    virtual bool isPet();
    virtual bool isMonster();
    virtual bool isBoss();
	virtual bool isMerchant();
    
    virtual void move(int dir);
    virtual void interact(Unit *unit) = 0; // pure virtual function
    virtual void interact(Projectile *projectile);
    
    virtual void useItem(int itemIndex);
    
    virtual bool equip(Item *itemToEquip); // calling from EquippableItemItem::use()
    virtual void unequip(int bodyPartID); // calling from main()
    
    // for shockwave
    virtual void effect(Unit *waveUnit, Item *waveItem, Prop *waveProp, int skillNumber);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
