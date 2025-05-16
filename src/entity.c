#include "simple_logger.h"

#include "camera.h"
#include "entity.h"

typedef struct
{
	Entity *entity_list;
	Uint32 entity_max;
}EntityManager;



void entity_system_close();


static EntityManager _entity_manager = { 0 };

void entity_system_initialize(Uint32 max)
{
	if (_entity_manager.entity_list)
	{
		slog("can not have two instances of an entity manager, one is already active");
		return;
	}
	if (!max)
	{
		slog("can not allocate 0 entities");
		return;
	}
	_entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), max);
	if (!_entity_manager.entity_list)
	{
		slog("failed to allocate global entity list");
		return;
	}
	_entity_manager.entity_max = max;
	atexit(entity_system_close);
}

void entity_system_close()
{
	entity_clear_all(NULL);
	if (_entity_manager.entity_list)free(_entity_manager.entity_list);
	memset(&_entity_manager, 0, sizeof(EntityManager));
}

void entity_clear_all(Entity *ignore)
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (&_entity_manager.entity_list[i] == ignore)continue;
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_free(&_entity_manager.entity_list[i]);

	}
}

Entity *entity_new()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (_entity_manager.entity_list[i]._inuse)continue;
		memset(&_entity_manager.entity_list[i], 0, sizeof(Entity));
		_entity_manager.entity_list[i]._inuse = 1;

		return &_entity_manager.entity_list[i];
	}
	slog("no more available entities");
	return NULL;
}

void entity_free(Entity *self)
{
	if (!self)return;
	gf2d_sprite_free(self->sprite);
	if (self->free)self->free(self->data);
	memset(self, 0, sizeof(*self));

}

void entity_think(Entity *self)
{
	if (!self)return;

	if (self->think)self->think(self);
}

void entity_system_think()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_think(&_entity_manager.entity_list[i]);
	}

}

void entity_update(Entity *self)
{
	if (!self)return;

	if (self->update)self->update(self);
}

void entity_system_update()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_update(&_entity_manager.entity_list[i]);
	}

}
void entity_draw(Entity *self)
{
	GFC_Vector2D offset;
	GFC_Vector2D position;

	GFC_Rect hitbox;

	

	if (!self)return;

	offset = camera_get_offset();
	gfc_vector2d_add(position, self->position, offset);

	if (self->type == T_Projectile)
	{
		hitbox = gfc_rect(position.x, position.y, 20, 10);
		gf2d_draw_rect(hitbox, GFC_COLOR_ORANGE);
		self->hitbox = hitbox;
	}

	if (self->type == T_Ant)
	{
		hitbox = gfc_rect(position.x, position.y, 32, 32);
		gf2d_draw_rect(hitbox, GFC_COLOR_RED);
		self->hitbox = hitbox;
	}

	if (self->type == T_Main)
	{
		hitbox = gfc_rect(position.x, position.y, 32, 32);
		gf2d_draw_rect(hitbox, GFC_COLOR_DARKGREEN);
		self->hitbox = hitbox;
	}



	if (self->sprite);
	{
		gf2d_sprite_render(
			self->sprite,
			position,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			(Uint32)self->frame);
	}
}

GFC_Vector2D get_position(Entity target)
{
	return target.position;
}


void entity_system_draw()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;
		entity_draw(&_entity_manager.entity_list[i]);
	}



}