#ifndef ITEM_H
#define ITEM_H

class Unit;
class Item;

class ItemWrapper {
public:
    Item *item;
    
    ItemWrapper();
    ItemWrapper(Item *item);
    
    virtual ~ItemWrapper();
    
    void printFullSpec(ostream &out);
    
    bool operator<(const ItemWrapper &other);
    bool operator<=(const ItemWrapper &other);
    bool operator>(const ItemWrapper &other);
    bool operator>=(const ItemWrapper &other);
    
    bool operator==(const ItemWrapper &other);
    
    friend ostream &operator<<(ostream &out, const ItemWrapper &obj);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};
ostream &operator<<(ostream &out, const ItemWrapper &obj);

class Item {
protected:
public:

    char shape;
    //    int itemNumber;
    
    string name;
    int price;
    
    bool disposable; // 나는 성공적으로 use되었을 경우, inventory로부터 없어져도 되고, 심지어는 delete되어 heap으로부터도 즉시 사라져야 한다.
    bool removable;  // 나는 성공적으로 use되었을 경우, inventory로부터 없어져도 되지만, 다른곳으로 옮겨진 케이스가 대부분이므로(armor나 weapon처럼) 절대 delete하지 말 것.
    
    bool removed;    // removable일 경우, 이 removed가 true면 inventory에서 지우면 된다.
    
public:
    Item();
    Item(char shape, string name, int price, bool disposable, bool removable);
    virtual ~Item();
    
    void print();
    virtual void printFullSpec(ostream &out);
    
    char getShape();
    
    string getName();
    int getPrice();
    
    bool isDisposable();
    bool isRemovable();
    bool isRemoved();
    
    virtual bool isConsumable();
    virtual bool isEquippable();
    
    virtual bool use(Unit *unit) = 0; // pure virtual function
    
    virtual Item *clone() = 0; // pure virtual function
    
    static Item *createRandomItem();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName() = 0;
    static Item *createItemByID(string classTypeName);

    friend ostream &operator<<(ostream &out, const Item &obj);
};



#endif
