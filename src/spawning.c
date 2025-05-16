#include "entity.h"
#include "gfc_shape.h"
#include "gf2d_draw.h"

#include "projectile.h"
#include "spawning.h"

void ram_think(Entity* self, Entity target);
void skirmisher_think(Entity* self, Entity target);
void shield_bot_think(Entity* self, Entity target);
void adv_skirmisher_think(Entity* self, Entity target);
void assassin_think(Entity* self, Entity target);
void boss_think(Entity* self, Entity target);

void enemy_update(Entity* self, Entity target);
void boss_update(Entity* self, Entity target);

void enemy_free(Entity* self);
void boss_free(Entity* self);




Entity* enemy_new(const char* filename, int key, int x, int y, GFC_Rect other)
{
	SJson* json = NULL;
	SJson* wjson = NULL;

	Entity* enemy = NULL;
	Sprite* sprite;

	GFC_Rect target;

	int health;
	int shield;
	int currency;
	int shots;
	int spawnx = x;
	int spawny = y;

	int creature = key;

	if (!filename)
	{
		slog("no file name for enemy load");
		return NULL;
	}
	
	json = sj_load(filename);

	if (!json)
	{
		slog("failed to load enemy file %s", filename);
	}
	
	if (creature == 1)
	{
		wjson = sj_object_get_value(json, "ram");
		if (!wjson)
		{
			slog("missing 'ram' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (creature == 2)
	{
		wjson = sj_object_get_value(json, "skirmisher");
		if (!wjson)
		{
			slog("missing 'skirmisher' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (creature == 3)
	{
		wjson = sj_object_get_value(json, "shield_bot");
		if (!wjson)
		{
			slog("missing 'shield bot' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (creature == 4)
	{
		wjson = sj_object_get_value(json, "adv_skrimisher");
		if (!wjson)
		{
			slog("missing 'adv skirmisher' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (creature == 5)
	{
		wjson = sj_object_get_value(json, "assassin");
		if (!wjson)
		{
			slog("missing 'assassin' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (creature == 6)
	{
		wjson = sj_object_get_value(json, "boss");
		if (!wjson)
		{
			slog("missing 'boss' object", filename);
			sj_free(json);
			return NULL;
		}
	}

	sj_object_get_value_as_int(wjson, "health", &health);
	sj_object_get_value_as_int(wjson, "shield", &shield);
	sj_object_get_value_as_int(wjson, "currency", &currency);
	sj_object_get_value_as_int(wjson, "shots", &shots);
	
	target = other;
	
	if (creature == 1)
	{
		enemy = new_ram( spawnx, spawny, health, shield, shots, currency,other);
	}
	if (creature == 2)
	{
		enemy = new_skirmisher(spawnx, spawny, health, shield, shots, currency);
	}
	if (creature == 3)
	{
		enemy = new_shield_bot(spawnx, spawny, health, shield, shots, currency);
	}
	if (creature == 4)
	{
		enemy = new_adv_skirmisher(spawnx, spawny, health, shield, shots, currency);
	}
	if (creature == 5)
	{
		enemy = new_assassin(spawnx, spawny, health, shield, shots, currency);
	}
	if (creature == 6)
	{
		enemy = new_boss(spawnx, spawny, health, shield, shots, currency);
	}
	

	sj_free(json);

	return enemy;
}

Entity* new_ram(int spawnx, int spawny, int health, int shield, int shot, int currency, GFC_Rect other)
{
	Entity* ram;

	ram = entity_new();
	if (!ram)
	{
		slog("failed to spawn a ram");
		return NULL;

	}

	ram->sprite = gf2d_sprite_load_all(
		"images/entities/ram.png",
		32,
		32,
		1,
		0);
	ram->frame = 0;
	ram->position = gfc_vector2d(spawnx, spawny);

	ram->health = health;
	ram->shield = shield;
	ram->currency = currency;

	ram->going.x = 64;

	ram->think = ram_think;
	ram->update = enemy_update;
	ram->free = enemy_free;

	ram->team = T_Enemy;
	ram->type = T_Ant;

	ram->target_hitbox = other;

	return ram;
}
Entity* new_skirmisher(int spawnx, int spawny, int health, int shield, int shot, int currency)
{
	Entity* skir;

	skir = entity_new();
	if (!skir)
	{
		slog("failed to spawn a skirmisher");
		return NULL;

	}

	skir->sprite = gf2d_sprite_load_all(
		"images/entities/skirmisher.png",
		32,
		32,
		1,
		0);
	skir->frame = 0;
	skir->position = gfc_vector2d(spawnx, spawny);

	skir->health = health;
	skir->shield = shield;
	skir->currency = currency;

	skir->going.x = 64;

	skir->think = skirmisher_think;
	skir->update = enemy_update;
	skir->free = enemy_free;

	skir->team = T_Enemy;
	skir->type = T_Ant;

	return skir;
}
Entity* new_shield_bot(int spawnx, int spawny, int health, int shield, int shot, int currency)
{
	Entity* sbot;

	sbot = entity_new();
	if (!sbot)
	{
		slog("failed to spawn a shield bot");
		return NULL;

	}

	sbot->sprite = gf2d_sprite_load_all(
		"images/entities/shield_drone.png",
		32,
		32,
		1,
		0);
	sbot->frame = 0;
	sbot->position = gfc_vector2d(spawnx, spawny);

	sbot->health = health;
	sbot->shield = shield;
	sbot->currency = currency;

	sbot->going.x = 64;

	sbot->think = shield_bot_think;
	sbot->update = enemy_update;
	sbot->free = enemy_free;

	sbot->team = T_Enemy;
	sbot->type = T_Ant;

	return sbot;
}
Entity* new_adv_skirmisher(int spawnx, int spawny, int health, int shield, int shot, int currency)
{
	Entity* askir;

	askir = entity_new();
	if (!askir)
	{
		slog("failed to spawn an advanced skirmisher");
		return NULL;

	}

	askir->sprite = gf2d_sprite_load_all(
		"images/entities/adv_skirmisher.png",
		32,
		32,
		1,
		0);
	askir->frame = 0;
	askir->position = gfc_vector2d(spawnx, spawny);

	askir->health = health;
	askir->shield = shield;
	askir->currency = currency;

	askir->going.x = 64;

	askir->think = adv_skirmisher_think;
	askir->update = enemy_update;
	askir->free = enemy_free;

	askir->team = T_Enemy;
	askir->type = T_Ant;

	return askir;
}
Entity* new_assassin(int spawnx, int spawny, int health, int shield, int shot, int currency)
{
	Entity* assassin;

	assassin = entity_new();
	if (!assassin)
	{
		slog("failed to spawn an assassin");
		return NULL;

	}

	assassin->sprite = gf2d_sprite_load_all(
		"images/entities/assassin.png",
		32,
		32,
		1,
		0);
	assassin->frame = 0;
	assassin->position = gfc_vector2d(spawnx, spawny);

	assassin->health = health;
	assassin->shield = shield;
	assassin->currency = currency;
	assassin->sshots = shot;

	assassin->going.x = 64;

	assassin->think = assassin_think;
	assassin->update = enemy_update;
	assassin->free = enemy_free;

	assassin->team = T_Enemy;
	assassin->type = T_Ant;

	return assassin;
}
Entity* new_boss(int spawnx, int spawny, int health, int shield, int shot, int currency)
{
	Entity* boss;

	boss = entity_new();
	if (!boss)
	{
		slog("failed to spawn a boss");
		return NULL;

	}

	boss->sprite = gf2d_sprite_load_all(
		"images/entities/boss.png",
		64,
		64,
		1,
		0);
	boss->frame = 0;
	boss->position = gfc_vector2d(spawnx, spawny);

	boss->health = health;
	boss->shield = shield;
	boss->currency = currency;
	boss->sshots = shot;

	boss->going.x = 64;

	boss->think = boss_think;
	boss->update = boss_update;
	boss->free = enemy_free;

	boss->team = T_Enemy;
	boss->type = T_Boss;

	return boss;
}

void ram_think(Entity* self, Entity target)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx, my;
	int bounce_check;
	const Uint8* keys;

	keys = SDL_GetKeyboardState(NULL);


	if (!self)return;

	if (gfc_rect_overlap(self->hitbox, self->target_hitbox))
	{
		slog("ow");
	}

	//Movement
	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);


	if (self->position.x != self->going.x)
	{
		self->position.x -= 1;
	}

	if (self->position.x == self->going.x)
	{
		enemy_free(self);
	}

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}
}

void skirmisher_think(Entity* self, Entity target)
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
		enemy_free(self);
	}



	int sshots = self->sshots;
	int timer = gfc_random_int(sshots);
	int firingx = self->position.x;
	int firingy = self->position.y;

	int damage = self->damage;
	int distance = self->distance_to_die;
	int b_speed = 2;
	int team = self->team;
	if (timer == 100)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}
}
void shield_bot_think(Entity* self, Entity target)
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
		enemy_free(self);
	}

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}
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
		enemy_free(self);
	}



	int sshots = self->sshots;
	int timer = gfc_random_int(sshots);
	int firingx = self->position.x;
	int firingy = self->position.y;

	int damage = self->damage;
	int distance = self->distance_to_die;
	int b_speed = 2;
	int team = self->team;
	if (timer == 50)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}

}
void assassin_think(Entity* self, Entity target)
{
	GFC_Vector2D dir = { 0 };
	Sint32 mx, my;
	int bounce_check;
	const Uint8* keys;

	GFC_Rect mine;
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

	int sshots = self->sshots;
	int timer = gfc_random_int(sshots);
	int firingx = self->position.x;
	int firingy = self->position.y;

	int damage = self->damage;
	int distance = self->distance_to_die;
	int b_speed = 2;
	int team = self->team;
	if (timer == 25)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);

	}
	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}
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

	int sshots = self->sshots;
	int timer = gfc_random_int(sshots);
	int firingx = self->position.x;
	int firingy = self->position.y;

	int damage = self->damage;
	int distance = self->distance_to_die;
	int b_speed = 2;
	int team = self->team;
	if (timer == 25)
	{
		projectile_new(firingx, firingy + 10, team, damage, distance, b_speed);

	}



	gfc_vector2d_normalize(&dir);
	gfc_vector2d_scale(self->velocity, dir, 3);

	if (keys[SDL_SCANCODE_N])
	{
		enemy_free(self);
	}
}

void enemy_update(Entity* self, Entity target)
{
	if (!self)return;
}
void boss_update(Entity* self, Entity target)
{
	if (!self)return;
}

void enemy_free(Entity* self)
{
	if (!self)return;
	entity_free(self);
	
}


