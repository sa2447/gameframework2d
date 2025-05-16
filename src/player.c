#include "simple_logger.h"

#include "gf2d_draw.h"
#include "gfc_shape.h"

#include "camera.h"
#include "player.h"
#include "projectile.h"
#include "heart.h"

#include "spawning.h"



void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);

Entity* player_load(const char* filename, int startx, int starty, int level, Level *current, Entity *hearts)
{

	SJson* json = NULL;
	SJson* wjson = NULL;

	Entity* player = NULL;
	Entity* heart_count;
	Sprite* sprite;

	int health;
	int shield;
	int currency;
	int speed;
	int lives;
	int current_level;
	int start_x = startx;
	int start_y = starty;

	Level *now = current;


	heart_count = hearts;


	if (!filename)
	{
		slog("no file name for player load");
		return NULL;
	}

	json = sj_load(filename);

	if (!json)
	{
		slog("failed to load player file %s", filename);
	}

	wjson = sj_object_get_value(json, "player_stats");
	if (!wjson)
	{
		slog("missing 'player' object", filename);
		sj_free(json);
		return NULL;
	}

	sj_object_get_value_as_int(wjson, "health", &health);
	sj_object_get_value_as_int(wjson, "shield", &shield);
	sj_object_get_value_as_int(wjson, "currency", &currency);
	sj_object_get_value_as_int(wjson, "speed", &speed);
	sj_object_get_value_as_int(wjson, "lives", &lives);
	//sj_object_get_value_as_int(wjson, "level", &current_level);

	player = player_new(health, shield, speed, currency, start_x, start_y,lives,now, heart_count);



	sj_free(json);

	return player;
}

Entity* player_new(int health, int shield, int speed, int currency, int startx, int starty, int lives, Level *level, Entity *heart_tracker)
{
	Entity *player;
	Entity* heart = heart_tracker;

	
	player = entity_new();
	if (!player)
	{
		slog("failed to spawn a player");
		return NULL;

	}
	
	player->sprite = gf2d_sprite_load_all(
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

	player->frame = 0;
	player->position = gfc_vector2d(startx,starty);

	player->speed = speed;
	player->health = health;
	player->shield = shield;
	player->currency = currency;

	player->think = player_think;
	player->update = player_update;
	player->free = player_free;

	player->currentx = player_get_x;
	player->currenty = player_get_y;

	player->can_move = 0;
	player->alive = 0;
	player->going.x = 1700; //set to area before boss
	
	player->team = T_Player;
	player->type = T_Main;

	player->current = level;

	return player;

	
}
void player_think(Entity* player, Entity* other)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx = 0, my = 0;
	const Uint8* keys;
	int speed = player->speed;

	int firingx, firingy, team, damage, distance, b_speed;


	firingx = player->position.x + 10;
	firingy = player->position.y;
	team = 0;
	damage = 5;
	distance = 10;
	b_speed = 4;

	GFC_Rect check;

	check = player->hitbox;

	
	if (!player)return;

	keys = SDL_GetKeyboardState(NULL);

	//Start Controls

	player->can_move = 1;


	if (keys[SDL_SCANCODE_W]) //Upwards Movement
	{
		if (player->position.y >= 70)
		{
			player->position.y -= speed;
		}
		else
		{
			player->position.y += 10;
		}
		//slog("W is pressed");
	}
	if (keys[SDL_SCANCODE_A] && (player->can_move >= 1)) //Backwards movement
	{
		player->position.x -= speed;
		//slog("A is pressed");
	}
	if (keys[SDL_SCANCODE_S]) //Downwards Movement
	{
		if (player->position.y <= 650)
		{
			player->position.y += speed;
		}
		else
		{
			player->position.y -= 10;
		}
		//slog("S is pressed");
	}
	if (keys[SDL_SCANCODE_D] && (player->can_move >= 1)) //Forward movement
	{
		if (player->position.x <= 2100)
		{
			player->position.x += speed;
		}
		else
		{
			player->position.x -= 10;
		}
		//slog("D is pressed");
	}
	if (keys[SDL_SCANCODE_E])
	{
		slog("interact");
	}

	if (keys[SDL_SCANCODE_L])
	{
		player_free(player);

	}

//Auto Scroll until boss fight


	if (player->position.x != player->going.x)
	{
		if (player->position.x < player->going.x)
		{
			player->position.x += speed;
		}
	}
	if (player->position.x == player->going.x)
	{
		//self->alive += 1;
		player->can_move = 1;
	}
	/*
	if (player->alive >= 1)
	{
		player_free(player);
		player_new(5, 5, 2, 0);
	}*/
	//End Auto Scroll



	if (keys[SDL_SCANCODE_G])
	{
		heart_loss(player, 1);

		//teleport?
	}

	if (SDL_GetMouseState(&mx, &my) == SDL_BUTTON(1))
	{


		//slog("fire");
		projectile_new(firingx, firingy, team, damage, distance, b_speed);
	}


	//next level
	if (player->position.x >= 2000 && keys[SDL_SCANCODE_N])
	{
		//heart = heart_new(160, 700, 0, 5, 2); player_advance(player);
	}
	
	//Content Generation
	int timer1 = gfc_random_int(100);
	int choice;
	int schoice;

	int xdis;
	int ydis;
	

	int stop_spawns;

	stop_spawns = player->going.x - 100;

	if(player->position.x == player->going.x)
	{
		enemy_new("defs/ents/en.def", 6, 2000,384 , check);
		return;
	}
	else 
	{	
		if (timer1 == 50 && (player->position.x < (player->going.x - 100)))
		{

			choice = gfc_random_int(5) + 1;
			schoice = choice;

			xdis = player->position.x + gfc_random_int(100) + 500;
			ydis = gfc_random_int(550) + 80;
			enemy_new("defs/ents/en.def", choice, xdis, ydis, check);
		}

	}


}

float player_get_x(Entity* player)
{
	int currentx;

	currentx = player->position.x;
	
	return currentx;
}

float player_get_y(Entity* player)
{
	int currenty;

	currenty = player->position.y;

	return currenty;
}
int get_current_level(const char* filename)
{
	SJson* json = NULL;
	SJson* wjson = NULL;

	Entity* player = NULL;

	int current_level;



	if (!filename)
	{
		slog("no file name for level load");
		return NULL;
	}

	json = sj_load(filename);

	if (!json)
	{
		slog("failed to load level file %s", filename);
	}

	wjson = sj_object_get_value(json, "player_stats");
	if (!wjson)
	{
		slog("missing 'player' object", filename);
		sj_free(json);
		return NULL;
	}

	sj_object_get_value_as_int(wjson, "current_level", &current_level);

	return current_level;


}
void player_update(Entity * player)
{

	if (!player)return;

	//self->frame += 0.1;
	//if (self->frame >= 16)self->frame = 0;

	gfc_vector2d_add(player->position, player->position, player->velocity);

	camera_center_on(player->position);
}

void player_advance(Entity* player)
{
	Level *remove;
	Level* level;

	remove = player->current;

}
void player_free(Entity * player)
{
	Level* level;

	if (!player)return;

	level = level_load("defs/levels/levels.map", 2);
	//sj_save("defs/ents/player_default.def", "defs/ents/player_save.def");
	entity_clear_all(NULL);

	entity_free(player);
}