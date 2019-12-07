#include <iostream>
#include <math.h>

using namespace std;

#include "main.h"
#include "unit.h"
#include "tile.h"
#include "prop.h"
#include "hero.h"
#include "monster.h"
#include "boss.h"
#include "board.h"
#include "set.h"

#include "sim.h"
extern Sim *sim;

Boss::Boss() : Monster(BOSS_SHAPE, -1, -1, DIR_NONE, BOSS_DEFAULT_RANGE, BOSS_MAX_HP, BOSS_MAX_HP, BOSS_MAX_MP, BOSS_MAX_MP, BOSS_DEFAULT_ATK, BOSS_DEFAULT_DEF, BOSS_DEFAULT_GOLD, BOSS_DEFAULT_EXP, BOSS_DEFAULT_LVL) { // default cons
    
    //--------------------------------------------------------------------------
    // IQ100/IQ120이상에서 사용.
    //--------------------------------------------------------------------------
    pathFound = false;
    
    maxLenPath = MAX_LEN_PATH;
    lenPath = 0;
    
    curIndexPath = 0;
}

Boss::~Boss() { // destructor
}

void Boss::reset() {
    Unit::reset();
}

bool Boss::isBoss() {
	return true;
}

void Boss::move(int dir) {
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    // boss의 memory에 뭔가 가야할 곳이 있다면, 계속 간다.
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    if (pathFound) {
        int nextRow = path[ROW][curIndexPath];
        int nextCol = path[COL][curIndexPath];
        
        if ((sim->board->getProp(nextRow, nextCol) == NULL ||
             sim->board->getProp(nextRow, nextCol)->isClimbable()) &&
            sim->board->getUnit(nextRow, nextCol) == NULL) {
            sim->board->setUnit(row, col, NULL);
            sim->board->setUnit(nextRow, nextCol, this);
                
            dir = pathDir[curIndexPath];
            curIndexPath++;
            
            if (curIndexPath >= lenPath) { // 도착했다면..
                pathFound = false;
                lenPath = 0;
                curIndexPath = 0;
            }
        }
        return;
    }
    //--------------------------------------------------------------------------

    bool heroFound = false;
    Hero *hero = NULL;
    int heroRow = -1;
    int heroCol = -1;

    for (int i = row-range; i <= row+range && !heroFound; i++) { // Hero Tracking
        for (int j = col-range; j <= col+range && !heroFound; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                sim->board->getUnit(i, j)->isHero()) {
                heroFound = true;
                hero = (Hero *)sim->board->getUnit(i, j);
                heroRow = i;
                heroCol = j;
            }
        }
    }

    if (heroFound) {
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        // IQ 80: 무조건 hero에게 접근
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
#ifdef BOSS_IQ_80
        // 같은 horz 라인에 있을 경우.
        if (row == heroRow) {
            if (col > heroCol) { // left?
                if (col-1 == heroCol) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
				else {
					dir = DIR_W;
				}
            }
            else { // right?
                if (col+1 == heroCol) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
				else {
					dir = DIR_E;
				}
            }
        }
        // 같은 vert 라인에 있을 경우.
        else if (col == heroCol) {
            if (row > heroRow) { // up?
                if (row-1 == heroRow) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
				else {
					dir = DIR_N;
				}
            }
            else { // down?
                if (row+1 == heroRow) { // adjacent?
                    hero->interact(this);
                    dir = DIR_NONE;
                }
				else {
					dir = DIR_S;
				}
            }
        }
        // NW/NE/SW/SE 4개의 블럭중 한개에 있다.
        else {
            int diffRow = abs(row - heroRow);
            int diffCol = abs(col - heroCol);
            
			if (heroRow < row && heroCol < col) { //NW
				if (diffCol < diffRow) {
					dir = DIR_N;
				}
				else {
					dir = DIR_W;
				}
			}
			else if (heroRow < row && col < heroCol) { //NE
				if (diffCol < diffRow) {
					dir = DIR_N;
				}
				else {
					dir = DIR_E;
				}
			}
			else if (row < heroRow && heroCol < col) { //SW
				if (diffCol < diffRow) {
					dir = DIR_S;
				}
				else {
					dir = DIR_W;
				}
			}
			else if (row < heroRow && col < heroCol) { //SE
				if (diffCol < diffRow) {
					dir = DIR_S;
				}
				else {
					dir = DIR_E;
				}
			}
        }
#endif // end of BOSS_IQ_80
        
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        // IQ 100: Wall Follower Algorithm
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
#ifdef BOSS_IQ_100
        if (isDirStuck(dir, row, col)) {
//        bool pathFound;
//
//        int path[2][MAX_LEN_PATH];
//        int maxLenPath;
//        int lenPath;
//
//        int curIndexPath;
            //----------------------------------------------------------------------
            // 현재 진행 방향이 막혔을 경우에 한 해, Goal을 먼저 발견할 것.
            //----------------------------------------------------------------------
            int goalRow = row;
            int goalCol = col;
            
            //----------------------------------------------------------------------
            // find goal:
            //     현재 진행하는 방향으로(일단 막혔을 것이다) 막히지 않는 곳이 나올 때까지 가면
            //     그곳이 빈 곳이다.
            //----------------------------------------------------------------------
            while (true) {
                if (!isDirStuck(dir, goalRow, goalCol)) {
                    goalRow += (dir == DIR_N)?-1:((dir == DIR_S)?1:0);
                    goalCol += (dir == DIR_W)?-1:((dir == DIR_E)?1:0);
                    break;
                }
                
                // move goal position
                goalRow += (dir == DIR_N)?-1:((dir == DIR_S)?1:0);
                goalCol += (dir == DIR_W)?-1:((dir == DIR_E)?1:0);
            }
            
            //------------------------------------------------------------------
            // Wall Follower Algorithm
            //------------------------------------------------------------------
            // 1) 현재 진행 방향으로 가려고 한다.
            //     1-a) 막혔다면..
            //         왼쪽으로 돈다.
            //         (1)로 간다.
            //     1-b) 막히지 않았다면..
            //         진행한다
            //             Goal이면..
            //                 앨거리듬을 끝낸다.
            //             Goal이 아니면..
            //                 오른쪽으로 돈다.
            //                 (1)로 간다.
            //------------------------------------------------------------------
            pathFound = false;
            lenPath = 0;
            curIndexPath = 0;
            
            int curDir = dir;
            int curRow = row;
            int curCol = col;
            
            while (true) {
                // 1) 현재 진행 방향으로 가려고 한다.
                if (isDirStuck(curDir, curRow, curCol)) {
                    // 1-a) 막혔다면..
                    curDir = turnLeft(curDir);
                }
                else {
                    // 1-b) 막히지 않았다면..
                    goForward(curDir, curRow, curCol);
                    
                    // 현재 위치를 boss의 memory에 기록해둔다.
                    path[ROW][lenPath] = curRow;
                    path[COL][lenPath] = curCol;
                    pathDir[lenPath] = curDir;
                    lenPath++;

                    if (curRow == goalRow && curCol == goalCol) { // Goal이면..
                        // 앨거리듬을 끝낸다.
                        pathFound = true;
                        curIndexPath = 0;
                        break;
                    }
                    else { // Goal이 아니면..
                        curDir = turnRight(curDir);
                    }
                }
                
                if (lenPath >= MAX_LEN_PATH) {
                    break;
                }
            }
            
//            if (pathFound) {
//                cout << "Boss::move()::IQ100: PATH FOUND!!" << endl;
//
//                cout << "lenPath: " << lenPath << endl;
//                for (int i = 0; i < lenPath; i++) {
//                    cout << "(" << path[ROW][i] << ", " << path[COL][i] << ")->";
//                }
//                cout << endl;
//            }
//            else {
//                cout << "Boss::move()::IQ100: PATH NOT FOUND!!" << endl;
//            }
//            exit(1);
//        }
#endif // end of BOSS_IQ_100
        
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        // IQ 120: A*
        // Source: https://en.wikipedia.org/wiki/A*_search_algorithm
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
#ifdef BOSS_IQ_120
        if (isDirStuck(dir, row, col)) {
//            for (int i = 0; i < sim->board->getRowSize(); i++) {
//                for (int j = 0; j < sim->board->getRowSize(); j++) {
//                    sim->board->getTileAt(i, j)->astarReset();
//                }
//            }
            
            //cout << "Boss::BOSS_IQ_120:---------------------------------------------------- (" << row << ", " << col << ")" << endl;
			int goalRow = heroRow;
			int goalCol = heroCol;
            Tile *goal = sim->board->getTileAt(goalRow, goalCol);
//            cout << "Boss::move()::IQ120: goal = ";
//            goal->printAStarInfo();
//            cout << endl;

			Set *closedSet = new Set();
			Set *openSet = new Set();
			
            // For each node, which node it can most efficiently be reached from.
            // If a node can be reached from many nodes, cameFrom will eventually contain the
            // most efficient previous step.
            //cameFrom := an empty map
        
            // For each node, the cost of getting from the start node to that node.
            //gScore := map with default value of Infinity
        
            // For each node, the total cost of getting from the start node to the goal
            // by passing by that node. That value is partly known, partly heuristic.
            //fScore := map with default value of Infinity
        
			Tile *start = sim->board->getTileAt(row, col);
			openSet->add(start);
            
            // The cost of going from start to start is zero.
            //gScore[start] := 0
			start->g = 0.0;
            
            // For the first node, that value is completely heuristic.
            //fScore[start] := heuristic_cost_estimate(start, goal)
            start->h = start->calcH(goal);
            start->f = start->g + start->h;

            int maxIter = MAX_LEN_PATH-1;

            // while openSet is not empty
			while (!openSet->isEmpty()) {
                // current := the node in openSet having the lowest fScore[] value
				Tile *current = openSet->removeMinF();
                //cout << "Boss::move()::IQ120: current = ";
                //current->printAStarInfo();
                //cout << endl;
                
                // if current = goal
                if (current == goal) {
                    // return reconstruct_path(cameFrom, current)
//                    cout << "Boss::move()::IQ120: if (current == goal) { | goal = ";
//                    goal->printAStarInfo();
//                    cout << endl;
//                    exit(1);
                    reconstruct_path(start, goal);
                    return;
                }

                // openSet.Remove(current)
                // closedSet.Add(current)
                closedSet->add(current);

                // for each neighbor of current
                for (int i = 0; i < NUM_DIRS; i++) {
                    Tile *neighbor = getNeighborWhenNotBlockedIgnoreUnit(current, i);
                    
                    if (neighbor != NULL) {
                        //cout << "Boss::move()::IQ120: i = " << i << " | neighbor = ";
                        //neighbor->printAStarInfo();
                        //cout << endl;
                        
                        // if neighbor in closedSet
                        if (closedSet->find(neighbor)) {
                            // 특정 try이상 돌지 않게..
                            maxIter--;
                            if (maxIter <= 0) {
                                break;
                            }
                            continue;        // Ignore the neighbor which is already evaluated.
                        }
                        
                        // if neighbor not in openSet    // Discover a new node
                        if (!openSet->find(neighbor)) {
                            openSet->add(neighbor);
                        }
                        
                        // The distance from start to a neighbor
                        // the "dist_between" function may vary as per the solution requirements.
                        // tentative_gScore := gScore[current] + dist_between(current, neighbor)
                        double tentativeGScore = current->g + 1.0;
                        
                        if (tentativeGScore >= neighbor->g) {
                            // 특정 try이상 돌지 않게..
                            maxIter--;
                            if (maxIter <= 0) {
                                break;
                            }
                            continue;        // This is not a better path.
                        }
            
                        // This path is the best until now. Record it!
                        // cameFrom[neighbor] := current
                        neighbor->cameFrom = getParentTileDir(neighbor, current);
                        // gScore[neighbor] := tentative_gScore
                        neighbor->g = tentativeGScore;
                        // fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
                        neighbor->h = neighbor->calcH(goal);
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
                
                // 특정 try이상 돌지 않게..
                maxIter--;
                if (maxIter <= 0) {
                    break;
                }
            }
        }
#endif // end of BOSS_IQ_120: A*
    }
    
    Monster::move(dir);
}

//------------------------------------------------------------------------------
// IQ100/IQ120이상에서 사용.
//------------------------------------------------------------------------------

int Boss::turnLeft(int curDir) {
    return (curDir + NUM_DIRS - 1) % NUM_DIRS;
}

int Boss::turnRight(int curDir) {
    return (curDir + 1) % NUM_DIRS;
}

// pre-condition: 진행방향으로 막히지 않았음.
void Boss::goForward(int curDir, int &curRow, int &curCol) {
    curRow += (curDir == DIR_N)?-1:((curDir == DIR_S)?1:0);
    curCol += (curDir == DIR_W)?-1:((curDir == DIR_E)?1:0);
}

/*
 function reconstruct_path(cameFrom, current)
 total_path := [current]
 while current in cameFrom.Keys:
 current := cameFrom[current]
 total_path.append(current)
 return total_path
 */
void Boss::reconstruct_path(Tile *start, Tile *goal) {
//    cout << "Boss::IQ120::reconstruct_path(): started!!" << endl;

    //--------------------------------------------------------------------------
    // get lenPath
    //--------------------------------------------------------------------------
    lenPath = 0;
    
    Tile *curTile = getParentTileByCameFrom(goal);
    
    while (curTile != NULL && curTile != start) {
        lenPath++;
        curTile = getParentTileByCameFrom(curTile);
    }

    //--------------------------------------------------------------------------
    // record path
    //--------------------------------------------------------------------------
    curTile = getParentTileByCameFrom(goal);
    
    int i = lenPath-1;
    while (curTile != NULL && curTile != start) {
        path[ROW][i] = curTile->row;
        path[COL][i] = curTile->col;
        pathDir[i] = (curTile->cameFrom + 2) % NUM_DIRS;
        i--;
        
        curTile = getParentTileByCameFrom(curTile);
    }
    
    pathFound = true;
    curIndexPath = 0;
    
//    cout << "Boss::IQ120::reconstruct_path(): PATH FOUND!!" << endl;
//
//    cout << "lenPath: " << lenPath << endl;
//    for (int i = 0; i < lenPath; i++) {
//        cout << "(" << path[ROW][i] << ", " << path[COL][i] << ")->";
//    }
//    cout << endl;
//    exit(1);
}

Tile *Boss::getNeighborWhenNotBlockedIgnoreUnit(Tile *current, int dir) {
    if (dir == DIR_N && current->row > 0 &&
        (sim->board->getProp(current->row-1, current->col) == NULL ||
         sim->board->getProp(current->row-1, current->col)->isClimbable())) {
        return sim->board->getTileAt(current->row-1, current->col);
    }
    else if (dir == DIR_E && current->col < sim->board->getColSize()-1 &&
             (sim->board->getProp(current->row, current->col+1) == NULL ||
              sim->board->getProp(current->row, current->col+1)->isClimbable())) {
        return sim->board->getTileAt(current->row, current->col+1);
    }
    else if (dir == DIR_S && current->row < sim->board->getRowSize()-1 &&
             (sim->board->getProp(current->row+1, current->col) == NULL ||
              sim->board->getProp(current->row+1, current->col)->isClimbable())) {
        return sim->board->getTileAt(current->row+1, current->col);
    }
    else if (dir == DIR_W && current->col > 0 &&
             (sim->board->getProp(current->row, current->col-1) == NULL ||
              sim->board->getProp(current->row, current->col-1)->isClimbable())) {
        return sim->board->getTileAt(current->row, current->col-1);
    }

    return NULL;
}

int Boss::getParentTileDir(Tile *me, Tile *parent) {
    if (me->row-1 == parent->row) {
        return DIR_N;
    }
    else if (me->col+1 == parent->col) {
        return DIR_E;
    }
    else if (me->row+1 == parent->row) {
        return DIR_S;
    }
    else if (me->col-1 == parent->col) {
        return DIR_W;
    }
    
    return DIR_NONE;
}

Tile *Boss::getParentTileByCameFrom(Tile *me) {
    if (me->cameFrom != DIR_NONE) {
        if (me->cameFrom == DIR_N) {
            return sim->board->getTileAt(me->row-1, me->col);
        }
        else if (me->cameFrom == DIR_E) {
            return sim->board->getTileAt(me->row, me->col+1);
        }
        else if (me->cameFrom == DIR_S) {
            return sim->board->getTileAt(me->row+1, me->col);
        }
        else if (me->cameFrom == DIR_W) {
            return sim->board->getTileAt(me->row, me->col-1);
        }
    }
    return NULL;
}

bool Boss::isValid(int row, int col) {
	return (row >= 0) && (row < sim->board->getRowSize()) && (col >= 0) && (col < sim->board->getColSize())
		&& (sim->board->getProp(row, col) == NULL || sim->board->getProp(row, col)->isClimbable());
}

bool Boss::isDestination(int curRow, int curCol, int goalRow, int goalCol) {
	return (curRow == goalRow) && (curCol == goalCol);
}

double Boss::calculateH(int row, int col, int heroRow, int heroCol) {
	return abs(row - heroRow) + abs(col - heroCol);
}

void Boss::pathReverse(int path[2][MAX_LEN_PATH], int lenPath) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < lenPath / 2; j++) {
			int temp = path[i][j];
			path[i][j] = path[i][lenPath - j - 1];
			path[i][lenPath - j - 1] = temp;
		}
	}
}

void Boss::save(ostream &out) {
    Monster::save(out);
    out << "#-------------------- class Boss" << endl;
}

void Boss::load(istream &in) {
    char buf[250];
    Monster::load(in);
//    out << "#-------------------- class Boss" << endl;
    in.getline(buf, 250);
}
