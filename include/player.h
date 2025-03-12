#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gfc_input.h"
#include "entity.h"


Entity *player_new(int health, int shield, int speed, int currency);

typedef struct
{
	Sprite* image; //tile sheet
	Uint32 imageHeight; //tiles high
	Uint32 imageWidth; //tiles wide

}Hud;



#endif
