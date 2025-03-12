#include "simple_logger.h"

#include "camera.h"
#include "player.h"
#include "projectile.h"
#include "heart.h"


void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);

Entity *player_new(int health, int shield, int speed, int currency)
{
	Entity *self;


	self = entity_new();
	if (!self)
	{
		slog("failed to spawn a player");
		return NULL;

	}
	
	self->sprite = gf2d_sprite_load_all(
		"images/entities/player.png",
		32,
		32,
		1,
		0);
/*
	self->sprite = gf2d_sprite_load_all(
		"images/player_laser.png",
		12,
		24,
		16,
		0);
*/

	self->frame = 0;
	self->position = gfc_vector2d(96,384);

	self->speed = speed;
	self->health = health;
	self->shield = shield;
	self->currency = currency;

	self->think = player_think;
	self->update = player_update;
	self->free = player_free;

	self->can_move = 0;
	self->alive = 0;
	self->going.x = 1700; //set to area before boss

	return self;


}
void player_think(Entity* self)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx = 0, my = 0;
	const Uint8* keys;
	int speed = self->speed;

	int firingx, firingy, team, damage, distance, b_speed;

	firingx = self->position.x + 10;
	firingy = self->position.y;
	team = 0;
	damage = 5;
	distance = 10;
	b_speed = 4;


	if (!self)return;

	keys = SDL_GetKeyboardState(NULL);

	//Start Controls


	if (keys[SDL_SCANCODE_W])
	{
		if (self->position.y >= 70)
		{
			self->position.y -= speed;
		}
		else
		{
			self->position.y += 10;
		}
		//slog("W is pressed");
	}
	if (keys[SDL_SCANCODE_A] && (self->can_move >= 1))
	{
		self->position.x -= speed;
		//slog("A is pressed");
	}
	if (keys[SDL_SCANCODE_S])
	{
		if (self->position.y <= 650)
		{
			self->position.y += speed;
		}
		else
		{
			self->position.y -= 10;
		}
		//slog("S is pressed");
	}
	if (keys[SDL_SCANCODE_D] && (self->can_move >= 1))
	{
		if (self->position.x <= 2000)
		{
			self->position.x += speed;
		}
		else
		{
			self->position.x -= 10;
		}
		//slog("D is pressed");
	}
	if (keys[SDL_SCANCODE_E])
	{
		slog("interact");
	}



	/*
	int timer = self->position.x;

	if (timer % 50 == 0)
	{
		projectile_new(firingx, firingy, team, damage, distance, b_speed);
	}
*/
//Auto Scroll until boss fight

/**/
	if (self->position.x != self->going.x)
	{
		if (self->position.x < self->going.x)
		{
			self->position.x += speed;
		}
	}
	else
	{
		//self->alive += 1;
		self->can_move += 1;
	}

	if (self->alive >= 1)
	{
		player_free(self);
		player_new(5, 5, 2, 0);
	}
	//End Auto Scroll



	if (keys[SDL_SCANCODE_G])
	{
		heart_loss(self, 1);

		//teleport?
	}






	if (SDL_GetMouseState(&mx, &my) == SDL_BUTTON(1))
	{


		slog("fire");
		projectile_new(firingx, firingy, team, damage, distance, b_speed);
	}

	//End Controls


	/* Testing Free
	if (SDL_GetMouseState(&mx, &my) == SDL_BUTTON(2))
	{
		player_free(self);
		slog("ship crashing sounds");
		return;
	}
	*/
}


void player_update(Entity *self)
{
	if (!self)return;

	//self->frame += 0.1;
	//if (self->frame >= 16)self->frame = 0;

	gfc_vector2d_add(self->position, self->position, self->velocity);

	camera_center_on(self->position);
}
void player_free(Entity *self)
{
	if (!self)return;
	entity_free(self);
}