#include "simple_logger.h"

#include "projectile.h"

void projectile_think(Entity* self);
void projectile_update(Entity* self);
void projectile_free(Entity* self);

Entity *projectile_new(int startx, int starty, Teams side, int damage, int dtd, int speed)
{
	Entity* projectile;

	projectile = entity_new();

	

	if (!projectile)
	{
		slog("failed to spawn a projectile");
		return NULL;

	}

	projectile->frame = 0;
	projectile->position = gfc_vector2d(startx, starty);

	projectile->speed = speed;
	projectile->team = side;
	projectile->damage = damage;
	projectile->distance_to_die = dtd;

	projectile->type = T_Projectile;

	projectile->think = projectile_think;
	projectile->update = projectile_update;
	projectile->free = projectile_free;

	if (projectile->team == T_Player)
	{
		projectile->sprite = gf2d_sprite_load_all(
			"images/projectiles/player_shot.png",
			16,
			8,
			1,
			0);
	}
	if (projectile->team == (T_Enemy || T_Boss))
	{
		projectile->sprite = gf2d_sprite_load_all(
			"images/projectiles/enemy_shot.png",
			16,
			8,
			1,
			0);
	}

	projectile->frame = 0;
	projectile->position = gfc_vector2d(startx, starty);
	
}

void projectile_think(Entity * projectile)
{
	GFC_Vector2D dir = { 0 };
	int speed = projectile->speed;
	int dtd = projectile->distance_to_die;
	int current = projectile->position.x;
	const Uint8* keys;

	if (projectile->team == T_Player)
	{
		projectile->position.x += speed;
		if (projectile->position.x == current + dtd)
		{
			projectile_free(projectile);
		}
	}

	if (projectile->team == T_Enemy)
	{
		projectile->position.x -= speed;
		if (projectile->position.x == current - dtd)
		{
			projectile_free(projectile);
		}
	}

	if (projectile->team == 1)
	{
		if(projectile->position.x == 500)
		{ 
		projectile_free(projectile);
		}
	}

	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_N])
	{
		projectile_free(projectile);
	}



}
void projectile_update(Entity* projectile)
{
	if (!projectile)return;


	gfc_vector2d_add(projectile->position, projectile->position, projectile->velocity);

}
void projectile_free(Entity* projectile)
{
	if (!projectile)return;
	entity_free(projectile);
}