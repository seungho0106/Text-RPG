#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "main.h"
#include "board.h"
#include "unit.h"
#include "prop.h"
#include "item.h"
#include "magic_scroll.h"

#include "sim.h"
extern Sim *sim;

MagicScroll::MagicScroll() : ConsumableItem(MAGIC_SCROLL_SHAPE, MAGIC_SCROLL_NAME, MAGIC_SCROLL_PRICE, true, false) {
}

MagicScroll::~MagicScroll() {
}

void MagicScroll::printFullSpec(ostream &out) {
		ConsumableItem::printFullSpec(out);
}

bool MagicScroll::use(Unit *unit) {
	while (true) {
		int randRow = rand() % sim->board->getRowSize();
		int randCol = rand() % sim->board->getColSize();
		if (sim->board->getUnit(randRow, randCol) == NULL && sim->board->getProp(randRow, randCol) == NULL) {
			sim->board->setUnit(unit->getRow(), unit->getCol(), NULL);
            sim->board->setUnit(randRow, randCol, unit);
			sim->board->startWave(NULL, NULL, NULL, randRow, randCol, 3, 1, '@', -1);
			break;
		}
	}
	return true;
}

Item *MagicScroll::clone() {
	return new MagicScroll();
}

void MagicScroll::save(ostream &out) {
    ConsumableItem::save(out);
    out << "#-------------------- class MagicScroll" << endl;
}

void MagicScroll::load(istream &in) {
    ConsumableItem::load(in);
    char buf[250];
    //out << "#-------------------- class MagicScroll" << endl;
    in.getline(buf, 250);
}

string MagicScroll::getClassTypeName() {
    return string("MagicScroll");
}
