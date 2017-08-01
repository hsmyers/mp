//
// cspace.h
//
#ifndef CSPACE_H_   /* Include guard */
#define CSPACE_H_
#include "palette.h"

typedef struct {
    double H;
    double S;
    double V;
} HSV;

Rgb HSVToRGB( HSV hsv );
HSV RGBToHSV( Rgb rgb );
HSV GiveHSV( double complex z );
float calcDistance( float a, float b );

#endif // CSPACE_H_