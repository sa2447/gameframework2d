#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gf2d_sprite.h"
#include "gfc_shape.h"
#include "world.h"

typedef enum
{
	T_Player,
	T_Enemy,
	T_Interactable,
	T_Pickup

}Teams;

typedef enum
{
	T_Item,
	T_Projectile,
	T_Checkpoint,
	T_Main,
	T_Ant,
	T_Boss
}Extra;

typedef struct Entity_S
{
	Uint8	_inuse;
	Sprite	*sprite;
	float frame;
	GFC_Vector2D position;
	GFC_Vector2D velocity;
	void (*think)(struct Entity_S *self);
	void (*update)(struct Entity_S *self);
	void (*free)(struct Entity_S *self);
	void* data;
	int* speed;
	int* health;
	int* shield;
	int* currency;
	GFC_Vector2D going;
	int* can_move;
	int* alive;
	int* distance_to_die;
	int* damage;
	int* total;
	int* lives;
	int* sshots;

	Teams team;
	Extra type;
	GFC_Rect hitbox;
	GFC_Rect target_hitbox;



	float (*currentx)(struct Entity_S* self);
	float (*currenty)(struct Entity_S* self);

	Level *current;



}Entity;



void entity_system_initialize(Uint32 max);

GFC_Vector2D get_position(Entity target);

void entity_clear_all(Entity *ignore);

Entity *entity_new();

void entity_free(Entity *self);

void entity_system_think();

void entity_system_update();

void entity_system_draw();

#endif // !__ENTITY_H__

