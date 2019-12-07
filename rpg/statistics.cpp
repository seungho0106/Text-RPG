#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

Statistics::Statistics() {
    totalNumStepsHero = 0;
    numMonsKilled = 0;
//    totalMonRespawnInterval = 0.0;
    logging = true;
//
//    totalNumProjectileUsed = 0;
//    totalNumShockWaveUsed=0;
//    totalNumKnockbackUsed=0;
//    totalNumMeleeAttackUsed=0;
//    totalNumAttacks = 0;
}

Statistics::~Statistics() {}

//Time      |TtlSteps  |numMonsKilled  |avgMonRespInterval  |ProjectileRatio|ShockWaveRatio |KnockbackRatio |MeleeAttack    |
//----------+----------+---------------+--------------------+---------------+---------------+---------------+---------------+
//         0|         0|              0|                   0|              0|              0|              0|              0|
void Statistics::printHeader(ostream &out) {
    if (logging) {
        out << setw(10) << std::left << "Time" << "|" << setw(10) << std::left << "TtlSteps" << "|" << setw(15) << std::left << "numMonsKilled" << "|" << setw(20) << std::left << "avgMonRespInterval" << "|" 
			<< setw(15) << std::left << "ProjectileRatio" << "|" << setw(15) << std::left << "ShockWaveRatio" << "|" << setw(15) << std::left << "KnockbackRatio" << "|" << setw(15) << std::left << "MeleeAttack" << "|" << endl;
        out << "----------+----------+---------------+--------------------+---------------+---------------+---------------+---------------+" << endl;
    }
}

void Statistics::printStat(ostream &out) {
    if (logging) {
//        double avgMonRespInterval = 0.0;
//        if (numMonsKilled != 0) {
//            avgMonRespInterval = totalMonRespawnInterval / numMonsKilled;
//        }
//
//        double ratioProjectileUsed = 0.0;
//        double ratioShockWaveUsed = 0.0;
//        double ratioKnockbackUsed = 0.0;
//        double ratioMeleeAttackUsed = 0.0;
//        if (totalNumAttacks != 0) {
//            ratioProjectileUsed = totalNumProjectileUsed / totalNumAttacks;
//            ratioShockWaveUsed = totalNumShockWaveUsed / totalNumAttacks;
//            ratioKnockbackUsed = totalNumKnockbackUsed / totalNumAttacks;
//            ratioMeleeAttackUsed = totalNumMeleeAttackUsed / totalNumAttacks;
//        }
//        
//        //C: printf("%10d|%10d|%10d|%10.2lf\n", (sim->time / FPS), totalNumStepsHero, numMonsKilled, avgMonRespInterval);
        out << setw(10) << right << fixed << setprecision(1) << (sim->time / FPS) << "|" << setw(10) << right << totalNumStepsHero << "|" << setw(15) << std::right << numMonsKilled << endl;
//        out << setw(10) << right << fixed << setprecision(1) << (sim->time / FPS) << "|" << setw(10) << right << totalNumStepsHero << "|" << setw(15) << std::right << numMonsKilled << "|" << setw(20) << std::left << std::fixed << setprecision(2) << std::right << avgMonRespInterval << "|"
//            << setw(15) << std::left << std::fixed << setprecision(2) << std::right << ratioProjectileUsed << "|" 
//            << setw(15) << std::left << std::fixed << setprecision(2) << std::right << ratioShockWaveUsed << "|"
//            << setw(15) << std::left << std::fixed << setprecision(2) << std::right << ratioKnockbackUsed << "|"
//            << setw(15) << std::left << std::fixed << setprecision(2) << std::right << ratioMeleeAttackUsed << "|" << endl;
    }
}

void Statistics::toggleLog() {
    logging = !logging;
}

void Statistics::turnOnLog() {
    logging = true;
}

void Statistics::turnOffLog() {
    logging = false;
}
