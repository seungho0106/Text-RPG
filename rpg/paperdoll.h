#ifndef PAPERDOLL_H
#define PAPERDOLL_H

class Item;
class Armor;
class Weapon;
class Unit;

class Paperdoll {
public:
    Armor *head;
    Armor *back;
    Armor *chest;
    Armor *gloves;
    Armor *legs;
    Armor *feet;

    Weapon *rightHand;
    Weapon *leftHand;
    
public:
    Paperdoll();
    virtual ~Paperdoll();
    
    void print();
    
    bool equip(Item *itemToEquip, Unit *unit);
    Item *unequip(int bodyPartID, Unit *unit);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
