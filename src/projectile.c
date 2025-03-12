#include "simple_logger.h"

#include "projectile.h"

void projectile_think(Entity* self);
void projectile_update(Entity* self);
void projectile_free(Entity* self);

Entity *projectile_new(int startx, int starty, int team, int damage, int dtd, int speed)
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
	self->damage = damage;
	self->distance_to_die = dtd;

	self->think = projectile_think;
	self->update = projectile_update;
	self->free = projectile_free;

	if (self->team == 0)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/projectiles/player_shot.png",
			16,
			8,
			1,
			0);
	}
	if (self->team == 1)
	{
		self->sprite = gf2d_sprite_load_all(
			"images/projectiles/enemy_shot.png",
			16,
			8,
			1,
			0);
	}

	self->frame = 0;
	self->position = gfc_vector2d(startx, starty);
	
}

void projectile_think(Entity *self)
{
	GFC_Vector2D dir = { 0 };
	int speed = self->speed;
	int dtd = self->distance_to_die;
	int current = self->position.x;

	if (self->team == 0)
	{
		self->position.x += speed;
	}

	if (self->team == 1)
	{
		self->position.x -= speed;
	}

	if (self->team == 1)
	{
		if(self->position.x == 500)
		{ 
		projectile_free(self);
		}
	}

}
void projectile_update(Entity* self)
{
	if (!self)return;


	gfc_vector2d_add(self->position, self->position, self->velocity);

}
void projectile_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
}