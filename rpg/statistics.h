#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics {
public:
    bool logging;
    
    int totalNumStepsHero;

    int numMonsKilled;
//    double totalMonRespawnInterval;
//
//    int totalNumProjectileUsed;
//    int totalNumShockWaveUsed;
//    int totalNumKnockbackUsed;
//    int totalNumMeleeAttackUsed;
//    double totalNumAttacks;

    Statistics();
    virtual ~Statistics();
    
    void printHeader(ostream &out);
    void printStat(ostream &out);
    
    void toggleLog();
    void turnOnLog();
    void turnOffLog();
};

#endif
