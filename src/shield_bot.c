#include "simple_logger.h"

#include "entity.h"
#include "shield_bot.h"


void shield_bot_think(Entity* self, Entity target);
void shield_bot_update(Entity* self, Entity target);
void shield_bot_free(Entity* self);

Entity* new_shield_bot(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity* self;
	Entity enemy = target;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a shield_bot");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/shield_drone.png",
		32,
		32,
		1,
		0);
	self->frame = 0;
	self->position = gfc_vector2d(x, y);

	self->think = shield_bot_think;
	self->update = shield_bot_update;
	self->free = shield_bot_free;


	shield_bot_update(self, enemy);


	self->going.x = 64;


	return self;
}
void shield_bot_think(Entity* self, Entity target)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx, my;
	int bounce_check;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);
	//Entity enemy = target;




	if (!self)return;



	//Movement 

	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);


	if (self->position.x != self->going.x)
	{
		self->position.x -= 1;
	}

	if (self->position.x == self->going.x)
	{
		shield_bot_free(self);
	}
}


void shield_bot_update(Entity* self, Entity target)
{
	if (!self)return;

}
void shield_bot_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}