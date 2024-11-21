#ifndef WORLD_H
#define WORLD_H

#include "terminal-graphics/Graphics.h"
#include "common.h"

#define HEIGHT 11
#define WIDTH 11

#define BIOMEHEIGHT 18
#define BIOMEWIDTH 85

// World statically defined as a canvas_t world [N][M]
// every world[i][j] is a canvas BIOMEHEIGHT x BIOMEWIDTH

// creates a new biome inside the current world[i][j] cell
void world_create_biome();

//returns a pointer to the current biome
canvas_t * world_get_curr_biome();

//returns i and j of current biome (world[i][j])
v2i_t world_get_curr_biome_coord();

canvas_t world_get_left_biome();
canvas_t world_get_right_biome();
canvas_t world_get_up_biome();
canvas_t world_get_down_biome();

//returns the tile at the given position of the current biome
unsigned char world_get_tile(v2i_t coords);

//sets a tile at the given position of the current biome
void world_set_tile(v2i_t coords, unsigned char tile);
#endif