#include "world.h"
#include "terminal-graphics/Graphics.h"


int curr_biome_r=HEIGHT/2;
int curr_biome_c=WIDTH/2;

canvas_t world[HEIGHT][WIDTH]={0};


double rng(){
    return (double) rand()/RAND_MAX;
}

void world_create_biome(){
    world[curr_biome_r][curr_biome_c] = canvas_init(BIOMEHEIGHT, BIOMEWIDTH); 
    canvas_draw_arectangle(&world[curr_biome_r][curr_biome_c],
        (v2i_t) {0,0}, (v2i_t) {BIOMEWIDTH-1, BIOMEHEIGHT-1}, 'g', (color_t) {40, 200, 30}, (color_t) {30, 30, 30}, 1);
    srand(time(NULL));
    double d;
    for(int i = 0; i < BIOMEHEIGHT; i++){
        for(int j = 0; j< BIOMEWIDTH; j++){
            d=rng();
            if(d <= 0.2){
                canvas_draw_apixel(&world[curr_biome_r][curr_biome_c],
                    (v2i_t) {j, i}, 
                    'w', (color_t) {60, 60, 190}, (color_t) {30, 30, 30});
            }
            else if (d>=0.94){
                canvas_draw_apixel(&world[curr_biome_r][curr_biome_c], 
                    (v2i_t) {j, i}, 
                    't', (color_t) {90, 70, 50}, (color_t) {30, 30, 30});
            }
        }
    }
}

canvas_t * world_get_curr_biome(){
    return & world[curr_biome_r][curr_biome_c];
}

v2i_t world_get_curr_biome_coord(){
    return (v2i_t){curr_biome_c, curr_biome_r};
}

canvas_t world_get_left_biome(){
    curr_biome_c--;
    if(world[curr_biome_r][curr_biome_c].height==0){
        world_create_biome();
    }
    return world[curr_biome_r][curr_biome_c];
}
canvas_t world_get_right_biome(){
    curr_biome_c++;
    if(world[curr_biome_r][curr_biome_c].height==0){
        world_create_biome();
    }
    return world[curr_biome_r][curr_biome_c];
}
canvas_t world_get_up_biome(){
    curr_biome_r--;
    if(world[curr_biome_r][curr_biome_c].height==0){
        world_create_biome();
    }
    return world[curr_biome_r][curr_biome_c];
}
canvas_t world_get_down_biome(){
    curr_biome_r++;
    if(world[curr_biome_r][curr_biome_c].height==0){
        world_create_biome();
    }
    return world[curr_biome_r][curr_biome_c];
}