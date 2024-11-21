#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"
#include "terminal-graphics/Graphics.h"

//player handler
typedef struct player_s{
    v2i_t pos;
    unsigned char inv_ch[9];
    unsigned char inv_count[9];
    char active_slot;
}player_t;

enum direction{up, down, left, right};

// adds to a player's inventory an item
int inventory_add(player_t * p, unsigned char c, unsigned char amount);

// changes the current active inventory slot (moving it left or right)
void change_inv_sel_item(player_t * p, enum direction d);

// prints the whole inventory centerd in the screen
void inventory_print(player_t * p);

int player_move_left(player_t *p);
int player_move_right(player_t *p);
int player_move_up(player_t *p);
int player_move_down(player_t *p);

#endif