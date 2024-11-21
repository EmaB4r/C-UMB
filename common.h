#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#ifdef DEBUG
    #define debpr(fmt, ...) printf(fmt, ##__VA_ARGS__);
#else
    #define debpr(fmt, ...)
#endif

// returns a value between 0 and 1
double rng();


#endif