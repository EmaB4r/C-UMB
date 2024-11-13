#include "player.h"
#include "world.h"


int player_move_left(player_t *p){
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