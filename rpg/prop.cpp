#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "prop.h"
#include "board.h"
#include "event.h"

#include "sim.h"
extern Sim *sim;

//------------------------------------------------------------------------------
// class Prop
//------------------------------------------------------------------------------

Prop::Prop() { // default constructor
    shape = 'P';
    row = -1;
    col = -1;
}

Prop::Prop(char shape) { // general constructor
    this->shape = shape;
}

Prop::~Prop() { // destructor
}

void Prop::print() {
    cout << shape;
}

int Prop::getRow() {
	return row;
}

void Prop::setRow(int row) {
	this->row = row;
}

int Prop::getCol() {
	return col;
}

void Prop::setCol(int col) {
	this->col = col;
}

bool Prop::isClimbable() { // fake body
    return false;
}

bool Prop::isPortal() {
    return false;
}

bool Prop::isExit() {
    return false;
}

void Prop::trigger(Unit *unit) { // fake body
}

void Prop::save(ostream &out) {
    out << "#-------------------- class Prop" << endl;
    out << "# shape" << endl;
    out << shape << endl;
    out << "# row" << endl;
    out << row << endl;
    out << "# col" << endl;
    out << col << endl;
}

void Prop::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class Prop" << endl;
    in.getline(buf, 250);
//    out << "# shape" << endl;
    in.getline(buf, 250);
//    out << shape << endl;
    in >> shape >> buf[0];
    //    out << "# row" << endl;
    in.getline(buf, 250);
    //    out << row << endl;
    in >> row >> buf[0];
    //    out << "# col" << endl;
    in.getline(buf, 250);
    //    out << col << endl;
    in >> col >> buf[0];
}

Prop *Prop::createPropByID(string classTypeName) {
    if (classTypeName == "Tree") {
        return new Tree();
    }
    else if (classTypeName == "Portal") {
        return new Portal();
    }
    else if (classTypeName == "Exit") {
        return new Exit();
    }
    return NULL;
}
//------------------------------------------------------------------------------
// class Tree
//------------------------------------------------------------------------------

Tree::Tree() : Prop(TREE_SHAPE) { // default cons
}

Tree::~Tree() { // destructor
}

void Tree::save(ostream &out) {
    Prop::save(out);
    out << "#-------------------- class Tree" << endl;
}

void Tree::load(istream &in) {
    char buf[250];
    Prop::load(in);
//    out << "#-------------------- class Tree" << endl;
    in.getline(buf, 250);
}

void Tree::trigger(Unit *unit) {
}

string Tree::getClassTypeName() {
    return string("Tree");
}

//------------------------------------------------------------------------------
// class Portal
//------------------------------------------------------------------------------

Portal::Portal() : Prop(PORTAL_SHAPE) {
}

Portal::Portal(char shape) : Prop(shape) {
}

Portal::~Portal() {
}

bool Portal::isClimbable() {
    return true;
}

bool Portal::isPortal() {
    return true;
}

void Portal::trigger(Unit *unit) {
    while (true) {
		int randIter = rand() % sim->board->getMaxNumPortals();
		int nextRow = -1;
		int nextCol = -1;

        if (sim->board->getPortalAt(randIter) != this) { // not me?
			nextRow = sim->board->getPortalAt(randIter)->getRow();
			nextCol = sim->board->getPortalAt(randIter)->getCol();
			if (sim->board->getUnit(nextRow, nextCol) == NULL) {
				sim->board->setUnit(unit->getRow(), unit->getCol(), NULL);
				sim->board->setUnit(nextRow, nextCol, unit);
				sim->board->startWave(NULL, NULL, NULL, nextRow, nextCol, 3, 1, '@', -1);
				break;
			}
		}
	}
}

void Portal::save(ostream &out) {
    Prop::save(out);
    out << "#-------------------- class Portal" << endl;
}

void Portal::load(istream &in) {
    char buf[250];
    Prop::load(in);
    //    out << "#-------------------- class Portal" << endl;
    in.getline(buf, 250);
}

string Portal::getClassTypeName() {
    return string("Portal");
}

//------------------------------------------------------------------------------
// class Exit
//------------------------------------------------------------------------------

Exit::Exit() : Portal(EXIT_SHAPE) {
}

Exit::~Exit() {
}

bool Exit::isExit() {
    return true;
}

void Exit::trigger(Unit *unit) {
    sim->eventQueue->enqueue(EventWrapper(new NewMapSpawnEvent(sim->time+NEW_MAP_SPAWN_INTERVAL)));
}

void Exit::save(ostream &out) {
    Prop::save(out);
    out << "#-------------------- class Exit" << endl;
}

void Exit::load(istream &in) {
    char buf[250];
    Prop::load(in);
    //    out << "#-------------------- class Exit" << endl;
    in.getline(buf, 250);
}

string Exit::getClassTypeName() {
    return string("Exit");
}
