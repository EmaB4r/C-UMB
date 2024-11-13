#ifndef WORLD_H
#define WORLD_H

#include "terminal-graphics/Graphics.h"
#include <time.h>
#include <stdlib.h>

#define HEIGHT 11
#define WIDTH 11

#define BIOMEHEIGHT 20
#define BIOMEWIDTH 90

void world_create_biome();
canvas_t * world_get_curr_biome();
v2i_t world_get_curr_biome_coord();
canvas_t world_get_left_biome();
canvas_t world_get_right_biome();
canvas_t world_get_up_biome();
canvas_t world_get_down_biome();

#endif