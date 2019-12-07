#ifndef SIM_H
#define SIM_H

#include "priority_queue.h"

class Hero;
class Board;
class EventWrapper;
class Statistics;

class Sim {
public:
    Board *board;
    Hero *hero;
    int time;
    Queue<EventWrapper> *eventQueue;
    Statistics *stat;
    
    string systemMessage;
    string tempSystemMessage;
    int systemMessageCount;
    
    Sim();
    virtual ~Sim();
};

#endif
