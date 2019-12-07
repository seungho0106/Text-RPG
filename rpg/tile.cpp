#include <iostream>
#include <cmath>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "prop.h"
#include "projectile.h"
#include "tile.h"

Tile::Tile() { // Default Constructor
    fx = FX_NONE;
    
    unit = NULL;
    item = NULL;
    prop = NULL;
    projectile = NULL;
    
    //--------------------------------------------------------------------------
    // IQ120: A*
    //--------------------------------------------------------------------------
    astarReset();
}

void Tile::astarReset() {
    row = -1;
    col = -1;
    
    f = INF;
    g = INF;
    h = 0.0;
    
    cameFrom = DIR_NONE;
}

double Tile::calcH(Tile *goal) {
    return abs(row - goal->row) + abs(col - goal->col);
}

Tile::~Tile() { // Destructor
    // board쪽에서 모든 (죽은/죽지않은) unit들이 있으므로, 그쪽 destructor에서 지운다.
    // 마찬가지로 projectile도 그쪽에서 지운다.
    
//    if (unit != NULL) {
//        delete unit;
//    }
    
    if (item != NULL) {
        delete item;
    }
    
    if (prop != NULL) {
        delete prop;
    }
    
    if (projectile != NULL) {
        delete projectile;
    }
}

void Tile::print() {
    if (fx != FX_NONE) {
        cout << fx;
    }
    else if (unit != NULL) {
        unit->print();
    }
    else if (item != NULL) {
        item->print();
    }
    else if (prop != NULL) {
        prop->print();
    }
    else if (projectile != NULL) {
        projectile->print();
    }
    else {
        cout << TILE_EMPTY;
    }
}

void Tile::printAStarInfo() {
    cout << "[" << row << ", " << col << "| f(" << f << ") g(" << g << ") h(" << h << ") | cameFrom(";
    if (cameFrom == DIR_N) {
        cout << "N";
    }
    else if (cameFrom == DIR_E) {
        cout << "E";
    }
    else if (cameFrom == DIR_S) {
        cout << "S";
    }
    else if (cameFrom == DIR_W) {
        cout << "W";
    }
    else if (cameFrom == DIR_NONE) {
        cout << "-";
    }
    cout << ") ]";
}

char Tile::getFx() {
    return fx;
}

void Tile::setFx(char fx) {
    this->fx = fx;
}

void Tile::clearFx() {
    fx = FX_NONE;
}

Unit *Tile::getUnit() {
    return unit;
}

void Tile::setUnit(Unit *unit) {
    this->unit = unit;
}

Item *Tile::getItem() {
    return item;
}

void Tile::setItem(Item *item) {
    this->item = item;
}

Prop *Tile::getProp() {
    return prop;
}

void Tile::setProp(Prop *prop) {
    this->prop = prop;
}

Projectile *Tile::getProjectile() {
    return projectile;
}

void Tile::setProjectile(Projectile *projectile) {
    this->projectile = projectile;
}

//--------------------------------------------------------------------------
// Save/load
//--------------------------------------------------------------------------
void Tile::save(ostream &out) {
    out << "#---------------------------------------- class Tile" << endl;
    out << "#-------------------- item" << endl;
    if (item != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        out << "# Item ID" << endl;
        out << item->getClassTypeName() << endl;
        item->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    
    out << "#-------------------- prop" << endl;
    if (prop != NULL && !prop->isPortal()) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        out << "# Prop ID" << endl;
        out << prop->getClassTypeName() << endl;
        prop->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
}

void Tile::load(istream &in) {
    char buf[250];
//    out << "#---------------------------------------- class Tile" << endl;
    in.getline(buf, 250);
//    out << "#-------------------- item" << endl;
    in.getline(buf, 250);
//    if (item != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        out << "# Item ID" << endl;
//        out << item->getClassTypeName() << endl;
//        item->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        in.getline(buf, 250);
        string classTypeName = "";
        in >> classTypeName >> buf[0];
//        cout << "Item::load(): classTypeName = " << classTypeName << endl;
        item = Item::createItemByID(classTypeName);
        item->load(in);
//        exit(1);
    }
    else {
        item = NULL;
    }
//    out << "#-------------------- prop" << endl;
    in.getline(buf, 250);
//    if (prop != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        out << "# Prop ID" << endl;
//        out << prop->getClassTypeName() << endl;
//        prop->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        in.getline(buf, 250);
        string classTypeName = "";
        in >> classTypeName >> buf[0];
//        cout << "prop::load(): classTypeName = " << classTypeName << endl;
        prop = Prop::createPropByID(classTypeName);
        prop->load(in);
    }
    else {
        prop = NULL;
    }
}
