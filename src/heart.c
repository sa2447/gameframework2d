#include "simple_logger.h"

#include "heart.h"

void heart_think(Entity* self);
void heart_update(Entity* self);
void heart_free(Entity* self);

Entity* heart_new(int startx, int starty, int team, int total, int speed)
{
	Entity* self;

	self = entity_new();

	if (!self)
	{
		slog("failed to spawn a player");
		return NULL;

	}

	self->frame = 0;
	self->position = gfc_vector2d(startx, starty);

	self->speed = speed;
	self->team = team;

	self->think = heart_think;
	self->update = heart_update;
	self->free = heart_free;
	self->total = total;

	

	self->going.x = 1700;

	self->frame = 0;
	self->position = gfc_vector2d(startx, starty);

}

void heart_loss(Entity* self, int loss_amount)
{
	int loss;
	int total;

	total = self->total;
	loss = loss_amount;
	
	self->total = total - loss;
}

void heart_think(Entity* self)
{
	GFC_Vector2D dir = { 0 };
	int speed = self->speed;
	int dtd = self->distance_to_die;
	int current = self->position.x;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);

	self->frame = 0;

	if (self->total == 5)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/entities/heart_5.png",
			320,
			64,
			1,
			0);
	}
	if (self->total == 4)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/entities/heart_4.png",
			256,
			64,
			1,
			0);
	}
	if (self->total == 3)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/entities/heart_3.png",
			192,
			64,
			1,
			0);
	}
	if (self->total == 2)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/entities/heart_2.png",
			128,
			64,
			1,
			0);
	}
	if (self->total == 1)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/entities/heart_1.png",
			64,
			64,
			1,
			0);

	}

	if (self->position.x < self->going.x)
	{
		self->position.x += speed;
	}
/*
	if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= speed;
		}
	if (keys[SDL_SCANCODE_S])
	{
		self->position.y += speed;
		
	
	//slog("S is pressed");
}
*/
	if (keys[SDL_SCANCODE_Z])
	{
		self->total = 4;
	}
	if (keys[SDL_SCANCODE_X])
	{
		self->total = 3;
	}
	if (keys[SDL_SCANCODE_C])
	{
		self->total = 2;
	}
	if (keys[SDL_SCANCODE_V])
	{
		self->total = 1;
	}
	

}
void heart_update(Entity* self)
{
	if (!self)return;


	gfc_vector2d_add(self->position, self->position, self->velocity);

}
void heart_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}