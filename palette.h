//
// palette.h
//
#ifndef PALETTE_H_   /* Include guard */
#define PALETTE_H_
#include <complex.h>
#include "getopt.h"

typedef struct  {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Rgb;

typedef struct {
    Rgb *array;
    size_t used;
    size_t size;
} Array;

void initArray( Array *a, size_t initialSize );
void insertArray( Array *a, Rgb element );
void freeArray( Array *a );
Array getColors( char *palname );
Array setColors( Parameters p );

#endif // PALETTE_H_