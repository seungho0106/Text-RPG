#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "board.h"
#include "tile.h"

#include "unit.h"
#include "hero.h"
#include "pet.h"
#include "projectile.h"
#include "monster.h"
#include "boss.h"
#include "merchant.h"

#include "item.h"
#include "health_potion.h"
#include "mana_potion.h"
#include "magic_scroll.h"

#include "prop.h"
#include "shockwave.h"
#include "event.h"

#include "sim.h"
extern Sim *sim;

#ifdef TEST_BOARD_TURN_ON

//char TEST_BOARD[TEST_ROW_SIZE][TEST_COL_SIZE+1] = {
//    "..........",
//    "..Y.Y.....",
//    "..Y&Y.....",
//    "..Y.Y.....",
//    "...Y......",
//    "..Y.Y.....",
//    ".Y...Y....",
//    "...H..Y...",
//    "..........",
//    "..........",
//};

char TEST_BOARD[TEST_ROW_SIZE][TEST_COL_SIZE+1] = {
    "..........",
    "..&&&HY...",
    "....Y.....",
    ".Y.&&.....",
    "..........",
    "..........",
    "..........",
    "..........",
    "..........",
    "..........",
};

//char TEST_BOARD[TEST_ROW_SIZE][TEST_COL_SIZE+1] = {
//    "......&H..",
//    "..&&.&Y...",
//    "....Y.&...",
//    ".Y........",
//    "..........",
//    "..........",
//    "..........",
//    "..........",
//    "..........",
//    "..........",
//};

//char TEST_BOARD[TEST_ROW_SIZE][TEST_COL_SIZE+1] = {
//    "&mGYObd~..",
//    "YYH.......",
//    ".....m....",
//    ".O........",
//    ".....m....",
//    "..........",
//    "..........",
//    "..........",
//    "..........",
//    "..........",
//};

#endif

Board::Board() { // default constructor
    createBoard(false);
}

Board::Board(bool doNotCreateHero) {
    createBoard(true);
}

void Board::createBoard(bool doNotCreateHero) {
#ifdef TEST_BOARD_TURN_ON
    createTiles(TEST_ROW_SIZE, TEST_COL_SIZE);
    
    loadTestBoard();
#else
    createTiles(HUGE_ROW_SIZE, HUGE_COL_SIZE);
    
    if (!doNotCreateHero) {
        createHero();
    }
    else {
        cout << "createBoard(true)::sim->hero: " << sim->hero << endl;
        hero = sim->hero;
        setUnit(HERO_START_ROW, HERO_START_COL, hero);
    }
    createRandomProps();
    createRandomItems();
    createRandomUnits();
#endif
    initEtc();
}

void Board::createTiles(int rowSize, int colSize) {
    //--------------------------------------------------------------------------
    // create 2D array of Tile objects
    //--------------------------------------------------------------------------
    this->rowSize = rowSize;
    this->colSize = colSize;
    
    board = new Tile **[rowSize];
    
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
    }
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile();
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
    }
}

void Board::createMons(int maxNumMons) {
    this->maxNumMons = maxNumMons;
    if (maxNumMons == 0) {
        mons = NULL;
    }
    else {
        mons = new Monster *[maxNumMons];
    }
    numMons = 0;
}

void Board::createBosses(int maxNumBosses) {
    this->maxNumBosses = maxNumBosses;
    if (maxNumBosses == 0) {
        bosses = NULL;
    }
    else {
        bosses = new Boss *[maxNumBosses];
    }
    numBosses = 0;
}

void Board::createMerchants(int maxNumMerchants) {
    this->maxNumMerchants = maxNumMerchants;
    if (maxNumMerchants == 0) {
        merchants = NULL;
    }
    else {
        merchants = new Merchant *[maxNumMerchants];
    }
    numMerchants = 0;
}

void Board::createPortals(int maxNumPortals) {
    this->maxNumPortals = maxNumPortals;
    if (maxNumPortals == 0) {
        portals = NULL;
    }
    else {
        portals = new Portal *[maxNumPortals];
    }
    numPortals = 0;
}

#ifdef TEST_BOARD_TURN_ON
void Board::loadTestBoard() {
    //==============================================================================
    //==============================================================================
    //==============================================================================
    // Load Test Board
    //==============================================================================
    //==============================================================================
    //==============================================================================
    maxNumMons = 0;
    maxNumBosses = 0;
    maxNumMerchants = 0;
    maxNumPortals = 0;
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (TEST_BOARD[i][j] == MONSTER_SHAPE) {
                maxNumMons++;
            }
            else if (TEST_BOARD[i][j] == BOSS_SHAPE) {
                maxNumBosses++;
            }
            else if (TEST_BOARD[i][j] == MERCHANT_SHAPE) {
                maxNumMerchants++;
            }
            else if (TEST_BOARD[i][j] == PORTAL_SHAPE) {
                maxNumPortals++;
            }
        }
    }
    
    hero = new Hero();
    
    createMons(maxNumMons);
    createBosses(maxNumBosses);
    createMerchants(maxNumMerchants);
    createPortals(maxNumPortals);
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            //------------------------------------------------------------------
            // Units
            //------------------------------------------------------------------
            if (TEST_BOARD[i][j] == HERO_SHAPE) {
                setUnit(i, j, hero);
            }
            else if (TEST_BOARD[i][j] == MONSTER_SHAPE) {
                mons[numMons] = new Monster();
                setUnit(i, j, mons[numMons]);
                numMons++;
            }
            else if (TEST_BOARD[i][j] == BOSS_SHAPE) {
                bosses[numBosses] = new Boss();
                setUnit(i, j, bosses[numBosses]);
                numBosses++;
            }
            else if (TEST_BOARD[i][j] == MERCHANT_SHAPE) {
                merchants[numMerchants] = new Merchant();
                setUnit(i, j, merchants[numMerchants]);
                numMerchants++;
            }
            //------------------------------------------------------------------
            // Props
            //------------------------------------------------------------------
            else if (TEST_BOARD[i][j] == PORTAL_SHAPE) {
                portals[numPortals] = new Portal();
                setProp(i, j, portals[numPortals]);
                numPortals++;
            }
            else if (TEST_BOARD[i][j] == TREE_SHAPE) {
                setProp(i, j, new Tree());
            }
            //------------------------------------------------------------------
            // Items
            //------------------------------------------------------------------
            else if (TEST_BOARD[i][j] == HEALTH_POTION_SHAPE) {
                setItem(i, j, new HealthPotion());
            }
            else if (TEST_BOARD[i][j] == MANA_POTION_SHAPE) {
                setItem(i, j, new ManaPotion());
            }
            else if (TEST_BOARD[i][j] == MAGIC_SCROLL_SHAPE) {
                setItem(i, j, new MagicScroll());
            }
        }
    }
}
#endif

void Board::createHero() {
    hero = new Hero();
    setUnit(hero->getRow(), hero->getCol(), hero);
    
    //    pet = new Pet();
    //    setUnit(pet->getRow(), pet->getCol(), pet);
}

void Board::createRandomProps() {
    //--------------------------------------------------------------------------
    // Create random trees
    //--------------------------------------------------------------------------
    for (int i = 0; i < HUGE_MAX_NUM_TREES; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                Tree *newTree = new Tree();
                setProp(randRow, randCol, newTree);
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random portals
    //--------------------------------------------------------------------------
    createPortals(HUGE_MAX_NUM_PORTALS);
    
    for (int i = 0; i < maxNumPortals; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                portals[numPortals] = new Portal();
                setProp(randRow, randCol, portals[numPortals]);
                numPortals++;
                break;
            }
        }
    }
}

void Board::createRandomItems() {
    //--------------------------------------------------------------------------
    // Create random health potions
    //--------------------------------------------------------------------------
    for (int i = 0; i < HUGE_MAX_NUM_HEALTH_POTIONS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                setItem(randRow, randCol, new HealthPotion());
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random mana potions
    //--------------------------------------------------------------------------
    for (int i = 0; i < HUGE_MAX_NUM_MANA_POTIONS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                setItem(randRow, randCol, new ManaPotion());
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random magic scrolls
    //--------------------------------------------------------------------------
    for (int i = 0; i < HUGE_MAX_NUM_MAGIC_SCROLLS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                setItem(randRow, randCol, new MagicScroll());
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random weapon/armor
    //--------------------------------------------------------------------------
    //    for (int i = 0; i < HUGE_MAX_NUM_WEAPONS_AND_ARMORS; i++) {
    //        while (true) {
    //            int randRow = rand() % rowSize;
    //            int randCol = rand() % colSize;
    //
    //            if (board[randRow][randCol]->getProp() == NULL &&
    //                board[randRow][randCol]->getItem() == NULL &&
    //                board[randRow][randCol]->getUnit() == NULL) {
    //                if (rand() % 2 == 0) {
    //                    setItem(randRow, randCol, createRandomArmor());
    //                }
    //                else {
    //                    setItem(randRow, randCol, createRandomWeapon());
    //                }
    //                break;
    //            }
    //        }
    //    }
}

void Board::createRandomUnits() {
    //--------------------------------------------------------------------------
    // Create random monsters
    //--------------------------------------------------------------------------
    createMons(HUGE_MAX_NUM_MONS);
    
    for (int i = 0; i < maxNumMons; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                mons[numMons] = new Monster();
                setUnit(randRow, randCol, mons[numMons]);
                numMons++;
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random bosses
    //--------------------------------------------------------------------------
    createBosses(HUGE_MAX_NUM_BOSSES);
    
    for (int i = 0; i < maxNumBosses; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                bosses[numBosses] = new Boss();
                setUnit(randRow, randCol, bosses[numBosses]);
                numBosses++;
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Create random merchant
    //--------------------------------------------------------------------------
    createMerchants(HUGE_MAX_NUM_MERCHANTS);
    
    for (int i = 0; i < maxNumMerchants; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                merchants[numMerchants] = new Merchant();
                setUnit(randRow, randCol, merchants[numMerchants]);
                numMerchants++;
                break;
            }
        }
    }
}

void Board::initEtc() {
    //--------------------------------------------------------------------------
    // ETC
    //--------------------------------------------------------------------------
    dayAndNight = DEFAULT_DAY_AND_NIGHT;
    
    //--------------------------------------------------------------------------
    // Exit
    //--------------------------------------------------------------------------
    exit = NULL;
    
    //--------------------------------------------------------------------------
    // Projectile
    //--------------------------------------------------------------------------
    initProjectiles();
    
    //--------------------------------------------------------------------------
    // Shockwave
    //--------------------------------------------------------------------------
    initFx();
}

Board::~Board() { // destructor
    destroyBoard();
}

void Board::destroyBoard() {
    destroyBoard(false);
}

void Board::destroyBoard(bool doNotDeleteHero) {
    destroyEtc();
    
    if (portals != NULL) {
        delete [] portals;
        portals = NULL;
        
        maxNumPortals = 0;
        numPortals = 0;
    }
    
    if (merchants != NULL) {
        for (int i = 0; i < maxNumMerchants; i++) {
            delete merchants[i];
        }
        delete [] merchants;
        merchants = NULL;
        
        maxNumMerchants = 0;
        numMerchants = 0;
    }
    
    if (bosses != NULL) {
        for (int i = 0; i < maxNumBosses; i++) {
            delete bosses[i];
        }
        delete [] bosses;
        bosses = NULL;
        
        maxNumBosses = 0;
        numBosses = 0;
    }
    
    if (mons != NULL) {
        for (int i = 0; i < maxNumMons; i++) {
            delete mons[i];
        }
        delete [] mons;
        mons = NULL;
        
        maxNumMons = 0;
        numMons = 0;
    }
    
    if (!doNotDeleteHero && hero != NULL) {
        delete hero;
        hero = NULL;
    }
//    else {
//        setUnit(hero->getRow(), hero->getCol(), NULL);
//    }
    
    if (board != NULL) {
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                delete board[i][j];
            }
        }
        
        for (int i = 0; i < rowSize; i++) {
            delete [] board[i];
        }
        
        delete [] board;
        board = NULL;
        
        rowSize = 0;
        colSize = 0;
    }
}

void Board::destroyEtc() {
    //--------------------------------------------------------------------------
    // Shockwave
    //--------------------------------------------------------------------------
    destroyFx();
    
    //--------------------------------------------------------------------------
    // Projectile
    //--------------------------------------------------------------------------
    destroyProjectiles();
    
    //--------------------------------------------------------------------------
    // Exit
    //--------------------------------------------------------------------------
    if (exit != NULL) {
        exit = NULL;
    }
}

void Board::print() {
    // Process shockwaves
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] != NULL) {
            if (!shockwaves[i]->getWaveActivated()) {
                delete shockwaves[i];
                shockwaves[i] = NULL;
                numShockwaves--;
            }
            else {
                shockwaves[i]->print();
            }
        }
    }
    
    // Print board
    int minimapRowSize = rowSize / MINIMAP_CELL_SIZE;
    int minimapColSize = colSize / MINIMAP_CELL_SIZE;
    int minimapRow = 0; // minimapRow
    
    cout << endl;
    
    // Upper borderline
    cout << "+";
    for (int j = 0; j < VIEWPORT_COL_RANGE*2+1; j++) {
        cout << "-";
    }
    cout << "+  ";
    
    // Minimap upper borderline
    cout << "+";
    for (int j = 0; j < minimapColSize; j++) {
        cout << "-";
    }
    cout << "+" << endl;
    
    // Print inside board
    for (int i = hero->getRow()-VIEWPORT_ROW_RANGE; i <= hero->getRow()+VIEWPORT_ROW_RANGE; i++) {
        cout << "|";
        for (int j = hero->getCol()-VIEWPORT_COL_RANGE; j <= hero->getCol()+VIEWPORT_COL_RANGE; j++) {
            if (validate(i, j)) {
                if (dayAndNight == DAY ||
                    (i >= hero->getRow()-NIGHT_VISION_ROW_RANGE && i <= hero->getRow()+NIGHT_VISION_ROW_RANGE &&
                     j >= hero->getCol()-NIGHT_VISION_COL_RANGE && j <= hero->getCol()+NIGHT_VISION_COL_RANGE)
                    ) {
                    board[i][j]->print();
                }
                else { // night? out of night vision?
                    cout << "%";
                }
            }
            else { // out of bound?
                cout << "#";
            }
        }
        cout << "|";
        cout << "  ";
        
        // Print minimap
        if (minimapRow < minimapRowSize) {
            cout << "|";
            for (int minimapCol = 0; minimapCol < minimapColSize; minimapCol++) {
                // scan for the important unit/prop/item
                Unit *heroFound = NULL;
                Unit *petFound = NULL;
                Unit *bossFound = NULL;
                Unit *merchantFound = NULL;
                Prop *portalFound = NULL;
                Prop *exitFound = NULL;
                
                for (int ii = minimapRow*MINIMAP_CELL_SIZE; ii < (minimapRow+1)*MINIMAP_CELL_SIZE; ii++) {
                    for (int jj = minimapCol*MINIMAP_CELL_SIZE; jj < (minimapCol+1)*MINIMAP_CELL_SIZE; jj++) {
                        if (getUnit(ii, jj) != NULL && getUnit(ii, jj)->isHero()) {
                            heroFound = getUnit(ii, jj);
                        }
                        if (getUnit(ii, jj) != NULL && getUnit(ii, jj)->isPet()) {
                            petFound = getUnit(ii, jj);
                        }
                        if (getUnit(ii, jj) != NULL && getUnit(ii, jj)->isBoss()) {
                            bossFound = getUnit(ii, jj);
                        }
                        if (getUnit(ii, jj) != NULL && getUnit(ii, jj)->isMerchant()) {
                            merchantFound = getUnit(ii, jj);
                        }
                        if (getProp(ii, jj) != NULL && getProp(ii, jj)->isPortal()) {
                            portalFound = getProp(ii, jj);
                        }
                        if (getProp(ii, jj) != NULL && getProp(ii, jj)->isExit()) {
                            exitFound = getProp(ii, jj);
                        }
                    }
                }
                
                if (heroFound) {
                    heroFound->print();
                }
                else if (exitFound) {
                    exitFound->print();
                }
                else if (petFound) {
                    petFound->print();
                }
                else if (bossFound) {
                    bossFound->print();
                }
                else if (merchantFound) {
                    merchantFound->print();
                }
                else if (portalFound) {
                    portalFound->print();
                }
                else {
                    cout << TILE_EMPTY;
                }
            }
            cout << "|";
            minimapRow++;
        }
        
        // Print minimap lower borderline
        if (i == hero->getRow()-VIEWPORT_ROW_RANGE+minimapRowSize) {
            cout << "+";
            for (int j = 0; j < minimapColSize; j++) {
                cout << "-";
            }
            cout << "+";
        }
        cout << endl;
    }
    
    // Print lower borderline
    cout << "+";
    for (int j = 0; j < VIEWPORT_COL_RANGE*2+1; j++) {
        cout << "-";
    }
    cout << "+";
    cout << endl;
    
}

void Board::printEngaged() {
    for (int i = 0; i < numMons; i++) {
        if (mons[i]->isEngaged()) {
            mons[i]->printStat();
            cout << endl;
        }
    }
    for (int i = 0; i < numBosses; i++) {
        if (bosses[i]->isEngaged()) {
            bosses[i]->printStat();
            cout << endl;
        }
    }
}

bool Board::validate(int row, int col) {
    return row >= 0 && row < rowSize && col >= 0 && col < colSize;
}

int Board::getRowSize() const {
    return rowSize;
}

int Board::getColSize() const {
    return colSize;
}

Hero *Board::getHero() {
    return hero;
}

void Board:: setHeroNULL() {
    hero = NULL;
}

Unit *Board::getUnit (int row, int col) {
    if (!validate(row, col)) { // validate
        return NULL;
    }
    
    return board[row][col]->getUnit();
}


void Board::setUnit(int row, int col, Unit *unit) {
    if (!validate(row, col)) { // validate
        return;
    }
    
    board[row][col]->setUnit(unit);
    
    if (unit != NULL) {
        unit->setRow(row);
        unit->setCol(col);
    }
}

Item *Board::getItem(int row, int col)  {
    if (!validate(row, col)) { // validate
        return NULL;
    }
    
    return board[row][col]->getItem();
}

void Board::setItem(int row, int col, Item *item)  {
    if (!validate(row, col)) { // validate
        return;
    }
    
    board[row][col]->setItem(item);
}

Prop *Board::getProp(int row, int col)  {
    if (!validate(row, col)) { // validate
        return NULL;
    }
    
    return board[row][col]->getProp();
}

void Board::setProp(int row, int col, Prop *prop)  {
    if (!validate(row, col)) { // validate
        return;
    }
    
    board[row][col]->setProp(prop);

	if (prop != NULL) {
		prop->setRow(row);
		prop->setCol(col);
	}
}

void Board::moveMons() {
    for (int i = 0; i < maxNumMons; i++) {
        if (mons[i]->isDead() && mons[i]->getRow() != -1) {
            setUnit(mons[i]->getRow(), mons[i]->getCol(), NULL);
            mons[i]->setRow(-1);
            mons[i]->setCol(-1);
            
            int randMonRespawnInterval = (rand() % (MON_RESPAWN_INTERVAL_MAX - MON_RESPAWN_INTERVAL_MIN + 1)) + MON_RESPAWN_INTERVAL_MIN;
            sim->eventQueue->enqueue(EventWrapper(new MonRespawnEvent(sim->time+randMonRespawnInterval, mons[i])));
        }
        else {
            int randDir = rand() % NUM_DIRS;
            mons[i]->move(randDir);
        }
    }
}

void Board::moveBosses() {
    for (int i = 0; i < maxNumBosses; i++) {
        if (bosses[i]->isDead() && bosses[i]->getRow() != -1) {
            setUnit(bosses[i]->getRow(), bosses[i]->getCol(), NULL);
            numBosses--;
            bosses[i]->setRow(-1);
            bosses[i]->setCol(-1);
            
            if (exit == NULL) {
                createExit();
            }
        }
        else {
            int randDir = rand() % NUM_DIRS;
            bosses[i]->move(randDir);
        }
    }
}

//void Board::movePet() {
//    if (pet != NULL) {
//        if (pet->isDead() && pet->getRow() != -1) {
//            setUnit(pet->getRow(), pet->getCol(), NULL);
//            pet->setRow(-1);
//            pet->setCol(-1);
//        }
//        else {
//            int randDir = rand() % NUM_DIRS;
//            pet->move(randDir);
//        }
//    }
//}


//--------------------------------------------------------------------------
// Projectiles
//--------------------------------------------------------------------------

void Board::initProjectiles() {
    maxNumProjectiles = MAX_NUM_PROJECTILES;
    projectiles = new Projectile *[maxNumProjectiles];
    numProjectiles = 0;
    
    for (int i = 0; i < maxNumProjectiles; i++) {
        projectiles[i] = NULL;
    }
    
    // Init shurikens
    maxNumShurikens = MAX_NUM_SHURIKENS;
    shurikens = new Shuriken *[maxNumShurikens];
    numShurikens = 0;
    
    for (int i = 0; i < maxNumShurikens; i++) {
        shurikens[i] = new Shuriken();
    }
    
    // Init fireballs
    maxNumFireballs = MAX_NUM_FIREBALLS;
    fireballs = new Fireball *[maxNumFireballs];
    numFireballs = 0;
    
    for (int i = 0; i < maxNumFireballs; i++) {
        fireballs[i] = new Fireball();
    }
}

void Board::destroyProjectiles() {
    // destroy fireballs
    if (fireballs != NULL) {
        for (int i = 0; i < maxNumFireballs; i++) {
            delete fireballs[i];
        }
        delete [] fireballs;
        fireballs = NULL;
        maxNumFireballs = 0;
        numFireballs = 0;
    }
    
    // destroy shurikens
    if (shurikens != NULL) {
        for (int i = 0; i < maxNumShurikens; i++) {
            delete shurikens[i];
        }
        delete [] shurikens;
        shurikens = NULL;
        maxNumShurikens = 0;
        numShurikens = 0;
    }
    
    if (projectiles != NULL) {
        delete [] projectiles;
        projectiles = NULL;
        maxNumProjectiles = 0;
        numProjectiles = 0;
    }
}

Projectile *Board::getProjectile(int row, int col) {
    if (!validate(row, col)) { // validate
        return NULL;
    }

    return board[row][col]->getProjectile();
}

void Board::setProjectile(int row, int col, Projectile *projectile) {
    if (!validate(row, col)) { // validate
        return;
    }
    
    board[row][col]->setProjectile(projectile);
   
    if (projectile != NULL) {
        projectile->setRow(row);
        projectile->setCol(col);
    }
}

void Board::shootProjectiles() {
    // Check num projectiles
    if (numShurikens > maxNumShurikens || numFireballs > maxNumFireballs) {
        sim->systemMessage = "error: Can't shoot more projectiles!";
        return;
    }
    
    // Check hero mana
    if (sim->hero->getMp() < PROJECTILE_SHURIKEN_MP && sim->hero->getProjectileIndex() == PROJECTILE_SHURIKEN) {
        sim->systemMessage = "error: Not enough MP!";
        return;
    }
    else if (sim->hero->getMp() < PROJECTILE_FIREBALL_MP && sim->hero->getProjectileIndex() == PROJECTILE_FIREBALL) {
        sim->systemMessage = "error: Not enough MP!";
        return;
    }

    cout << "Board::shootProjectiles() activated!" << endl;
    cout << "numProjectiles is: " << numProjectiles << endl;
    cout << "maxNumProjectiles is: " << maxNumProjectiles << endl;

    for (int i = 0; i < maxNumProjectiles; i++) {
        if (projectiles[i] == NULL) {
            if (sim->hero->getProjectileIndex() == PROJECTILE_SHURIKEN) {
                for (int j = 0; j < maxNumShurikens; j++) {
                    if (!shurikens[j]->isActivated()) {
                        setProjectile(sim->hero->getRow(), sim->hero->getCol(), shurikens[j]);
                        shurikens[j]->setDir(sim->hero->getDir());
                        shurikens[j]->activate();
                        projectiles[i] = shurikens[j];
                        sim->hero->decMp(projectiles[i]->getMp());
                        numProjectiles++;
                        break;
                    }
                }
                cout << "error: Can't shoot more shurikens!";
            }
            else if (sim->hero->getProjectileIndex() == PROJECTILE_FIREBALL) {
                for (int j = 0; j < maxNumFireballs; j++) {
                    if (!fireballs[j]->isActivated()) {
                        setProjectile(sim->hero->getRow(), sim->hero->getCol(), fireballs[j]);
                        fireballs[j]->setDir(sim->hero->getDir());
                        fireballs[j]->activate();
                        projectiles[i] = fireballs[j];
                        sim->hero->decMp(projectiles[i]->getMp());
                        numProjectiles++;
                        break;
                    }
                }
                cout << "error: Can't shoot more fireballs!";
            }
            break;
        }
    }
}

void Board::moveProjectiles() {
    for (int i = 0; i < maxNumProjectiles; i++) {
        if (projectiles[i] != NULL) {
            if (projectiles[i]->isActivated()) {
                projectiles[i]->move();
            }
            else if (!projectiles[i]->isActivated()) {
                projectiles[i] = NULL;
                numProjectiles--;
            }
        }
    }
}

//--------------------------------------------------------------------------
// Portal
//--------------------------------------------------------------------------
int Board::getMaxNumPortals() {
    return maxNumPortals;
}

Portal *Board::getPortalAt(int index) {
    if (index >= maxNumPortals) {
        return NULL;
    }
    
    return portals[index];
}

//--------------------------------------------------------------------------
// Exit
//--------------------------------------------------------------------------
void Board::createExit() {
    exit = new Exit();
    
    while (true) {
        int randRow = rand() % rowSize;
        int randCol = rand() % colSize;
        
        if (board[randRow][randCol]->getProp() == NULL &&
            board[randRow][randCol]->getItem() == NULL &&
            board[randRow][randCol]->getUnit() == NULL) {
            setProp(randRow, randCol, exit);
            break;
        }
    }
}


//--------------------------------------------------------------------------
// A*
//--------------------------------------------------------------------------
Tile *Board::getTileAt(int curRow, int curCol) {
	if (!validate(curRow, curCol)) {
		return NULL;
	}
	return board[curRow][curCol];
}

void Board::astarReset() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j]->astarReset();
        }
    }
}

//--------------------------------------------------------------------------
// Event
//--------------------------------------------------------------------------
void Board::toggleDayAndNight() {
    dayAndNight = !dayAndNight;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// for shockwave
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Board::initFx() {
//    cout << "Board::initFx()" << endl;
    maxNumShockwaves = SHOCKWAVES_NUM_MAX;
    shockwaves = new Shockwave *[maxNumShockwaves];
    numShockwaves = 0;
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        shockwaves[i] = NULL;
    }
}

void Board::destroyFx() {
    if (shockwaves != NULL) {
        for (int i = 0; i < maxNumShockwaves; i++) {
            if (shockwaves[i] != NULL) {
                delete shockwaves[i];
            }
        }
        
        delete [] shockwaves;
        shockwaves = NULL;
        
        maxNumShockwaves = 0;
        numShockwaves = 0;
    }
}

void Board::clearFx(int row, int col) {
    board[row][col]->clearFx();
}

void Board::setFx(int row, int col, char fx) {
    board[row][col]->setFx(fx);
}

void Board::startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                      int row, int col, int range, int frameInterval, char fxShape, int skillNumber) {
    
    if (numShockwaves >= maxNumShockwaves) {
        cout << "error: can't start new shockwave!";
        return;
    }
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] == NULL) {
            shockwaves[i] = new Shockwave(waveUnit, waveItem, waveProp,
                                          row, col, range, frameInterval, fxShape);
            shockwaves[i]->start();
            shockwaves[i]->setSkillNumber(skillNumber);
            numShockwaves++;
            break;
        }
    }
}

//--------------------------------------------------------------------------
// Save/load
//--------------------------------------------------------------------------
void Board::save(ostream &out) {
    out << "#---------------------------------------- class Board" << endl;
    out << "#======================================== board[][]" << endl;
    out << "# rowSize" << endl;
    out << rowSize << endl;
    out << "# colSize" << endl;
    out << colSize << endl;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            out << "#======================================== board[" << i << "]" << "[" << j << "]" << endl;
            board[i][j]->save(out);
        }
    }
    out << "#======================================== mons[]" << endl;
    out << "# maxNumMons" << endl;
    out << maxNumMons << endl;
    out << "# numMons" << endl;
    out << numMons << endl;
    for (int i = 0; i < maxNumMons; i++) {
        out << "#======================================== mons[" << i << "]" << endl;
        mons[i]->save(out);
    }
    out << "#======================================== bosses[]" << endl;
    out << "# maxNumBosses" << endl;
    out << maxNumBosses << endl;
    out << "# numBosses" << endl;
    out << numBosses << endl;
    for (int i = 0; i < maxNumBosses; i++) {
        out << "#======================================== bosses[" << i << "]" << endl;
        bosses[i]->save(out);
    }
    out << "#======================================== merchants[]" << endl;
    out << "# maxNumMerchants" << endl;
    out << maxNumMerchants << endl;
    out << "# numMerchants" << endl;
    out << numMerchants << endl;
    for (int i = 0; i < maxNumMerchants; i++) {
        out << "#======================================== merchants[" << i << "]" << endl;
        merchants[i]->save(out);
    }
    out << "#======================================== portals[]" << endl;
    out << "# maxNumPortals" << endl;
    out << maxNumPortals << endl;
    out << "# numPortals" << endl;
    out << numPortals << endl;
    for (int i = 0; i < maxNumPortals; i++) {
        out << "#---------------------------------------- portals[" << i << "]" << endl;
        portals[i]->save(out);
    }
    out << "#======================================== hero" << endl;
    hero->save(out);
    out << "#======================================== exit" << endl;
    if (exit != NULL) {
        out << TOMBSTONE_NOT_EMPTY << endl;
        exit->save(out);
    }
    else {
        out << TOMBSTONE_EMPTY << endl;
    }
    out << "#======================================== dayAndNight" << endl;
    out << dayAndNight << endl;
}

void Board::load(istream &in) {
    destroyBoard();
    
    char buf[250];
//    out << "#---------------------------------------- class Board" << endl;
    in.getline(buf, 250);
//    out << "#======================================== board[][]" << endl;
    in.getline(buf, 250);
//    out << "# rowSize" << endl;
    in.getline(buf, 250);
//    out << rowSize << endl;
    in >> rowSize >> buf[0];
//    out << "# colSize" << endl;
    in.getline(buf, 250);
//    out << colSize << endl;
    in >> colSize >> buf[0];
    
    createTiles(rowSize, colSize);
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
//            out << "#---------------------------------------- board[" << i << "]" << "[" << j << "]" << endl;
            in.getline(buf, 250);
//            board[i][j] = new Tile();
            board[i][j]->load(in);
        }
    }
//    out << "#======================================== mons[]" << endl;
    in.getline(buf, 250);
//    out << "# maxNumMons" << endl;
    in.getline(buf, 250);
//    out << maxNumMons << endl;
    in >> maxNumMons >> buf[0];
    
    createMons(maxNumMons);
    
//    out << "# numMons" << endl;
    in.getline(buf, 250);
//    out << numMons << endl;
    in >> numMons >> buf[0];
    for (int i = 0; i < maxNumMons; i++) {
//        out << "#---------------------------------------- mons[" << i << "]" << endl;
        in.getline(buf, 250);
        mons[i] = new Monster();
        mons[i]->load(in);
        setUnit(mons[i]->getRow(), mons[i]->getCol(), mons[i]);
    }
    
//    out << "#======================================== bosses[]" << endl;
    in.getline(buf, 250);
//    out << "# maxNumBosses" << endl;
    in.getline(buf, 250);
//    out << maxNumBosses << endl;
    in >> maxNumBosses >> buf[0];
    
    createBosses(maxNumBosses);
    
//    out << "# numBosses" << endl;
    in.getline(buf, 250);
//    out << numBosses << endl;
    in >> numBosses >> buf[0];
    for (int i = 0; i < maxNumBosses; i++) {
//        out << "#---------------------------------------- bosses[" << i << "]" << endl;
        in.getline(buf, 250);
        bosses[i] = new Boss();
        bosses[i]->load(in);
        setUnit(bosses[i]->getRow(), bosses[i]->getCol(), bosses[i]);
    }
    
//    out << "#======================================== merchants[]" << endl;
    in.getline(buf, 250);
//    out << "# maxNumMerchants" << endl;
    in.getline(buf, 250);
//    out << maxNumMerchants << endl;
    in >> maxNumMerchants >> buf[0];

    createMerchants(maxNumMerchants);

//    out << "# numMerchants" << endl;
    in.getline(buf, 250);
//    out << numMerchants << endl;
    in >> numMerchants >> buf[0];
    for (int i = 0; i < maxNumMerchants; i++) {
//        out << "#---------------------------------------- merchants[" << i << "]" << endl;
        in.getline(buf, 250);
        merchants[i] = new Merchant();
        merchants[i]->load(in);
        setUnit(merchants[i]->getRow(), merchants[i]->getCol(), merchants[i]);
    }
    
    //    out << "#======================================== portals[]" << endl;
    in.getline(buf, 250);
    //    out << "# maxNumPortals" << endl;
    in.getline(buf, 250);
    //    out << maxNumPortals << endl;
    in >> maxNumPortals >> buf[0];
    
    createPortals(maxNumPortals);
    
    //    out << "# numPortals" << endl;
    in.getline(buf, 250);
    //    out << numPortals << endl;
    in >> numPortals >> buf[0];
    for (int i = 0; i < maxNumPortals; i++) {
        //        out << "#---------------------------------------- portals[" << i << "]" << endl;
        in.getline(buf, 250);
        portals[i] = new Portal();
        portals[i]->load(in);
        setProp(portals[i]->getRow(), portals[i]->getCol(), portals[i]);
    }
    
//    out << "#======================================== hero" << endl;
    in.getline(buf, 250);
//  hero->save(out);
    hero = new Hero();
    hero->load(in);
    sim->hero = hero;
//    out << "#======================================== exit" << endl;
    in.getline(buf, 250);
//    if (exit != NULL) {
//        out << TOMBSTONE_NOT_EMPTY << endl;
//        exit->save(out);
//    }
//    else {
//        out << TOMBSTONE_EMPTY << endl;
//    }
    in.getline(buf, 250);
    if (strcmp(buf, TOMBSTONE_NOT_EMPTY) == 0) {
        exit = new Exit();
        exit->load(in);
        setProp(exit->getRow(), exit->getCol(), exit);
    }
    else {
        exit = NULL;
    }
    
//    out << "#======================================== dayAndNight" << endl;
    in.getline(buf, 250);
//    out << dayAndNight << endl;
    in >> dayAndNight >> buf[0];
    astarReset();
    
    // 맨 위의 destroyBoard()에서 모두 지우므로..
    initEtc();
}
