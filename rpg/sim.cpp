#include <iostream>

using namespace std;

#include "main.h"
#include "hero.h"
#include "event.h"
#include "board.h"
#include "sim.h"
#include "statistics.h"

Sim::Sim() {
    time = 0;
    board = new Board();
    hero = board->getHero();
    
    eventQueue = new VectorPriorityQueue<EventWrapper>();
    stat = new Statistics();

    systemMessage = "";
    tempSystemMessage = "";
    systemMessageCount = 0;
}

Sim::~Sim() {
    if (stat != NULL) {
        delete stat;
        stat = NULL;
    }
    delete eventQueue;
    delete board;
}
