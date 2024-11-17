#include "player.h"
#include "terminal-graphics/Graphics.h"
#include "terminal-graphics/ansi-terminal/Ansi.h"
#include "world.h"
#include <complex.h>

#define debpr(fmt, ...) printf(fmt, ##__VA_ARGS__);

player_t P={0};

void handle_input(unsigned char key){
    switch (key) {
        case 0: break;
        case 'w': if(player_move_up(&P))world_get_up_biome(); break;
        case 'a': if(player_move_left(&P))world_get_left_biome(); break;
        case 's': if(player_move_down(&P))world_get_down_biome(); break;
        case 'd': if(player_move_right(&P))world_get_right_biome(); break;
    }
}

int main(){
    
    unsigned char key;
    P.pos.x=BIOMEWIDTH/2;
    P.pos.y=BIOMEHEIGHT/2;
    inventory_add(&P, 'a', 1);
    world_create_biome();
    canvas_t * Map;
    canvas_t GameCanvas = canvas_init(BIOMEHEIGHT, BIOMEWIDTH);
    SCREEN_LOOP(50, {
        Map = world_get_curr_biome();
        canvas_copy(&GameCanvas, Map);
        key=getkey(stdin);
        handle_input(key);
        canvas_draw_apixel(&GameCanvas, P.pos, 'P', (color_t){200, 200, 200}, (color_t){30, 30, 30});
        canvas_ashow(GameCanvas);
        debpr(TEXT_WHYTE("\n"));
        inventory_print(&P);
        debpr("PLAYER COORDS { %d ; %d }    \n", P.pos.x, P.pos.y);
        debpr("WORLD COORDS { %d ; %d }    \n", world_get_curr_biome_coord().x, world_get_curr_biome_coord().y);
        debpr((key == 0) ? "Current key: none\n": "Current key: %c     \n", key);
    });
    return 0;
}