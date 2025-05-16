#ifndef __SPAWNING_H__
#define __SPAWNING_H__

#include "simple_logger.h"
#include "entity.h"



Entity* enemy_new(const char* filename, int key, int x, int y, GFC_Rect other);

Entity* new_skirmisher(int spawnx, int spawny,int health, int shield, int shot, int currency);
Entity* new_assassin(int spawnx, int spawny, int health, int shield, int shot, int currency);
Entity* new_adv_skirmisher(int spawnx, int spawny, int health, int shield, int shot, int currency);
Entity* new_ram(int spawnx, int spawny, int health, int shield, int shot, int currency, GFC_Rect other);
Entity* new_shield_bot(int spawnx, int spawny, int health, int shield, int shot, int currency);
Entity* new_boss(int spawnx, int spawny, int health, int shield, int shot, int currency);


#endif
