#include "simple_logger.h"

#include "entity.h"
#include "assassin.h"


void assassin_think(Entity* self, Entity target);
void assassin_update(Entity* self, Entity target);
void assassin_free(Entity* self);

Entity* assassin_new(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity* self;
	Entity enemy = target;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a assassin");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/Assassin.png",
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

	self->think = assassin_think;
	self->update = assassin_update;
	self->free = assassin_free;


	assassin_update(self, enemy);

	return self;
}
void assassin_think(Entity* self, Entity target)
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
			self->position.y -= 4;
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
			self->position.y += 4;
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

	if (timer % 20 == 0)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);


}


void assassin_update(Entity* self, Entity target)
{

	if (!self)return;



}
void assassin_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}