#ifndef PET_H
#define PET_H

#include "unit.h"

class Pet : public Unit {
protected:
public:
    Pet();
    virtual ~Pet();
    
    bool isPet();
    
    void move(int dir);
    void interact(Unit *unit);
    
    bool isDirStuck(int curRow, int curCol, int curDir);
};

#endif
