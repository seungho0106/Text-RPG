#include <iostream>
#include <fstream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "prop.h"
#include "monster.h"
#include "event.h"
#include "board.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

//==============================================================================
// class EventWrapper
//==============================================================================
EventWrapper::EventWrapper() {
    event = NULL;
}

EventWrapper::EventWrapper(Event *event) {
    this->event = event;
}

EventWrapper::~EventWrapper() {
    //    cout << "EventWrapper::~EventWrapper(): start" << endl;
    //    delete event; // double deletion
    //    cout << "EventWrapper::~EventWrapper(): end" << endl;
}

bool EventWrapper::operator<(const EventWrapper &other) {
    return *event < *(other.event);
}

bool EventWrapper::operator<=(const EventWrapper &other) {
    return *event <= *(other.event);
}

bool EventWrapper::operator>(const EventWrapper &other) {
    return *event > *(other.event);
}

bool EventWrapper::operator>=(const EventWrapper &other) {
    return *event >= *(other.event);
}

ostream &operator<<(ostream &out, const EventWrapper &obj) {
    out << *(obj.event);
    return out;
}

//==============================================================================
// class Event
//==============================================================================
Event::Event() : time(0) {
}

Event::Event(int time) : time(time) {
}

Event::~Event() {
    //    cout << "Event::~Event()" << endl;
}

bool Event::operator==(const Event &other) {
    return time == other.time;
}

bool Event::operator<(const Event &other) {
    return time < other.time;
}

bool Event::operator<=(const Event &other) {
    return time <= other.time;
}

bool Event::operator>(const Event &other) {
    return time > other.time;
}

bool Event::operator>=(const Event &other) {
    return time >= other.time;
}

void Event::print() {
    cout << "time: " << time << endl;
}

void Event::trigger() {
}

ostream &operator<<(ostream &out, const Event &obj) {
    out << "time: " << obj.time;
    return out;
}

//==============================================================================
// class DayAndNightEvent
//==============================================================================
DayAndNightEvent::DayAndNightEvent() : Event() {
    interval = 0;
}

DayAndNightEvent::DayAndNightEvent(int time) : Event(time) {
    interval = DAY_AND_NIGHT_INTERVAL;
}

DayAndNightEvent::DayAndNightEvent(int time, int interval) : Event(time) {
    this->interval = interval;
}

DayAndNightEvent::~DayAndNightEvent() {
    //    cout << "DayAndNightEvent::~DayAndNightEvent()" << endl;
}

void DayAndNightEvent::trigger() {
    sim->board->toggleDayAndNight();
    
    time = sim->time + interval;
    sim->eventQueue->enqueue(EventWrapper(this)); // rescheduling needed
    // delete this; // destroy me when rescheduling is not needed.
}

//==============================================================================
// class MonRespawnEvent
//==============================================================================
MonRespawnEvent::MonRespawnEvent() : Event() {
    mon = NULL;
}

MonRespawnEvent::MonRespawnEvent(int time, Monster *mon) : Event(time) {
    this->mon = mon;
}

MonRespawnEvent::~MonRespawnEvent() {
    //    cout << "MonRespawnEvent::~MonRespawnEvent()" << endl;
}

void MonRespawnEvent::trigger() {
    //    cout << "DayAndNightEvent::trigger(): started" << endl;
    while (true) {
        int randRow = rand() % sim->board->getRowSize();
        int randCol = rand() % sim->board->getColSize();
        
        if (sim->board->getUnit(randRow, randCol) == NULL &&
            sim->board->getItem(randRow, randCol) == NULL &&
            sim->board->getProp(randRow, randCol) == NULL) {
            mon->reset();
            sim->board->setUnit(randRow, randCol, mon);
            break;
        }
    }
    
    delete this; // destroy me when rescheduling is not needed.
}

//==============================================================================
// class MonsterStatPrintEvent ??????????????????????????????????????????????????
//==============================================================================
MonsterStatPrintEvent::MonsterStatPrintEvent() : Event() {
}

MonsterStatPrintEvent::MonsterStatPrintEvent(int time) : Event(time) {
}

MonsterStatPrintEvent::~MonsterStatPrintEvent() {
}

void MonsterStatPrintEvent::trigger() {
}

//==============================================================================
// class NewMapSpawnEvent
//==============================================================================
NewMapSpawnEvent::NewMapSpawnEvent() : Event() {
}

NewMapSpawnEvent::NewMapSpawnEvent(int time) : Event(time) {
}

NewMapSpawnEvent::~NewMapSpawnEvent() {
}

void NewMapSpawnEvent::trigger() {
    Board *oldBoard = sim->board;
    sim->board = new Board(true);
    oldBoard->setHeroNULL();
    
    delete oldBoard;
    delete this; // destroy me when rescheduling is not needed.
}

//==============================================================================
// class StatLogEvent
//==============================================================================
//int logInterval;
StatLogEvent::StatLogEvent() : Event() {
    logInterval = 0;
    logFilename = "";
}

StatLogEvent::StatLogEvent(int time, int logInterval, string logFilename) : Event(time) {
    this->logInterval = logInterval;
    this->logFilename = logFilename;
    
    ofstream logFile;
    logFile.open(logFilename.c_str(), ofstream::out);
    sim->stat->printHeader(logFile);
    logFile.close();
}

void StatLogEvent::trigger() {
    ofstream logFile;
    logFile.open(logFilename.c_str(), ofstream::out | ofstream::app);
    sim->stat->printStat(logFile);
    logFile.close();
    
    // re-scheduling
    time = sim->time + logInterval;
    sim->eventQueue->enqueue(this);
}
