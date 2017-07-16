//
// colors.h
//
#ifndef colors_H_   /* Include guard */
#define colors_H_
#include <quadmath.h>
#include "palette.h"
#include "getopt.h"

extern Array colors;

__float128 getCColor128( __complex128 Z, __complex128 C, unsigned int n, Parameters P );
Rgb getColor128( __float128 colorPoly, int rgb, int n, int maxiter );
Rgb getRgbSmoothCP128( __float128 cp, int count, int MaxCount );

long double getCColorLDBL( long double complex Z, long double complex C,unsigned int n, Parameters P );
Rgb getColorLDBL( long double colorPoly, int rgb, int n, int maxiter );
Rgb getRgbSmoothCPLDBL( long double cp, int count, int MaxCount );

double getCColorDBL( double complex Z, double complex C,unsigned int n, Parameters P );
Rgb getColorDBL( double colorPoly, int rgb, int n, int maxiter );
Rgb getRgbSmoothCPDBL( double cp, int count, int MaxCount );

float getCColorFLT( float complex Z, float complex C,unsigned int n, Parameters P );
Rgb getColorFLT( float colorPoly, int rgb, int n, int maxiter );
Rgb getRgbSmoothCPFLT( float cp, int count, int MaxCount );

Rgb getRgb( int count, int MaxCount );
Rgb getRgb2( int count, int MaxCount );
Rgb getRgb3( int count, int MaxCount );
Rgb getRgbFromTable( int count, int MaxCount );
Rgb getRgbSmooth( int count, int MaxCount );

#endif // colors_H_