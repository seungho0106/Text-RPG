#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

#ifdef _MBCS
#include <windows.h>
#include <conio.h>
#include <dos.h>
#else
#include <unistd.h>
#endif

using namespace std;

#include "main.h"
#include "board.h"
#include "util.h"
#include "unit.h"
#include "hero.h"
#include "monster.h"
#include "merchant.h"
#include "item.h"
#include "inventory.h"
#include "backpack.h"
#include "event.h"

#include "sim.h"
Sim *sim = NULL;

int main() {
    srand((unsigned)time(NULL));
    
    sim = new Sim();

    sim->eventQueue->enqueue(EventWrapper(new DayAndNightEvent(sim->time+DAY_AND_NIGHT_INTERVAL, DAY_AND_NIGHT_INTERVAL)));

#ifdef LOG_EVENT_ON
    sim->eventQueue->enqueue(EventWrapper(new StatLogEvent(sim->time+STAT_LOG_EVENT_INTERVAL, STAT_LOG_EVENT_INTERVAL, "statistics.txt")));
#endif
    
    while (true) {
        sim->board->print();
        
        //----------------------------------------------------------------------
        // System Message
        //----------------------------------------------------------------------
        if (sim->systemMessage != "") {
            if (sim->tempSystemMessage != sim->systemMessage) {
                sim->tempSystemMessage = sim->systemMessage;
                sim->systemMessageCount = 0;
            }
            else if (sim->systemMessageCount >= SYSTEM_MESSAGE_INTERVAL) {
                sim->systemMessage = "";
                sim->systemMessageCount = 0;
            }
            cout << "SYSTEM: [ " << setw(40) << left << sim->systemMessage << " ]" << endl;
            sim->systemMessageCount++;
        }
        //----------------------------------------------------------------------
        
        sim->board->printEngaged();
        
        sim->hero->printStat();
        
        cout << "sim->time: " << sim->time << endl;
        
        //----------------------------------------------------------------------
        // event 처리 loop
        //----------------------------------------------------------------------
        while (sim->eventQueue->size() > 0 &&
               sim->eventQueue->peek().event->time <= sim->time) {
            Event *curEvent = sim->eventQueue->dequeue().event;
            curEvent->trigger();
        }
        //----------------------------------------------------------------------

        if (_kbhit()) {
#ifdef _MBCS
            char command = _getch();
#else
            char command = getchar();
#endif
            //------------------------------------------------------------------
            // Move hero
            //------------------------------------------------------------------
            int heroDir = DIR_NONE;
            
            if (command == 'w' || command == 'W') { // N
                heroDir = DIR_N;
            }
            else if (command == 'd' || command == 'D') { // E
                heroDir = DIR_E;
            }
            else if (command == 's' || command == 'S') { // S
                heroDir = DIR_S;
            }
            else if (command == 'a' || command == 'A') { // W
                heroDir = DIR_W;
            }
            
            sim->hero->move(heroDir);

            //------------------------------------------------------------------
            // Use item
            //------------------------------------------------------------------
            if (command >= '1' && command <= '5') {
                int itemIndex = command - '1';
                sim->hero->useItem(itemIndex);
            }

            //------------------------------------------------------------------
            // Unequip
            //------------------------------------------------------------------
            if (command == 'u' || command == 'U') {
                int bodyPartID;
                cout << "Enter the body part ID(-1 to cancel): ";
                cin >> bodyPartID;
                if (bodyPartID != -1) {
                    sim->hero->unequip(bodyPartID);
                }
            }

			//------------------------------------------------------------------
			// Projectile
			//------------------------------------------------------------------
            if (command == 'c' || command == 'C') {
                sim->hero->changeProjectileIndex();
            }
            if (command == 'x' || command == 'X') {
                sim->board->shootProjectiles();
			}
            
            //------------------------------------------------------------------
            // Load & Save
            //------------------------------------------------------------------
            if (command == 'o' || command == 'O') {
                string FILENAME = "";
                cout << "Enter save file name(-1 to cancel): " << endl;
                cin >> FILENAME;
                if (FILENAME != "-1") {
                    ofstream fout(FILENAME.c_str());
                    sim->board->save(fout);
                    fout.close();
                }
            }
            else if (command == 'p' || command == 'P') {
                string FILENAME = "";
                cout << "Enter load file name(-1 to cancel): " << endl;
                cin >> FILENAME;
                if (FILENAME != "-1") {
                    ifstream fin(FILENAME.c_str());
                    sim->board->load(fin);
                    fin.close();
                }
            }
            //------------------------------------------------------------------
            // Quit the game
            //------------------------------------------------------------------
            else if (command == 'q' || command == 'Q') {
                cout << "Do you want to quit the game? (Y/N)" << endl;
                char input = getchar();
                
                if (input == 'y' || input == 'Y') {
                    break;
                }
            }
		}
        
        // Move monsters
        if (sim->time % 10 == 0) {
            sim->board->moveMons();
        }
        
        // Move bosses
        if (sim->time % 5 == 0) {
            sim->board->moveBosses();
        }
        
//        // Move pet
//        if (sim->time % 5 == 0) {
//            sim->board->movePet();
//        }
        
        // Move projectiles
        if (sim->time % 2 == 0) {
            sim->board->moveProjectiles();
        }
        
#ifdef _MBCS
        Sleep(GAME_LOOP_DELAY_IN_MILLISEC);
        system("cls");
#else
        usleep(GAME_LOOP_DELAY_IN_MICROSEC);
#endif
        sim->time++;
        
        if (sim->hero->isDead()) {
            sim->board->print();
            sim->hero->printStat();
            cout << "GAME OVER! Press enter to exit..." << endl;
            int command = getchar();
            break;
        }
    }

    delete sim;
    
    return 0;
}
