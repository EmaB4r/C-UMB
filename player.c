#include "player.h"
#include "common.h"
#include "terminal-graphics/Graphics.h"
#include "terminal-graphics/ansi-terminal/Ansi.h"
#include "world.h"
#include <stdio.h>



unsigned char active_item(player_t * p){
    return p->inv_ch[p->active_slot];
}

int inventory_has(player_t * p, unsigned char c){
    for(int i = 0; i < 9; i++){
        if(p->inv_ch[i]==c) return 1;
    }
    return 0;
}

void change_inv_sel_item(player_t * p, enum direction d){
    switch(d){
        case left: {
            p->active_slot--;
            if(p->active_slot<0) p->active_slot=8;
        } break;
        case right: {
            p->active_slot++;
            if(p->active_slot>8) p->active_slot=0;
        } break;
    }
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

void inventory_remove(player_t *p, int amount){
    p->inv_count[p->active_slot]-=amount;
    if(p->inv_count[p->active_slot]<=0){
        p->inv_count[p->active_slot]=0;
        p->inv_ch[p->active_slot]=0;
    }
}

int place_inv_tile(player_t *p, enum direction d){
    v2i_t tilepos = p->pos;
    switch(d){
        case up: tilepos.y--; break;
        case down: tilepos.y++; break;
        case left: tilepos.x--; break;
        case right: tilepos.x++; break;
    }
    if(tilepos.x<0 ||tilepos.x>=BIOMEWIDTH ||tilepos.y<0 ||tilepos.y>=BIOMEHEIGHT) return 0;
    switch(active_item(p)){
        case 'W': world_set_tile(tilepos, 'W'); inventory_remove(p, 1); return 1; break;
        default: return 0; break;
    }
}

void inventory_print(player_t * p){
    printf("%*s", BIOMEWIDTH/2 - 15, "");
    for(int i = 0; i < 9; i++){
        putc(' ', stdout);
        putc(' ', stdout);
        if(i == p->active_slot) {
            if(p->inv_ch[i]) printf(TEXT_UNDERLINED("%c"), p->inv_ch[i]);
            else putc('_', stdout);
        }
        else{
            if(p->inv_ch[i]) putc( p->inv_ch[i], stdout);
            else putc(' ', stdout);
        }
    }
    putc('\n', stdout);
    printf("%*s", BIOMEWIDTH/2 - 15, "");
    for(int i = 0; i < 9; i++){
        printf("%3d", p->inv_count[i]);
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
            if(active_item(p) == 'A' || rng()<=0.15){
                if (inventory_add(p, 'W', 1)){
                    world_set_tile(tilepos, 'g');
                    return 1;
                }
                world_set_tile(tilepos, 'W');
            } 
        } break;
        case 'W': {
            if(active_item(p) == 'A'){
                if (inventory_add(p, 'W', 1)){
                    world_set_tile(tilepos, 'g');
                    return 1;
                }
            }
        } break;
            
        
    }
    return 0;
}

int tile_walkable(v2i_t tile_pos){
    char tile;
    tile = world_get_tile(tile_pos);
    switch (tile) {
        case 't':
        case 'r':
        case 'W':
            return 0; break;
        default: return 1; break;
    }
}

int player_move_left(player_t *p){
    if(place_inv_tile(p, left)) return 0;
    p->pos.x--;
    if(!tile_walkable(p->pos)){
        p->pos.x++;
        break_tile(left, p);
    }
    if(p->pos.x < 0){
        p->pos.x=BIOMEWIDTH-1;
        return 1;
    }
    return 0;
}
int player_move_right(player_t *p){
    if(place_inv_tile(p, right)) return 0;
    p->pos.x++;
    if(!tile_walkable(p->pos)){
        p->pos.x--;
        break_tile(right, p);
    }
    if(p->pos.x > BIOMEWIDTH-1){
        p->pos.x=0;
        return 1;
    }
    return 0;
}
int player_move_up(player_t *p){
    if(place_inv_tile(p, up)) return 0;
    p->pos.y--;
    if(!tile_walkable(p->pos)){
        p->pos.y++;
        break_tile(up, p);
    }
    if(p->pos.y < 0){
        p->pos.y = BIOMEHEIGHT-1;
        return 1;
    }
    return 0;
}
int player_move_down(player_t *p){
    if(place_inv_tile(p, down)) return 0;
    p->pos.y++;
    if(!tile_walkable(p->pos)){
        p->pos.y--;
        break_tile(down, p);
    }
    if(p->pos.y > BIOMEHEIGHT-1){
        p->pos.y = 0;
        return 1;
    }
    return 0;
}