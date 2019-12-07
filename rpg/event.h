#ifndef EVENT_H
#define EVENT_H

class Event;
class Monster;

class EventWrapper {
public:
    Event *event;
    
    EventWrapper();
    EventWrapper(Event *event);
    
    virtual ~EventWrapper();
    
    bool operator<(const EventWrapper &other);
    bool operator<=(const EventWrapper &other);
    bool operator>(const EventWrapper &other);
    bool operator>=(const EventWrapper &other);
    
    friend ostream &operator<<(ostream &out, const EventWrapper &obj);
};

ostream &operator<<(ostream &out, const EventWrapper &obj);

//==============================================================================
// class Event
//==============================================================================
class Event {
public:
    int time;
    
    Event();
    Event(int time);
    virtual ~Event();
    
    void print();

    bool operator==(const Event &other);
    
    bool operator<(const Event &other);
    bool operator<=(const Event &other);
    bool operator>(const Event &other);
    bool operator>=(const Event &other);
    
    virtual void trigger();
    
    friend ostream &operator<<(ostream &out, const Event &obj);
};

ostream &operator<<(ostream &out, const Event &obj);

//==============================================================================
// class DayAndNightEvent
//==============================================================================
class DayAndNightEvent : public Event {
private:
    int interval;
    
public:
    DayAndNightEvent();
    DayAndNightEvent(int time);
    DayAndNightEvent(int time, int interval);
    virtual ~DayAndNightEvent();
    
    virtual void trigger();
};

//==============================================================================
// class MonRespawnEvent
//==============================================================================
class MonRespawnEvent : public Event {
private:
    Monster *mon;
    
public:
    MonRespawnEvent();
    MonRespawnEvent(int time, Monster *mon);
    virtual ~MonRespawnEvent();
    
    virtual void trigger();
};

//==============================================================================
// class MonsterStatPrintEvent
//==============================================================================
class MonsterStatPrintEvent : public Event {
private:
public:
    MonsterStatPrintEvent();
    MonsterStatPrintEvent(int time);
    virtual ~MonsterStatPrintEvent();
    
    virtual void trigger();
};

//==============================================================================
// class NewMapSpawnEvent
//==============================================================================
class NewMapSpawnEvent : public Event {
private:
public:
    NewMapSpawnEvent();
    NewMapSpawnEvent(int time);
    virtual ~NewMapSpawnEvent();
    
    virtual void trigger();
};

//==============================================================================
// class StatLogEvent
//==============================================================================
class StatLogEvent : public Event {
private:
    int logInterval;
    string logFilename;
    
public:
    StatLogEvent();
    StatLogEvent(int time, int logInterval, string logFilename);
    
    void trigger();
};

#endif

