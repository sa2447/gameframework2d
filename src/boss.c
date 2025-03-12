#include "simple_logger.h"

#include "entity.h"
#include "boss.h"


void boss_think(Entity* self, Entity target);
void boss_update(Entity* self, Entity target);
void boss_free(Entity* self);

Entity* boss_new(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity* self;
	Entity enemy = target;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a boss");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/boss.png",
		64,
		64,
		1,
		0);
	self->frame = 0;
	self->position = gfc_vector2d(x, y);

	self->health = health;
	self->shield = shield;
	self->currency = currency;

	self->think = boss_think;
	self->update = boss_update;
	self->free = boss_free;


	boss_update(self, enemy);

	return self;
}
void boss_think(Entity* self, Entity target)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx, my;
	int bounce_check;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);
	
	if (!self)return;

	//Movement 
	if (keys[SDL_SCANCODE_W])
	{
		if (self->position.y >= 70)
		{
			self->position.y -= 2;
		}
		else
		{
			self->position.y += 10;
		}
		//slog("W is pressed");
	}
	if (keys[SDL_SCANCODE_S])
	{
		if (self->position.y <= 650)
		{
			self->position.y += 2;
		}
		else
		{
			self->position.y -= 10;
		}
		//slog("S is pressed");
	}
		//slog("D is pressed");

	int timer = self->position.y;
	int firingx = self->position.x;
	int firingy = self->position.y;
	int team = 1;
	int damage = 5;
	int distance = 10;
	int b_speed = 2;

	if (timer % 25 == 0)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);
		
		projectile_new(firingx, firingy - 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);

	
}


void boss_update(Entity* self, Entity target)
{

	if (!self)return;



}
void boss_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}