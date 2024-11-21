#include "common.h"

int rnginit=0;

double rng(){
    if(!rnginit) {srand(time(NULL)); rnginit=1;}
    return (double) rand()/RAND_MAX;
}