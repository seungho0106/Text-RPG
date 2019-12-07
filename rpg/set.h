#ifndef SET_H
#define SET_H

#include <vector>

using namespace std;

#define MAX_NUM_TILES 1000

class Tile;

class Set {
//    Tile *tiles[MAX_NUM_TILES];
//    int maxNumTiles;
//    int numTiles;
    vector<Tile *> *tiles;
    
public:
    Set();
    virtual ~Set();

    void print();
    
    void add(Tile *tile);
    bool find(Tile *tile); // contains() / indexOf()
    Tile *removeMinF();

    bool isEmpty();

    int size();
};

#endif
