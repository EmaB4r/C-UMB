#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"
#include "terminal-graphics/Graphics.h"

typedef struct player_s{
    v2i_t pos;
}player_t;

int player_move_left(player_t *p);
int player_move_right(player_t *p);
int player_move_up(player_t *p);
int player_move_down(player_t *p);

#endif