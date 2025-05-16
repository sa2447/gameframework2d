#include "simple_logger.h"
#include "tracker.h"

void tracker_think(Entity* self);
void tracker_update(Entity* self);
void tracker_free(Entity* self);

Entity* tracker_new(int startx, int starty, int team, int total, int speed)
{
	Entity* self;

	self = entity_new();

	if (!self)
	{
		slog("failed to spawn a tracker");
		return NULL;

	}

	self->frame = 0;
	self->position = gfc_vector2d(startx, starty);

	self->speed = speed;
	self->team = team;

	self->think = tracker_think;
	self->update = tracker_update;
	self->free = tracker_free;
	self->total = total;



	self->going.x = 2000;

	self->frame = 0;
	self->position = gfc_vector2d(startx, starty);

}
void tracker_think(Entity* self)
{
	GFC_Vector2D dir = { 0 };
	int speed = self->speed;
	int dtd = self->distance_to_die;
	int current = self->position.x;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);

	self->frame = 0;

	if (self->total == 1)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/1.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 2)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/2.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 3)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/3.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 4)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/4.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 5)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/5.png",
			160,
			16,
			1,
			0);

	}
	if (self->total == 6)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/6.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 7)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/7.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 8)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/8.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 9)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/9.png",
			160,
			16,
			1,
			0);
	}
	if (self->total == 10)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/backgrounds/s/10.png",
			160,
			16,
			1,
			0);

	}

	if (self->position.x < self->going.x)
	{
		self->position.x += speed;
	}

	if (self->position.x <= 200)
	{
		self->total = 1;
	}
	if (self->position.x == 400)
	{
		self->total = 2;
	}
	if (self->position.x == 600)
	{
		self->total = 3;
	}
	if (self->position.x == 800)
	{
		self->total = 4;
	}
	if (self->position.x == 1000)
	{
		self->total = 5;
	}
	if (self->position.x == 1200)
	{
		self->total = 6;
	}
	if (self->position.x == 1400)
	{
		self->total = 7;
	}
	if (self->position.x == 1600)
	{
		self->total = 8;
	}
	if (self->position.x == 1800)
	{
		self->total = 9;
	}
	if (self->position.x == 2000)
	{
		self->total = 10;
	}

	if (keys[SDL_SCANCODE_N])
	{
		//entity_clear_all(self);
		self->position.x = 96;
	}

}
void tracker_update(Entity* self)
{
	if (!self)return;
}
void tracker_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}

