#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gfc_input.h"
#include "entity.h"
#include "world.h"


Entity *player_new(int health, int shield, int speed, int currency,int startx, int starty, int lives, Level *level, Entity *hearts);
float player_get_x(Entity* self);
float player_get_y(Entity* self);

GFC_Rect get_player_hitbox(Entity* player);

Entity* player_load(const char* filename, int startx, int starty, int level, Level *current, Entity *heart);
void player_advance(Entity* player, Entity *heart);
int get_current_level(const char* filename);

typedef struct
{
	Sprite* image; //tile sheet
	Uint32 imageHeight; //tiles high
	Uint32 imageWidth; //tiles wide

}Hud;



#endif
