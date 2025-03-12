#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"

typedef struct
{
	Sprite *background; //background image
	Sprite *tileLayer; // prerendered tile layer
	Sprite *tileSet; //tile sheet
	Uint8 *tileMap; //tiles
	Uint32 tileHeight; //tiles high
	Uint32 tileWidth; //tiles wide

}Level;

Level* level_load(const char* filename);

Level *level_test_new();

Level *level_new(Uint32 width, Uint32 height);

void level_free(Level *level);

void level_draw(Level *level);

void level_tile_layer_build(Level* level);

void level_setup_camera(Level* level);

#endif

