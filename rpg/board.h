#ifndef BOARD_H
#define BOARD_H

class Tile;
class Item;
class Unit;
class Prop;
class Hero;
class Pet;
class Projectile;
class Shuriken;
class Fireball;
class Monster;
class Boss;
class Merchant;
class Portal;
class Exit;
class Shockwave;

class Board {
protected:
    Tile ***board; // 2D array of Tile object
    int rowSize;
    int colSize;
    
    Hero *hero;
    
//    Pet *pet;

    Monster **mons;
    int maxNumMons;
    int numMons;

    Boss **bosses;
    int maxNumBosses;
    int numBosses;

	Merchant **merchants;
	int maxNumMerchants;
	int numMerchants;

	Portal **portals;
	int maxNumPortals;
    int numPortals;
    
    Projectile **projectiles;
    int maxNumProjectiles;
    int numProjectiles;
    
    Shuriken **shurikens;
    int maxNumShurikens;
    int numShurikens;
    
    Fireball **fireballs;
    int maxNumFireballs;
    int numFireballs;

    Exit *exit;
    
    bool dayAndNight; // day == true / night == false

    //--------------------------------------------------------------------------
    // Shockwave
    //--------------------------------------------------------------------------
    Shockwave **shockwaves;
    int maxNumShockwaves;
    int numShockwaves;

public:
    Board();
    Board(bool doNotCreateHero);
    void createBoard(bool doNotCreateHero);
    void createTiles(int rowSize, int colSize); // test mode/random mode 둘다 사용. 맨 처음에 call할 것.
    void createMons(int maxNumMons);
    void createBosses(int maxNumBosses);
    void createMerchants(int maxNumMerchants);
    void createPortals(int maxNumPortals);
    
    void loadTestBoard();
    void createHero();
    void createRandomProps();
    void createRandomItems();
    void createRandomUnits();
    void initEtc(); // test mode/random mode 둘다 사용. 맨 나중에 call할 것.
    
	virtual ~Board();
    void destroyBoard();
    void destroyBoard(bool doNotDeleteHero);
    void destroyEtc();
    
    void print();
    void printEngaged();
    
    bool validate(int row, int col);
    
    int getRowSize() const;
    int getColSize() const;

    Hero *getHero();
    void setHeroNULL();
    
    Unit *getUnit(int row, int col);
    void setUnit(int row, int col, Unit *unit);
    
    Item *getItem(int row, int col);
    void setItem(int row, int col, Item *item);
    
    Prop *getProp(int row, int col);
    void setProp(int row, int col, Prop *prop);
    
//    void movePet();
    void moveMons();
    void moveBosses();
    
    //--------------------------------------------------------------------------
    // Projectile
    //--------------------------------------------------------------------------
    void initProjectiles();
    void destroyProjectiles();

    Projectile *getProjectile(int row, int col);
    void setProjectile(int row, int col, Projectile *projectile);
    void shootProjectiles();
    void moveProjectiles();
    
    //--------------------------------------------------------------------------
    // Portal
    //--------------------------------------------------------------------------
    int getMaxNumPortals();
    Portal *getPortalAt(int index);

    //--------------------------------------------------------------------------
    // Exit
    //--------------------------------------------------------------------------
    void createExit();
    
	//--------------------------------------------------------------------------
	// A*
	//--------------------------------------------------------------------------
	Tile *getTileAt(int row, int col);
    void astarReset();

    //--------------------------------------------------------------------------
    // Event
    //--------------------------------------------------------------------------
    void toggleDayAndNight();
    
    //--------------------------------------------------------------------------
    // For shockwave
    //--------------------------------------------------------------------------
    void initFx();
    void destroyFx();
    
    void clearFx(int row, int col);
    void setFx(int row, int col, char fx);
    void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                   int row, int col, int range, int frameInterval, char fxShape, int skillNumber);
    
    //--------------------------------------------------------------------------
    // Save/load
    //--------------------------------------------------------------------------
    void save(ostream &out);
    void load(istream &in);
};

#endif
