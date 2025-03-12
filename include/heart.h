#ifndef __HEART_H__
#define __HEART_H__

#include "entity.h"


Entity* heart_new(int startx, int starty, int team, int total, int speed);

void heart_loss(Entity* self, int loss_amount);

#endif