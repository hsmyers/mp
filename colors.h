//
// colors.h
//
#ifndef colors_H_   /* Include guard */
#define colors_H_
#include <quadmath.h>
#include "palette.h"
#include "getopt.h"

extern Array colors;

typedef struct {
    float Zx;
    float Zy;
    float Cx;
    float Cy;
    float colorPoly;
    float Exps;
    int n;
} ColorFLT;

typedef struct {
    double Zx;
    double Zy;
    double Cx;
    double Cy;
    double colorPoly;
    double Exps;
    int n;
} ColorDBL;

typedef struct {
    long double Zx;
    long double Zy;
    long double Cx;
    long double Cy;
    long double colorPoly;
    long double Exps;
    int n;
} ColorLDBL;

typedef struct {
    __float128 Zx;
    __float128 Zy;
    __float128 Cx;
    __float128 Cy;
    __float128 colorPoly;
    __float128 Exps;
    int n;
} Color128;

__float128 getCColor128( __complex128 Z, __complex128 C, unsigned int n, Parameters P );
double getCColorDBL( double complex Z, double complex C,unsigned int n, Parameters P );
float getCColorFLT( float complex Z, float complex C,unsigned int n, Parameters P );
int fractionCount( int n, int max );
int getfColorFLT( Parameters g, ColorFLT c );
int getfColorDBL( Parameters g, ColorDBL c );
int getfColorLDBL( Parameters g, ColorLDBL c );
int getfColor128( Parameters g, Color128 c );
int rgb2int( Rgb color );
long double getCColorLDBL( long double complex Z, long double complex C,unsigned int n, Parameters P );
Rgb getBersteinFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBerstein128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_amp );
Rgb getColor128( __float128 colorPoly, int rgb, int n, int maxiter );
Rgb getColorDBL( double colorPoly, int rgb, int n, int maxiter );
Rgb getColorFLT( float colorPoly, int rgb, int n, int maxiter );
Rgb getColorLDBL( long double colorPoly, int rgb, int n, int maxiter );
Rgb getRgb( int count, int MaxCount );
Rgb getRgb2( int count, int MaxCount );
Rgb getRgb3( int count, int MaxCount );
Rgb getRgb4( int count, int MaxCount );
Rgb getRgb5( int count, int MaxCount );
Rgb getRgbFromTable( int count, int MaxCount );
Rgb getRgbSmooth( int count, int MaxCount );
Rgb getRgbSmoothCP128( __float128 cp, int count, int MaxCount );
Rgb getRgbSmoothCPDBL( double cp, int count, int MaxCount );
Rgb getRgbSmoothCPFLT( float cp, int count, int MaxCount );
Rgb getRgbSmoothCPLDBL( long double cp, int count, int MaxCount );
void setRgb( Rgb *a, Rgb *b, Parameters p );
void cpyRgb( Rgb source, Rgb *dest );

#endif // colors_H_