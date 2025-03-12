#include "simple_logger.h"

#include "entity.h"
#include "adv_skirmisher.h"


void adv_skirmisher_think(Entity* self, Entity target);
void adv_skirmisher_update(Entity* self, Entity target);
void adv_skirmisher_free(Entity* self);

Entity* new_adv_skirmisher(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity* self;
	Entity enemy = target;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a adv_skirmisher");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/adv_skirmisher.png",
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

	self->think = adv_skirmisher_think;
	self->update = adv_skirmisher_update;
	self->free = adv_skirmisher_free;


	adv_skirmisher_update(self, enemy);

	return self;
}
void adv_skirmisher_think(Entity* self, Entity target)
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
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);
		projectile_new(firingx, firingy - 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);


}


void adv_skirmisher_update(Entity* self, Entity target)
{

	if (!self)return;



}
void adv_skirmisher_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}