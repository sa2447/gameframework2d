#include "simple_logger.h"

#include "entity.h"
#include "skirmisher.h"


void skirmisher_think(Entity* self, Entity target);
void skirmisher_update(Entity* self, Entity target);
void skirmisher_free(Entity* self);

Entity* new_skirmisher(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity* self;
	Entity enemy = target;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a skirmisher");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/skirmisher.png",
		32,
		32,
		1,
		0);
	self->frame = 0;
	self->position = gfc_vector2d(x, y);

	self->health = health;
	self->shield = shield;
	self->currency = currency;

	self->going.x = 64;

	self->think = skirmisher_think;
	self->update = skirmisher_update;
	self->free = skirmisher_free;


	skirmisher_update(self, enemy);

	return self;
}
void skirmisher_think(Entity* self, Entity target)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx, my;
	int bounce_check;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);

	if (!self)return;

	if (self->position.x != self->going.x)
	{
		self->position.x -= 1;
	}

	if (self->position.x == self->going.x)
	{
		monster_free(self);
	}



	int timer = self->position.x;
	int firingx = self->position.x;
	int firingy = self->position.y;
	int team = 1;
	int damage = 5;
	int distance = 10;
	int b_speed = 2;

	if (timer % 100 == 0)
	{
		projectile_new(firingx, firingy, team, damage, distance, b_speed);
		

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);


}


void skirmisher_update(Entity* self, Entity target)
{

	if (!self)return;



}
void skirmisher_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}