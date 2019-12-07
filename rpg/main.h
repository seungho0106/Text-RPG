#ifndef MAIN_H
#define MAIN_H

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Flags
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//#define TEST_BOARD_TURN_ON 1
#define STATISTICS_ON 1
#define LOG_EVENT_ON 1

#ifdef TEST_BOARD_TURN_ON
#define TEST_BOARD_01_ON
#define TEST_BOARD_01_ROW_SIZE 10
#define TEST_BOARD_01_COL_SIZE 10
#define TEST_ROW_SIZE TEST_BOARD_01_ROW_SIZE
#define TEST_COL_SIZE TEST_BOARD_01_COL_SIZE
#endif

#define BOSS_IQ_80 0
//#define BOSS_IQ_100 1
#define BOSS_IQ_120 2
//#define BOSS_IQ_150 3

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Huge Map
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifdef TEST_BOARD_TURN_ON
    #define ROW_SIZE TEST_ROW_SIZE
    #define COL_SIZE TEST_COL_SIZE
    #define HUGE_ROW_SIZE (ROW_SIZE*1)
    #define HUGE_COL_SIZE (COL_SIZE*1)
#else
    #define ROW_SIZE 10
    #define COL_SIZE 40
    #define HUGE_ROW_SIZE (ROW_SIZE*5)
    #define HUGE_COL_SIZE (COL_SIZE*5)
#endif

#define MINIMAP_CELL_SIZE 10
#define MONSTER_STAT_WINDOW_CELL_SIZE 10

#define HUGE_MAP_RATIO ((double)((HUGE_ROW_SIZE*HUGE_COL_SIZE)/(double)(ROW_SIZE*COL_SIZE)))

#define MAX_NUM_MONS 8
#define MAX_NUM_BOSSES 0.2
#define MAX_NUM_MERCHANTS 0.15
#define MAX_NUM_TREES 50
#define MAX_NUM_PORTALS 0.3
#define MAX_NUM_HEALTH_POTIONS 2
#define MAX_NUM_MANA_POTIONS 2
#define MAX_NUM_MAGIC_SCROLLS 1
#define MAX_NUM_WEAPONS_AND_ARMORS 20

#define HUGE_MAX_NUM_MONS ((int)(MAX_NUM_MONS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_BOSSES ((int)(MAX_NUM_BOSSES*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_MERCHANTS ((int)(MAX_NUM_MERCHANTS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_TREES ((int)(MAX_NUM_TREES*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_PORTALS ((int)(MAX_NUM_PORTALS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_HEALTH_POTIONS ((int)(MAX_NUM_HEALTH_POTIONS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_MANA_POTIONS ((int)(MAX_NUM_MANA_POTIONS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_MAGIC_SCROLLS ((int)(MAX_NUM_MAGIC_SCROLLS*HUGE_MAP_RATIO))
#define HUGE_MAX_NUM_WEAPONS_AND_ARMORS ((int)(MAX_NUM_WEAPONS_AND_ARMORS*HUGE_MAP_RATIO))

#define VIEWPORT_ROW_RANGE 7
#define VIEWPORT_COL_RANGE 20

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// General
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define TILE_EMPTY '.'

#define NUM_DIRS 4

#define DIR_NONE -1

#define DIR_N 0
#define DIR_E 1
#define DIR_S 2
#define DIR_W 3

#define GAME_LOOP_DELAY_IN_SEC 0.1f
#define GAME_LOOP_DELAY_IN_MILLISEC (GAME_LOOP_DELAY_IN_SEC*1000)
#define GAME_LOOP_DELAY_IN_MICROSEC (GAME_LOOP_DELAY_IN_SEC*1000000)
#define FPS ((int)(1.0f/GAME_LOOP_DELAY_IN_SEC))

#define SYSTEM_MESSAGE_INTERVAL_IN_SEC 3.0
#define SYSTEM_MESSAGE_INTERVAL ((int)(FPS*SYSTEM_MESSAGE_INTERVAL_IN_SEC))

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Unit
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Hero
//------------------------------------------------------------------------------
#define HERO_SHAPE 'H'
#define HERO_START_ROW (HUGE_ROW_SIZE/2)
#define HERO_START_COL (HUGE_COL_SIZE/2)
#define HERO_MAX_HP 100
#define HERO_MAX_MP 100
#define HERO_MAX_LEVEL 5
#define HERO_DEFAULT_ATK 100
#define HERO_DEFAULT_DEF 100
#define HERO_DEFAULT_GOLD 100000
#define HERO_DEFAULT_EXP 0
#define HERO_DEFAULT_EXP_TO_LVL_UP 100
#define HERO_DEFAULT_LVL 1

//------------------------------------------------------------------------------
// Pet
//------------------------------------------------------------------------------
#define PET_SHAPE 'q'
#define PET_START_ROW HERO_START_ROW
#define PET_START_COL (HERO_START_COL+1)
#define PET_DEFAULT_RANGE 5
#define PET_MAX_HP 50
#define PET_MAX_MP 0
#define PET_DEFAULT_ATK 10
#define PET_DEFAULT_DEF 10
#define PET_DEFAULT_GOLD 0
#define PET_DEFAULT_EXP 0
#define PET_DEFAULT_LVL 1

//------------------------------------------------------------------------------
// Monster
//------------------------------------------------------------------------------
#define MONSTER_SHAPE 'm'
#define MONSTER_DEFAULT_RANGE 2
#define MONSTER_MAX_HP 30
#define MONSTER_MAX_MP 0
#define MONSTER_DEFAULT_ATK 10
#define MONSTER_DEFAULT_DEF 10
#define MONSTER_DEFAULT_GOLD 1000
#define MONSTER_DEFAULT_EXP 25
#define MONSTER_DEFAULT_LVL 1

//------------------------------------------------------------------------------
// Boss
//------------------------------------------------------------------------------
#define BOSS_SHAPE '&'
#define BOSS_MAX_HP 500
#define BOSS_MAX_MP 0
#define BOSS_DEFAULT_RANGE 10
#define BOSS_DEFAULT_ATK 30
#define BOSS_DEFAULT_DEF 30
#define BOSS_DEFAULT_GOLD 100000
#define BOSS_DEFAULT_EXP 100000
#define BOSS_DEFAULT_LVL 1

//------------------------------------------------------------------------------
// Merchant
//------------------------------------------------------------------------------
#define MERCHANT_ITEMS_TO_SELL_MAX_NUM_ITEMS 10
//#define MERCHANT_ITEMS_TO_BUY_MAX_NUM_ITEMS 10

#define MERCHANT_SHAPE 'G'
#define MERCHANT_DEFAULT_GOLD 1000000
#define MERCHANT_DEFAULT_EXP 0
#define MERCHANT_DEFAULT_LVL 1

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Prop
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Tree
//------------------------------------------------------------------------------
#define TREE_SHAPE 'Y'

//------------------------------------------------------------------------------
// Portal
//------------------------------------------------------------------------------
#define PORTAL_SHAPE 'O'

//------------------------------------------------------------------------------
// Exit
//------------------------------------------------------------------------------
#define EXIT_SHAPE 'E'

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Consumable Item
//------------------------------------------------------------------------------
#define CONSUMABLE_ITEM_RANDOM_NUM_MAX 3

//------------------------------------------------------------------------------
// Health Potion
//------------------------------------------------------------------------------
#define HEALTH_POTION_SHAPE 'b'
#define HEALTH_POTION_NAME "Health Potion"
#define HEALTH_POTION_PRICE 1000
#define HEALTH_POTION_HP 15

//------------------------------------------------------------------------------
// Mana Potion
//------------------------------------------------------------------------------
#define MANA_POTION_SHAPE 'd'
#define MANA_POTION_NAME "Mana Potion"
#define MANA_POTION_PRICE 2000
#define MANA_POTION_MP 15

//------------------------------------------------------------------------------
// Magic Scroll
//------------------------------------------------------------------------------
#define MAGIC_SCROLL_SHAPE '~'
#define MAGIC_SCROLL_NAME "Magic Scroll"
#define MAGIC_SCROLL_PRICE 5000

//------------------------------------------------------------------------------
// Weapon
//------------------------------------------------------------------------------
#define RANDOM_EQUIPPABLE_ITEM_MAX_ITER 10000

#define ITEM_ID_WEAPON "Weapon"

#define DEFAULT_WEAPON_SHAPE 'W'
#define DEFAULT_WEAPON_NAME "Weapon"
#define DEFAULT_WEAPON_PRICE 0
#define DEFAULT_WEAPON_DURABILITY 10
#define DEFAULT_WEAPON_ATK 10
#define DEFAULT_WEAPON_NUM_HANDS 1

//------------------------------------------------------------------------------
// Armor
//------------------------------------------------------------------------------
#define MAX_NUM_RANDOM_ARMORS 18

#define ITEM_ID_ARMOR "Armor"

#define DEFAULT_ARMOR_SHAPE 'A'
#define DEFAULT_ARMOR_NAME "Armor"
#define DEFAULT_ARMOR_PRICE 0
#define DEFAULT_ARMOR_DURABILITY 10
#define DEFAULT_ARMOR_DEF 10

#define ARMOR_BODYPART_ID_NONE -1
#define ARMOR_BODYPART_ID_HEAD 0
#define ARMOR_BODYPART_ID_CHEST 1
#define ARMOR_BODYPART_ID_GLOVES 2
#define ARMOR_BODYPART_ID_BACK 3
#define ARMOR_BODYPART_ID_LEGS 4
#define ARMOR_BODYPART_ID_FEET 5
#define WEAPON_BODYPART_ID_LEFT_HAND 6
#define WEAPON_BODYPART_ID_RIGHT_HAND 7

#define ARMOR_HEAD_SHAPE 'A'
#define ARMOR_CHEST_SHAPE 'W'
#define ARMOR_GLOVES_SHAPE 'U'
#define ARMOR_BACK_SHAPE 'Q'
#define ARMOR_LEGS_SHAPE 'L'
#define ARMOR_FEET_SHAPE 'F'
#define WEAPON_ONE_HAND_SHAPE '!'
#define WEAPON_TWO_HAND_SHAPE '?'

#define WEAPON_ONE_HAND 1
#define WEAPON_TWO_HAND 2

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Projectiles
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define MAX_NUM_PROJECTILES (MAX_NUM_SHURIKENS+MAX_NUM_FIREBALLS)
#define MAX_NUM_SHURIKENS 4
#define MAX_NUM_FIREBALLS 1

#define PROJECTILE_NUM_TYPES (PROJECTILE_FIREBALL+1)
#define PROJECTILE_SHURIKEN 0
#define PROJECTILE_FIREBALL (PROJECTILE_SHURIKEN+1)

#define PROJECTILE_SHURIKEN_SHAPE '+'
#define PROJECTILE_SHURIKEN_ATK 5
#define PROJECTILE_SHURIKEN_MP 5
#define PROJECTILE_SHURIKEN_RANGE 5

#define PROJECTILE_FIREBALL_SHAPE '@'
#define PROJECTILE_FIREBALL_ATK 25
#define PROJECTILE_FIREBALL_MP 40
#define PROJECTILE_FIREBALL_RANGE 10

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Inventory
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define INVENTORY_NUM_ITEMS_MAX 5

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Shockwave
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define SHOCKWAVES_NUM_MAX 100

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Magic
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define MAGIC_FROZEN 0
#define MAGIC_FROZEN_SHAPE '*'

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// A*
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define INF 1000000.0

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Event
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DayAndNightEvent
//------------------------------------------------------------------------------
#define DAY true
#define NIGHT false

#define DEFAULT_DAY_AND_NIGHT DAY
//#define DEFAULT_DAY_AND_NIGHT NIGHT

#define DAY_AND_NIGHT_INTERVAL_IN_SEC 30.0
#define DAY_AND_NIGHT_INTERVAL ((int)(FPS*DAY_AND_NIGHT_INTERVAL_IN_SEC))

#define NIGHT_VISION_ROW_RANGE 3
#define NIGHT_VISION_COL_RANGE 6

//------------------------------------------------------------------------------
// MonRespawnEvent
//------------------------------------------------------------------------------
#define MON_RESPAWN_INTERVAL_MIN_IN_SEC 5.0
#define MON_RESPAWN_INTERVAL_MAX_IN_SEC 10.0
#define MON_RESPAWN_INTERVAL_MIN ((int)(FPS*MON_RESPAWN_INTERVAL_MIN_IN_SEC))
#define MON_RESPAWN_INTERVAL_MAX ((int)(FPS*MON_RESPAWN_INTERVAL_MAX_IN_SEC))

//------------------------------------------------------------------------------
// NewMapSpawnEvent
//------------------------------------------------------------------------------
#define NEW_MAP_SPAWN_INTERVAL_IN_SEC 0.1
#define NEW_MAP_SPAWN_INTERVAL ((int)(FPS*NEW_MAP_SPAWN_INTERVAL_IN_SEC))

//------------------------------------------------------------------------------
// Statistics related
//------------------------------------------------------------------------------
#define STAT_LOG_EVENT_INTERVAL_IN_SEC 3.0
#define STAT_LOG_EVENT_INTERVAL ((int)(FPS*STAT_LOG_EVENT_INTERVAL_IN_SEC))

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Save & Load
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define TOMBSTONE_EMPTY "EMPTY"
#define TOMBSTONE_NOT_EMPTY "NOT EMPTY"

#endif
