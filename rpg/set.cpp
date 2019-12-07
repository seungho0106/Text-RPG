#include <iostream>

using namespace std;

#include "main.h"
#include "tile.h"
#include "set.h"

Set::Set() {
//    maxNumTiles = MAX_NUM_TILES;
//    numTiles = 0;
//
//    for (int i = 0; i < maxNumTiles; i++) {
//        tiles[i] = NULL;
//    }
     tiles = new vector<Tile *>();
}

Set::~Set() {
    // 비워둘 것.
}

void Set::print() {
    for (int i = 0; i < tiles->size(); i++) {
        (*tiles)[i]->printAStarInfo();
        cout << " ";
    }
    cout << endl;
}

void Set::add(Tile *tile) {
    tiles->push_back(tile);
}

bool Set::find(Tile *tile) { // contains() / indexOf()
    return std::find(tiles->begin(), tiles->end(), tile) != tiles->end();
}

// pre-condition: size() > 0
Tile *Set::removeMinF() {
    int indexMinF = 0;
    
	for (int i = 1; i < tiles->size(); i++) {
		if ((*tiles)[indexMinF]->f > (*tiles)[i]->f) {
				indexMinF = i;
//                cout << "tiles[" << indexMinF << "]: " << tiles[indexMinF] << endl;
		}
	}
    Tile *minF = (*tiles)[indexMinF];
    
//    cout << "minF[" << indexMinF << "]: " << tiles[indexMinF] << endl;

    tiles->erase(tiles->begin()+indexMinF);
    
    return minF;
}

bool Set::isEmpty() {
    return tiles->size() == 0;
}

int Set::size() {
    return tiles->size();
}
