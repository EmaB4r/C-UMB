#include "player.h"
#include "terminal-graphics/Graphics.h"
#include "world.h"
#include <stdio.h>

enum direction{up, down, left, right};

int inventory_has(player_t * p, unsigned char c){
    for(int i = 0; i < 9; i++){
        if(p->inv_ch[i]==c) return 1;
    }
    return 0;
}

int inventory_add(player_t * p, unsigned char c, unsigned char amount){
    int first_free_slot = -1;
    for(int i=0; i<9; i++){
        if(first_free_slot == -1 && p->inv_count[i]==0) first_free_slot = i;
        if(p->inv_ch[i] == c){
            p->inv_count[i]+=amount;
            return 1;
        }
    }
    if(first_free_slot!=-1){
        p->inv_ch[first_free_slot] = c;
        p->inv_count[first_free_slot]=amount;
        return 1;
    }
    return 0;
}

void inventory_print(player_t * p){
    printf("%*s", BIOMEWIDTH/2 - 10, "");
    for(int i = 0; i < 9; i++){
        putc(' ', stdout);
        putc(p->inv_ch[i], stdout);
    }
    putc('\n', stdout);
    printf("%*s", BIOMEWIDTH/2 - 10, "");
    for(int i = 0; i < 9; i++){
        printf("%2d", p->inv_count[i]);
    }
    putc('\n', stdout);
}

int break_tile(enum direction d, player_t *p){
    v2i_t tilepos = p->pos;
    unsigned char tile;
    switch(d){
        case up: tilepos.y--; break;
        case down: tilepos.y++; break;
        case left: tilepos.x--; break;
        case right: tilepos.x++; break;
    }
    tile = world_get_tile(tilepos);
    switch (tile) {
        case 't':{
            if(inventory_has(p, 'a')){
                if (inventory_add(p, 'w', 1)){
                    world_set_tile(tilepos, 'g');
                    return 1;
                }
                world_set_tile(tilepos, 'W');
                return 0;
            }
        }
        break;
    }
    return 0;
}

int player_move_left(player_t *p){
    break_tile(left, p);
    p->pos.x--;
    if(p->pos.x < 0){
        p->pos.x=BIOMEWIDTH-1;
        return 1;
    }
    return 0;
}
int player_move_right(player_t *p){
    p->pos.x++;
    if(p->pos.x > BIOMEWIDTH-1){
        p->pos.x=0;
        return 1;
    }
    return 0;
}
int player_move_up(player_t *p){
    break_tile(up, p);
    p->pos.y--;
    if(p->pos.y < 0){
        p->pos.y = BIOMEHEIGHT-1;
        return 1;
    }
    return 0;
}
int player_move_down(player_t *p){
    p->pos.y++;
    if(p->pos.y > BIOMEHEIGHT-1){
        p->pos.y = 0;
        return 1;
    }
    return 0;
}