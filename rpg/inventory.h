#ifndef INVENTORY_H
#define INVENTORY_H

class Item;

class Inventory {
private:
    Item **slots;
    int maxNumItems;
    int numItems;
    
public:
    Inventory();
    Inventory(int maxNumItems);
    void init(int maxNumItems);
    virtual ~Inventory();

    void print();

    bool add(Item *item); // Create
    Item *getItemAt(int index); // Read
    Item *removeItemAt(int index); // Delete

    void useItem(int index, Unit *unit);
    
    bool isFull();
	bool isEmpty();

    int capacity();
    int size();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
