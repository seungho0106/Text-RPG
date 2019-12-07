#ifndef BACKPACK_H
#define BACKPACK_H

#include "item.h"

template <class T>
class Backpack {
private:
    vector<T> *slots;
    int loadSize;

public:
    Backpack() {
        slots = new vector<T>();
        loadSize = 0;
    }
    
    virtual ~Backpack() {
        delete slots;
    }
    
    void print() {
        for (int i = 0; i < slots->size(); i++) {
            cout << "[";
            if (slots[i] != NULL) {
                cout << slots[i];
            }
            else {
                cout << " ";
            }
            cout << "] ";
        }
    }
    
    void add(T elem) { // Create
        slots->push_back(elem);
    }
    
    // pre-condition: index >= 0 && index < maxNumItems
    T getItemAt(int index) { // Read
        if (index < 0 || index >= slots->size()) { // validate
            return T();
        }
        
        return (*slots)[index];
    }
    
    // pre-condition: index >= 0 && index < maxNumItems
    T removeItemAt(int index) { // Delete
        if (index < 0 || index >= slots->size()) { // validate
            return T();
        }
        
        T elemToReturn = (*slots)[index];
        
        slots->erase(slots->begin() + index);
        
        return elemToReturn;
    }
    
    int size() {
        return slots->size();
    }
    
    void save(ostream &out) {
        out << "#-------------------- class Backpack" << endl;
        out << "# size" << endl;
        out << slots->size() << endl;
        for (int i = 0; i < slots->size(); i++) {
            out << "#======================================== slots[" << i << "]" << endl;
            (*slots)[i].save(out);
        }
    }

    void load(istream &in) {
        char buf[250];
//        out << "#-------------------- class Backpack" << endl;
        in.getline(buf, 250);
//        out << "# size" << endl;
        in.getline(buf, 250);
//        out << slots->size() << endl;
        in >> loadSize >> buf[0];
        for (int i = 0; i < loadSize; i++) {
//            out << "#==================== slots[" << i << "]" << endl;
            in.getline(buf, 250);
//            (*slots)[i].save(out);
            ItemWrapper curItemWrapper;
            curItemWrapper.load(in);
            this->add(curItemWrapper);
        }
    }
};

#endif
