/**
 **  @file palette.h
 **  @author Hugh S. Myers
 **  @brief A collection of functions in aid of palette instantiation, manipulation, and deletion.
 **  @date Sat Aug 12 07:32:49 2017
 **
 **  @section DESCRIPTION
 **
 **  palettes (color arrays) are collections of Rgb values and the associated functions here
 **  are the ways the palettes are used.
 **
 **  @bug No known bugs.
 **/
#ifndef _PALETTE_H   /* Include guard */
#define _PALETTE_H
#include <complex.h>
#include "getopt.h"

#define PPMREADBUFLEN 256

/**
 *  The RGB color model is an additive color model in which red, green
 *  and blue light are added together in various ways to reproduce a broad
 *  array of colors. Stored as unsigned char (numbers in the range 0 to 255), the
 *  range that a single 8-bit byte can offer.
 *  <a href="https://en.wikipedia.org/wiki/RGB_color_model">See Wikipedia RGB article</a>
 */
typedef struct  {
    unsigned char r; /**< RED color, range [0..255] */
    unsigned char g; /**< GREEN color, range [0..255] */
    unsigned char b; /**< BLUE color, range [0..255] */
} Rgb;

/**
 *  Dynamic array typedef and structure.
 */
typedef struct {
    Rgb *array; /**< Internal pointer to array content */
    size_t used; /**< Count of items in array */
    size_t size; /**< sizeof item stored * allocated */
} Array;

Array buildColors( Parameters p );
Array fromStart2Finish( Rgb start, Rgb finish, int N );
Array getColors( char *palname );
Array readColors( char *filename );
Array setColors( Parameters p );
Rgb parseRGB( char *s, int *n );
void appendColors( Rgb a, Rgb b, int interval, Array *color );
void freeArray( Array *a );
void initArray( Array *a, size_t initialSize );
void insertArray( Array *a, Rgb element );
void writeColors( Array colors, char *filename );

#endif // _PALETTE_H