#ifndef BOSS_H
#define BOSS_H

class Unit;

#define ROW 0
#define COL 1
#define MAX_LEN_PATH 1000

class Boss : public Monster { // child class of class Monster
protected:
    
    //--------------------------------------------------------------------------
    // IQ100/IQ120이상에서 사용.
    //--------------------------------------------------------------------------
    bool pathFound;
    
    int path[2][MAX_LEN_PATH];
    int pathDir[MAX_LEN_PATH];
    int maxLenPath;
    int lenPath;
    
    int curIndexPath;
    
public:
	Boss();
	virtual ~Boss();

    void reset();
	
    bool isBoss();

	void move(int dir); // ?????????????????
    
    //--------------------------------------------------------------------------
    // A* Algorithm에서 사용.
    //--------------------------------------------------------------------------
    int turnLeft(int curDir);
    int turnRight(int curDir);
    
    void goForward(int curDir, int &curRow, int &curCol);

    void reconstruct_path(Tile *start, Tile *goal);

    Tile *getNeighborWhenNotBlockedIgnoreUnit(Tile *current, int dir);
    int getParentTileDir(Tile *me, Tile *parent);
    Tile *getParentTileByCameFrom(Tile *me);

	bool isValid(int row, int col);
	bool isDestination(int curRow, int curCol, int goalRow, int goalCol);
	double calculateH(int row, int col, int heroRow, int heroCol);
	void pathReverse(int path[2][MAX_LEN_PATH], int lenPath);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
