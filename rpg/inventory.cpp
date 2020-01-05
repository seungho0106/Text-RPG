#include <iostream>
#include <string>

using namespace std;

#include "main.h"
#include "item.h"
#include "inventory.h"

Inventory::Inventory() {
    init(INVENTORY_NUM_ITEMS_MAX);
}

Inventory::Inventory(int maxNumItems) {
    init(maxNumItems);
}

void Inventory::init(int maxNumItems) {
    this->maxNumItems = maxNumItems;
    slots = new Item *[maxNumItems];
    numItems = 0;
    
    for (int i = 0; i < maxNumItems; i++) {
        slots[i] = NULL;
    }
}

Inventory::~Inventory() {
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] != NULL) {
            delete slots[i];
        }
    }
    
    delete [] slots;
}

void Inventory::print() {
    for (int i = 0; i < maxNumItems; i++) {
        cout << "[";
        if (slots[i] != NULL) {
            slots[i]->print();
        }
        else {
            cout << " ";
        }
        cout << "] ";
    }
}

bool Inventory::add(Item *item) { // Create
    if (isFull()) {
        return false;
    }
    
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] == NULL) {
            slots[i] = item;
            break;
        }
    }
    
    numItems++;
    
    return true;
}

// pre-condition: index >= 0 && index < maxNumItems
Item *Inventory::getItemAt(int index) { // Read
    if (index < 0 || index >= maxNumItems) { // validate
        return NULL;
    }
    
    return slots[index];
}

// pre-condition: index >= 0 && index < maxNumItems
Item *Inventory::removeItemAt(int index) { // Delete
    if (index < 0 || index >= maxNumItems) { // validate
        return NULL;
    }
    
    if (slots[index] != NULL) {
        Item *itemToReturn = slots[index];
        slots[index] = NULL;
        numItems--;
        return itemToReturn;
    }
    
    return NULL;
}

// pre-condition: index >= 0 && index < maxNumItems
void Inventory::useItem(int index, Unit *unit) {
	if (index < 0 || index >= maxNumItems) { // validate
        return;
    }

    if (slots[index] != NULL) {
        if (slots[index]->use(unit)) {
            if (!(slots[index]->isRemovable() && slots[index]->isRemoved())) {
                delete slots[index];
            }
            slots[index] = NULL;
            numItems--;
        }
    }
}

bool Inventory::isFull() {
    return numItems >= maxNumItems;
}

bool Inventory::isEmpty() {
	if (numItems == 0) {
		return true;
	}
	return false;
}

int Inventory::capacity() {
    return maxNumItems;
}

int Inventory::size() {
    return numItems;
}

void Inventory::save(ostream &out) {
    out << "#-------------------- class Inventory" << endl;
    out << "# maxNumItems" << endl;
    out << maxNumItems << endl;
    out << "# numItems" << endl;
    out << numItems << endl;
    for (int i = 0; i < maxNumItems; i++) {
        out << "#==================== slots[" << i << "]" << endl;
        if (slots[i] != NULL) {
            out << TOMBSTONE_NOT_EMPTY << endl;
            out << "# Item ID" << endl;
            out << slots[i]->getClassTypeName() << endl;
            slots[i]->save(out);
        }
        else {
            out << TOMBSTONE_EMPTY << endl;
        }
    }
}

void Inventory::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class Inventory" << endl;
    in.getline(buf, 250);
//    out << "# maxNumItems" << endl;
    in.getline(buf, 250);
//    out << maxNumItems << endl;
    in >> maxNumItems >> buf[0];
//    out << "# numItems" << endl;
    in.getline(buf, 250);
//    out << numItems << endl;
    in >> numItems >> buf[0];
    for (int i = 0; i < maxNumItems; i++) {
//        out << "#==================== slots[" << i << "]" << endl;
        in.getline(buf, 250);
//        if (slots[i] != NULL) {
//            out << TOMBSTONE_NOT_EMPTY << endl;
//            out << "# Item ID" << endl;
//            out << slots[i]->getClassTypeName() << endl;
//            slots[i]->save(out);
//        }
//        else {
//            out << TOMBSTONE_EMPTY << endl;
//        }
//    }
        in.getline(buf, 250);
        if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
            in.getline(buf, 250);
            string classTypeName = "";
            in >> classTypeName >> buf[0];
            slots[i] = Item::createItemByID(classTypeName);
            slots[i]->load(in);
            }
        else {
            slots[i] = NULL;
        }
    }
}
