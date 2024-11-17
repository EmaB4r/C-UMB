#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"
#include "terminal-graphics/Graphics.h"

typedef struct player_s{
    v2i_t pos;
    unsigned char inv_ch[9];
    unsigned char inv_count[9];
}player_t;

int inventory_add(player_t * p, unsigned char c, unsigned char amount);
void inventory_print(player_t * p);

int player_move_left(player_t *p);
int player_move_right(player_t *p);
int player_move_up(player_t *p);
int player_move_down(player_t *p);

#endif