#include <iostream>

#ifdef _MBCS
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#endif

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "item.h"
#include "merchant.h"
#include "board.h"
#include "backpack.h"
#include "util.h"

#include "sim.h"
extern Sim *sim;

Merchant::Merchant() : Unit(MERCHANT_SHAPE, -1, -1, 0, DIR_NONE, 0, 0, 0, 0, 0, 0, MERCHANT_DEFAULT_GOLD, MERCHANT_DEFAULT_EXP, 0, MERCHANT_DEFAULT_LVL) {
    numItemsToSell = 0;
    numItemsBought = 0;
    
	itemsToSell = new Backpack<ItemWrapper>();
	itemsBought = new Backpack<ItemWrapper>();

    for (int i = 0; i < MERCHANT_ITEMS_TO_SELL_MAX_NUM_ITEMS; i++) {
        itemsToSell->add(Item::createRandomItem());
    }
}

Merchant::~Merchant() {
    delete itemsToSell;
    delete itemsBought;
}

bool Merchant::isMerchant() {
	return true;
}

void Merchant::move(int dir) {
}

void Merchant::interact(Unit *unit) {
    while (true) {
        cout << "=========================================================" << endl;
        cout << "=========================================================" << endl;
        cout << "=========================================================" << endl;
        cout << "========================= SH's Shop =====================" << endl;
        cout << "=========================================================" << endl;
        cout << "=========================================================" << endl;
        cout << "=========================================================" << endl;
        cout << "(B)uy, (S)ell, or e(X)it: ";
        
        string command = "";
        cin >> command;
        
        if (command == "b" || command == "B") {
            buy();
        }
		else if ((command == "s" || command == "S") && !sim->hero->isInventoryEmpty()) {
            sell();
        }
		else if ((command == "s" || command == "S") && sim->hero->isInventoryEmpty()) {
			cout << "error: no items to sell!" << endl;
		}
        else if (command == "x" || command == "X") {
            break;
        }
    }
    cout << "See you! Come Again!" << endl;

#ifdef _MBCS
	Sleep(GAME_LOOP_DELAY_IN_MILLISEC);

#else
usleep(GAME_LOOP_DELAY_IN_MICROSEC);
#endif
}

void Merchant::add(Item *itemSold) {
	itemsBought->add(itemSold);
}

void Merchant::buy() {
    
    while (true) {
        cout << "=========================================================" << endl;
        cout << "=========================== Buy =========================" << endl;
        cout << "=========================================================" << endl;

        for (int i = 0; i < itemsToSell->size(); i++) {
            Item *curItem = itemsToSell->getItemAt(i).item;
            cout << i << ": ";
			if (curItem != NULL) {
				curItem->printFullSpec(cout);
			}
            cout << endl;
        }
        cout << "---------------------------------------------------------" << endl;        
        cout << "Items to buy back" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (int i = 0; i < itemsBought->size(); i++) {
            Item *curItem = itemsBought->getItemAt(i).item;
            cout << (i + 100) << ": ";
            if (curItem != NULL) {
                curItem->printFullSpec(cout);
            }
            cout << endl;
        }
        cout << "---------------------------------------------------------" << endl;
        sim->hero->printStat();
        cout << "---------------------------------------------------------" << endl;
		cout << "Enter the item index to purchase (x to exit): ";
        string input;
        cin >> input;
        
        if (input == "x") {
            break;
        }
        
        int itemIndexToPurchase = atoi(input);
        
		if (itemIndexToPurchase >= 0 && itemIndexToPurchase < itemsToSell->size() && !sim->hero->isInventoryFull()) {
			Item *itemToBuy = itemsToSell->removeItemAt(itemIndexToPurchase).item;
			if (sim->hero->getGold() >= itemToBuy->getPrice()) {
				sim->hero->add(itemToBuy);
				sim->hero->decGold(itemToBuy->getPrice());
			}
			else {
				cout << "error: Not enought money!" << endl;
			}
		}
        else if (itemIndexToPurchase >= 100 && itemIndexToPurchase < (itemsBought->size()+100)) {
            itemIndexToPurchase -= 100;
            Item *itemToBuy = itemsBought->removeItemAt(itemIndexToPurchase).item;
            if (sim->hero->getGold() >= itemToBuy->getPrice()) {
                sim->hero->add(itemToBuy);
                sim->hero->decGold(itemToBuy->getPrice());
            }
            else {
                cout << "error: Not enought money!" << endl;
            }
        }
        else if (sim->hero->isInventoryFull()) {
            cout << "error: Inventory is full!" << endl;
        }
        else {
            cout << "error: Enter a valid item index!" << endl;
        }
    }
}

void Merchant::sell() {
	while (true) {
        cout << endl;
		cout << "=========================================================" << endl;
		cout << "========================== Sell =========================" << endl;
		cout << "=========================================================" << endl;

		for (int i = 0; i < sim->hero->getInventorySize(); i++) {
			Item *curItem = sim->hero->getInventoryItemAt(i);
			cout << i << ": ";
			if (sim->hero->getInventoryItemAt(i) != NULL) {
				curItem->printFullSpec(cout);
			}
			cout << endl;
		}

        cout << "---------------------------------------------------------" << endl;
        sim->hero->printStat();
        cout << "---------------------------------------------------------" << endl;

        cout << "Enter the item index to sell (x to exit): ";
        string input;
        cin >> input;
        
        if (input == "x") {
            break;
        }

        int itemIndexToSell = atoi(input);
        
		if (itemIndexToSell >= 0 && itemIndexToSell < sim->hero->getInventorySize()) {
			Item *itemToSell = sim->hero->removeInventoryItemAt(itemIndexToSell);
            if (itemToSell != NULL) {
                add(itemToSell);
                sim->hero->incGold(itemToSell->getPrice());
            }
		}
        else {
            cout << "error: enter a valid item index!" << endl;
        }
	}
}

int Merchant::atoi(string input) {
    int i = 0;
    
    while (input[i] != '\0') {
        i++;
    }
    
    i--;
    
    int total = 0;
    
    int temp = 1;
    
    while (i >= 0) {
        total += (input[i] - '0') * temp;
        i--;
        temp *= 10;
    }
    return total;
}

void Merchant::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Merchant" << endl;
    out << "#======================================== itemsToSell" << endl;
    itemsToSell->save(out);
    out << "#======================================== itemsBought" << endl;
    itemsBought->save(out);
}

void Merchant::load(istream &in) {
    char buf[250];
    Unit::load(in);
//    out << "#-------------------- class Merchant" << endl;
    in.getline(buf, 250);
//    out << "#==================== itemsToSell" << endl;
    in.getline(buf, 250);
//    itemsToSell->save(out);
    delete itemsToSell;
    itemsToSell = new Backpack<ItemWrapper>();
    itemsToSell->load(in);
//    out << "#==================== itemsBought" << endl;
    in.getline(buf, 250);
//    itemsBought->save(out);
    delete itemsBought;
    itemsBought = new Backpack<ItemWrapper>();
    itemsBought->load(in);
}
