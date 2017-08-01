/**
 **  @file palette.h
 **  @author Hugh S. Myers
 **  @brief Declarations and typedefs used for palettes.
 **  @date Mon Jul 24 16:55:30 2017
 **
 **  Origin for Rgb and Array types as well as function declarations.
 **
 **  @bug No known bugs.
 **/
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

Array getColors( char *palname );
Array setColors( Parameters p );
void freeArray( Array *a );
void initArray( Array *a, size_t initialSize );
void insertArray( Array *a, Rgb element );

#endif // PALETTE_H_