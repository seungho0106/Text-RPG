#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "item.h"
#include "armor.h"
#include "weapon.h"
#include "unit.h"
#include "paperdoll.h"

Paperdoll::Paperdoll() {
    head = NULL;
    back = NULL;
    chest = NULL;
    gloves = NULL;
    legs = NULL;
    feet = NULL;
    
    rightHand = NULL;
    leftHand = NULL;
}

Paperdoll::~Paperdoll() {
    if (head != NULL) {
        delete head;
    }
    if (back != NULL) {
        delete back;
    }
    if (chest != NULL) {
        delete chest;
    }
    if (gloves != NULL) {
        delete gloves;
    }
    if (legs != NULL) {
        delete legs;
    }
    if (feet != NULL) {
        delete feet;
    }
    if (rightHand != NULL) {
        delete rightHand;
    }
    if (leftHand != NULL) {
        delete leftHand;
    }
}

void Paperdoll::print() {
    cout << "+--------------------------------------+" << endl;
    cout << "|" << ARMOR_BODYPART_ID_HEAD << ":HEAD(" << ((head == NULL)?' ':head->getShape()) << ")   [" << setw(17) << left << ((head == NULL)?"":head->getName()) << "] def(" << ((head == NULL)?0:head->getDef()) << ")|" << endl;
    cout << "|" << ARMOR_BODYPART_ID_CHEST << ":CHEST(" << ((chest == NULL)?' ':chest->getShape()) << ")  [" << setw(17) << left << ((chest == NULL)?"":chest->getName()) << "] def(" << ((chest == NULL)?0:chest->getDef()) << ")|" << endl;
    cout << "|" << ARMOR_BODYPART_ID_GLOVES << ":GLOVES(" << ((gloves == NULL)?' ':gloves->getShape()) << ") [" << setw(17) << left << ((gloves == NULL)?"":gloves->getName()) << "] def(" << ((gloves == NULL)?0:gloves->getDef()) << ")|" << endl;
    cout << "|" << ARMOR_BODYPART_ID_BACK << ":BACK(" << ((back == NULL)?' ':back->getShape()) << ")   [" << setw(17) << left << ((back == NULL)?"":back->getName()) << "] def(" << ((back == NULL)?0:back->getDef()) << ")|" << endl;
    cout << "|" << ARMOR_BODYPART_ID_LEGS << ":LEGS(" << ((legs == NULL)?' ':legs->getShape()) << ")   [" << setw(17) << left << ((legs == NULL)?"":legs->getName()) << "] def(" << ((legs == NULL)?0:legs->getDef()) << ")|" << endl;
    cout << "|" << ARMOR_BODYPART_ID_FEET << ":FEET(" << ((feet == NULL)?' ':feet->getShape()) << ")   [" << setw(17) << left << ((feet == NULL)?"":feet->getName()) << "] def(" << ((feet == NULL)?0:feet->getDef()) << ")|" << endl;
    cout << "|" << WEAPON_BODYPART_ID_LEFT_HAND << ":LH(" << ((leftHand == NULL)?' ':leftHand->getShape()) << ")     [" << setw(17) << left << ((leftHand == NULL)?"":leftHand->getName()) << "] atk(" << ((leftHand == NULL)?0:leftHand->getAtk()) << ")|" << endl;
    cout << "|" << WEAPON_BODYPART_ID_RIGHT_HAND << ":RH(" << ((rightHand == NULL)?' ':rightHand->getShape()) << ")     [" << setw(17) << left << ((rightHand == NULL)?"":rightHand->getName()) << "] atk(" << ((rightHand == NULL)?0:rightHand->getAtk()) << ")|" << endl;
    cout << "+--------------------------------------+" << endl;
}

bool Paperdoll::equip(Item *itemToEquip, Unit *unit) {
    if (itemToEquip->isEquippable()) {
        EquippableItem *equippableItem = (EquippableItem *)itemToEquip;
        if (equippableItem->isArmor()) {
            Armor *armorToEquip = (Armor *)equippableItem;
            if (head == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_HEAD) {
                head = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
            else if (chest == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_CHEST) {
                chest = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
            else if (gloves == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_GLOVES) {
                gloves = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
            else if (back == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_BACK) {
                back = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
            else if (legs == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_LEGS) {
                legs = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
            else if (feet == NULL && armorToEquip->getBodyPartID() == ARMOR_BODYPART_ID_FEET) {
                feet = armorToEquip;
                unit->incDef(armorToEquip->getDef());
                return true;
            }
        }
        else {
            Weapon *weaponToEquip = (Weapon *)equippableItem;
            if (weaponToEquip->getNumHands() == WEAPON_ONE_HAND) {
                if (rightHand == NULL) {
                    rightHand = weaponToEquip;
                    unit->incAtk(weaponToEquip->getAtk());
                    return true;
                }
                else if (leftHand == NULL) {
                    leftHand = weaponToEquip;
                    unit->incAtk(weaponToEquip->getAtk());
                    return true;
                }
            }
            else { // if (weaponToEquip->getNumHands() == WEAPON_TWO_HAND) {
                if (rightHand == NULL) {
                    rightHand = weaponToEquip;
                    unit->incAtk(weaponToEquip->getAtk());
                    return true;
                }
            }
        }
    }
    
    return false;
}

Item *Paperdoll::unequip(int bodyPartID, Unit *unit) {
    if (bodyPartID == ARMOR_BODYPART_ID_HEAD) {
        if (head != NULL) {
            unit->decDef(head->getDef());
            Item *itemToReturn = head;
            head = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == ARMOR_BODYPART_ID_CHEST) {
        if (chest != NULL) {
            unit->decDef(chest->getDef());
            Item *itemToReturn = chest;
            chest = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == ARMOR_BODYPART_ID_GLOVES) {
        if (gloves != NULL) {
            unit->decDef(gloves->getDef());
            Item *itemToReturn = gloves;
            gloves = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == ARMOR_BODYPART_ID_BACK) {
        if (back != NULL) {
            unit->decDef(back->getDef());
            Item *itemToReturn = back;
            back = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == ARMOR_BODYPART_ID_LEGS) {
        if (legs != NULL) {
            unit->decDef(legs->getDef());
            Item *itemToReturn = legs;
            legs = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == ARMOR_BODYPART_ID_FEET) {
        if (feet != NULL) {
            unit->decDef(feet->getDef());
            Item *itemToReturn = feet;
            feet = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == WEAPON_BODYPART_ID_LEFT_HAND) {
        if (leftHand != NULL) {
            unit->decAtk(leftHand->getAtk());
            Item *itemToReturn = leftHand;
            leftHand = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == WEAPON_BODYPART_ID_RIGHT_HAND) {
        if (rightHand != NULL) {
            unit->decAtk(rightHand->getAtk());
            Weapon *weaponToReturn = rightHand;
            if (weaponToReturn->getNumHands() == WEAPON_ONE_HAND) {
                rightHand = leftHand;
                leftHand = NULL;
            }
            else { // if (weaponToReturn->getNumHands() == WEAPON_TWO_HAND) {
                rightHand = NULL;
            }
            return weaponToReturn;
        }
    }
    return NULL;
}

void Paperdoll::save(ostream &out) {
    out << "#-------------------- class Paperdoll" << endl;
    out << "# head" << endl;
    if (head != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        head->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# back" << endl;
    if (back != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        back->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# chest" << endl;
    if (chest != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        chest->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# gloves" << endl;
    if (gloves != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        gloves->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# legs" << endl;
    if (legs != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        legs->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# feet" << endl;
    if (feet != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        feet->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# leftHand" << endl;
    if (leftHand != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        leftHand->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "# rightHand" << endl;
    if (rightHand != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        rightHand->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
}

void Paperdoll::load(istream &in) {
    char buf[250];
//    out << "#-------------------- class Paperdoll" << endl;
    in.getline(buf, 250);
//    out << "# head" << endl;
    in.getline(buf, 250);
//    if (head != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        head->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        head = new Armor();
        head->load(in);
    }
    else {
        head = NULL;
    }
//    out << "# back" << endl;
    in.getline(buf, 250);
//    if (back != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        back->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        back = new Armor();
        back->load(in);
    }
    else {
        back = NULL;
    }
//    out << "# chest" << endl;
    in.getline(buf, 250);
//    if (chest != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        chest->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        chest = new Armor();
        chest->load(in);
    }
    else {
        chest = NULL;
    }
//    out << "# gloves" << endl;
    in.getline(buf, 250);
//    if (gloves != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        gloves->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        gloves = new Armor();
        gloves->load(in);
    }
    else {
        gloves = NULL;
    }
//    out << "# legs" << endl;
    in.getline(buf, 250);
//    if (legs != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        legs->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        legs = new Armor();
        legs->load(in);
    }
    else {
        legs = NULL;
    }
//    out << "# feet" << endl;
    in.getline(buf, 250);
//    if (feet != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        feet->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        feet = new Armor();
        feet->load(in);
    }
    else {
        feet = NULL;
    }
//    out << "# leftHand" << endl;
    in.getline(buf, 250);
//    if (leftHand != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        leftHand->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        leftHand = new Weapon();
        leftHand->load(in);
    }
    else {
        leftHand = NULL;
    }
//        out << "# rightHand" << endl;
    in.getline(buf, 250);
//        if (rightHand != NULL) {
//            out << TOMBSTONE_NOT_EMPTY << endl;
//            rightHand->save(out);
//        }
//        else {
//            out << TOMBSTONE_EMPTY << endl;
//        }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        rightHand = new Weapon();
        rightHand->load(in);
    }
    else {
        rightHand = NULL;
    }
}
