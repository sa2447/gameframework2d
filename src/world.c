#include "simple_logger.h"
#include "simple_json.h"

#include "gf2d_graphics.h"

#include "camera.h"
#include "world.h"


void level_tile_layer_build(Level *level)
{
	int i;
	int j;
	int index;
	Uint32 frame;
	GFC_Vector2D position;


	if (!level)
		return;

	if (!level->tileSet)
		return;

	if (level->tileLayer)
	{
		gf2d_sprite_free(level->tileLayer);
	}

	level->tileLayer = gf2d_sprite_new();


	level->tileLayer->surface = gf2d_graphics_create_surface(
		level->tileWidth * level->tileSet->frame_w,
		level->tileHeight * level->tileSet->frame_h);

	level->tileLayer->frame_w = level->tileWidth * level-> tileSet->frame_w;
	level->tileLayer->frame_h = level->tileHeight * level->tileSet->frame_h;

	if (!level->tileLayer->surface)
	{
		slog("failed to create tile layer");
		return;
	}

	for (j = 0; j < level->tileHeight; j++)
	{
		for (i = 0; i < level->tileWidth; i++)
		{
			index = i + (j * level->tileWidth);
			if (level->tileMap[index] == 0)
				continue;


			position.x = i * level->tileSet->frame_w;
			position.y = j * level->tileSet->frame_h;
			frame = level->tileMap[index] - 1;


			gf2d_sprite_draw_to_surface(
				level->tileSet,
				position,
				NULL,
				NULL,
				frame,
				level->tileLayer->surface);
		}
	}

	level->tileLayer->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), level->tileLayer->surface);
	if (!level->tileLayer->texture)
	{
		slog("failed to convert world tile layer to texture");
		return;
	}
}

Level* level_load(const char* filename, int levelselcted)
{
	Level* level = NULL;

	SJson* json = NULL;
	SJson* wjson = NULL;
	SJson* height;
	SJson* Width;
	SJson* vertical;
	SJson* horizontal;
	SJson* item;

	const char* tileSet;
	const char* background;
	
	int w = 0;
	int h = 0;
	int i;
	int j;
	int tile;
	int frame_w;
	int frame_h;
	int frames_per_line;

	int current_level;

	current_level = levelselcted;



	if (!filename)
	{
		slog("no file name for level load");
		return NULL;
	}

	json = sj_load(filename);
	
	if (!json)
	{
		slog("failed to load level file %s",filename);
	}



	if(current_level == 1)
	{ 
		wjson = sj_object_get_value(json, "level_1");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 2)
	{
		wjson = sj_object_get_value(json, "level_2");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 3)
	{
		wjson = sj_object_get_value(json, "Main_Menu");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 4)
	{
		wjson = sj_object_get_value(json, "Beast");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 5)
	{
		wjson = sj_object_get_value(json, "Game_Over");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}

	vertical = sj_object_get_value(wjson, "tileMap");
	if (!vertical)
	{
		slog("%s missing 'tilemap'", filename);
		sj_free(json);
		return NULL;
	}

	h = sj_array_get_count(vertical);
	horizontal = sj_array_get_nth(vertical,0);
	w = sj_array_get_count(horizontal);
	level = level_new(w,h);
	if (!level)
	{
		slog("failed to create space for a new world for file %s", filename);
		sj_free(json);
		return NULL;
	}

	for (j = 0; j < h; j++)
	{
		horizontal = sj_array_get_nth(vertical, j);
		if (!horizontal)continue;
		for (i = 0; i < w; i++)
		{
			item = sj_array_get_nth(horizontal, i);
			if (!item)continue;
			tile = 0;
			sj_get_integer_value(item, &tile);
			level->tileMap[i +(j*w)] = tile;

		}
	}

	background = sj_object_get_value_as_string(wjson, "background");
	level->background = gf2d_sprite_load_image(background);

	tileSet = sj_object_get_value_as_string(wjson, "tileSet");
	sj_object_get_value_as_int(wjson, "frame_w", &frame_w);
	sj_object_get_value_as_int(wjson, "frame_h", &frame_h);
	sj_object_get_value_as_int(wjson, "frames_per_line", &frames_per_line);


	level->tileSet = gf2d_sprite_load_all(
		tileSet,
		frame_w,
		frame_h,
		frames_per_line,
		1);

	level_tile_layer_build(level);

	level->selected = current_level;

	sj_free(json);

	return level;
}

Level *level_new(Uint32 width, Uint32 height)
{
	Level *level;

	if ((!width) || (!height))
	{
		slog("cannont not make world with 0 width and height");
		return NULL;
	}

	level = gfc_allocate_array(sizeof(Level),1);
	if (!level)
	{
		slog("failed to allocate world");
		return NULL;
	}
	level->tileMap = gfc_allocate_array(sizeof(Uint8), height*width);
	level->tileHeight = height;
	level->tileWidth = width;
	
	return level;
}

void level_free(Level *level)
{
	if (!level)
		return;
	gf2d_sprite_free(level->background);
	gf2d_sprite_free(level->tileSet);
	gf2d_sprite_free(level->tileLayer);
	free(level->tileMap);
	free(level);

}
void level_free_soft(Level* level)
{
	if (!level)
		return;
	gf2d_sprite_free(level->background);
	gf2d_sprite_free(level->tileSet);
	gf2d_sprite_free(level->tileLayer);
	free(level);
}

void level_draw(Level *level)
{

	GFC_Vector2D offset;

	GFC_Vector2D cam, diff, size, parallax = { 0 };

	if (!level)
		return;
	offset = camera_get_offset();
	size = camera_get_size();
	

	gf2d_sprite_draw_image(level->background, gfc_vector2d(0, 0));


	gf2d_sprite_draw_image(level->tileLayer, offset);
	
}

void level_setup_camera(Level *level)
{
	if (!level)return;
	if (!level->tileLayer || (!level->tileLayer->surface))
	{
		slog("no tile layer set for world");
		return;
	}
	camera_set_bounds(gfc_rect(0,0,(level->tileLayer->surface->w),(level->tileLayer->surface->h)));
	camera_apply_bounds();
	camera_enable_binding(1);

}

int get_spawn_x(const char* filename, int levelselcted)
{
	Level* level = NULL;

	SJson* json = NULL;
	SJson* wjson = NULL;

	int spawn_x;

	int current_level;

	current_level = levelselcted;



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



	if (current_level == 1)
	{
		wjson = sj_object_get_value(json, "level_1");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 2)
	{
		wjson = sj_object_get_value(json, "level_2");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}

	sj_object_get_value_as_int(wjson, "spawn_x", &spawn_x);

	return spawn_x;


}
int get_spawn_y(const char* filename, int levelselcted)
{
	Level* level = NULL;

	SJson* json = NULL;
	SJson* wjson = NULL;

	int spawn_y;

	int current_level;

	current_level = levelselcted;



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



	if (current_level == 1)
	{
		wjson = sj_object_get_value(json, "level_1");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}
	if (current_level == 2)
	{
		wjson = sj_object_get_value(json, "level_2");
		if (!wjson)
		{
			slog("missing 'level' object", filename);
			sj_free(json);
			return NULL;
		}
	}

	sj_object_get_value_as_int(wjson, "spawn_y", &spawn_y);

	return spawn_y;


}
