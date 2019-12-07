#ifndef PROP_H
#define PROP_H

class Unit;

//------------------------------------------------------------------------------
// class Prop
//------------------------------------------------------------------------------
class Prop { // parent class of class Tree/Portal
protected:
    char shape;
    
	int row;
	int col;
    
public:
    Prop();
    Prop(char shape);
    virtual ~Prop();
    
    void print();

	int getRow();
	void setRow(int row);

	int getCol();
	void setCol(int col);
    
    virtual bool isClimbable();
    
    virtual bool isPortal();
    virtual bool isExit();
    
    virtual void trigger(Unit *unit);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName() = 0;
    static Prop *createPropByID(string classTypeName);
};

//------------------------------------------------------------------------------
// class Tree
//------------------------------------------------------------------------------
class Tree : public Prop {
protected:
public:
    Tree();
    virtual ~Tree();
    
    virtual void trigger(Unit *unit);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

//------------------------------------------------------------------------------
// class Portal
//------------------------------------------------------------------------------
class Portal : public Prop {
protected:
public:
    Portal();
    Portal(char shape);
    virtual ~Portal();

    bool isClimbable();

    bool isPortal();

    virtual void trigger(Unit *unit);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

//------------------------------------------------------------------------------
// class Exit
//------------------------------------------------------------------------------
class Exit : public Portal {
protected:
public:
    Exit();
    virtual ~Exit();
        
    virtual bool isExit();
    
    virtual void trigger(Unit *unit);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual string getClassTypeName();
};

#endif
