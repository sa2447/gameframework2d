#include "simple_logger.h"

#include "entity.h"
#include "monster.h"


void monster_think(Entity *self, Entity target);
void monster_update(Entity *self, Entity target);
void monster_free(Entity *self);

Entity *monster_new(int x, int y, Entity target, int health, int shield, int currency)
{
	Entity *self;
	Entity enemy = target;
	

	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a monster");
		return NULL;

	}
	self->sprite = gf2d_sprite_load_all(
		"images/entities/ram.png",
		32,
		32,
		1,
		0);
	self->frame = 0;
	self->position = gfc_vector2d(x, y);

	self->think = monster_think;
	self->update = monster_update;
	self->free = monster_free;

	
	monster_update(self, enemy);
	
	//self->going.x = 200;
	//self->going.y = 200;
	

	self->going.x = 64;


	return self;
}
void monster_think(Entity* self, Entity target)
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
		monster_free(self);
	}
/*
	if (self->position.y != self->going.y)
	{
		if (self->position.x > self->going.x)
		{
			self->position.x -= 1;
		}
		if (self->position.y > self->going.y)
		{
			self->position.y -= 1;
		}
		if (self->position.x < self->going.x)
		{
			self->position.x += 1;
		}
		if (self->position.y < self->going.y)
		{
			self->position.y += 1;
		}
		
	}
*/
	

	
	/*
		if (SDL_GetMouseState(&mx, &my) == SDL_BUTTON(3))
		{
			self->going.x = 300;
			self->going.y = 300;
			slog("bug sounds");
			return;
		}
		if (SDL_GetMouseState(&mx, &my) == SDL_BUTTON(2))
		{
			self->going.x = 300;
			self->going.y = 300;
			slog("bug dying sounds");
			return;
		}
	*/
}


void monster_update(Entity *self, Entity target)
{
	//Entity enemy = target;
	if (!self)return;

	//self->frame += 0.1;
	//if (self->frame >= 16)self->frame = 0;
	
	//monster_think(self, target);

}
void monster_free(Entity *self)
{
	if (!self)return;
	entity_free(self);
}