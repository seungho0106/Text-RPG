#ifndef TILE_H
#define TILE_H

class Unit;
class Item;
class Prop;
class Projectile;

#define FX_NONE '\0'

class Tile {
protected:
    char fx; // fx layer
    
    Projectile *projectile;
    Unit *unit;
    Item *item;
    Prop *prop;
    
public:
    //--------------------------------------------------------------------------
    // IQ120: A*
    //--------------------------------------------------------------------------
    int row;
    int col;
    
    double f;
    double g;
    double h;
    
    int cameFrom; // parentDir
    
    void astarReset();
    double calcH(Tile *goal);

public:
    Tile();
    virtual ~Tile();
    
    char getFx();
    void setFx(char fx);
    void clearFx(); // resetFx()

    void print();
    void printAStarInfo();
    
    Unit *getUnit();
    void setUnit(Unit *unit);

    Item *getItem();
    void setItem(Item *item);

    Prop *getProp();
    void setProp(Prop *prop);
    
    Projectile *getProjectile();
    void setProjectile(Projectile *projectile);
    
    //--------------------------------------------------------------------------
    // aave/load
    //--------------------------------------------------------------------------
    void save(ostream &out);
    void load(istream &in);
};

#endif
