//
// colors.h
//
#ifndef _COLORS_H   // Include guard
#define _COLORS_H
#include <quadmath.h>
#include "palette.h"
#include "getopt.h"

extern Array colors;

typedef struct {
    float Zx;
    float Zy;
    float Cx;
    float Cy;
    float Zx2;
    float Zy2;
    float colorPoly;
    float Exps;
    float DistanceMax;
    complex C;
    complex Z;
    int n;
} ColorFLT;

typedef struct {
    double Zx;
    double Zy;
    double Cx;
    double Cy;
    double Zx2;
    double Zy2;
    double complex Z;
    double complex C;
    double colorPoly;
    double Exps;
    double DistanceMax;
    int n;
} ColorDBL;

typedef struct {
    long double Zx;
    long double Zy;
    long double Cx;
    long double Cy;
    long double Zx2;
    long double Zy2;
    long double complex Z;
    long double complex C;
    long double colorPoly;
    long double Exps;
    long double DistanceMax;
    int n;
} ColorLDBL;

typedef struct {
    __float128 Zx;
    __float128 Zy;
    __float128 Cx;
    __float128 Cy;
    __float128 Zx2;
    __float128 Zy2;
    __complex128 Z;
    __complex128 C;
    __float128 colorPoly;
    __float128 Exps;
    __float128 DistanceMax;
    int n;
} Color128;

__float128 getCColor128( Color128 c, Parameters P );
double getCColorDBL( ColorDBL c, Parameters P );
float getCColorFLT( ColorFLT c, Parameters P );
int fractionCount( int n, int max );
int getfColor128( Parameters g, Color128 c );
int getfColorDBL( Parameters g, ColorDBL c );
int getfColorFLT( Parameters g, ColorFLT c );
int getfColorLDBL( Parameters g, ColorLDBL c );
int rgb2int( Rgb color );
double GiveDistanceMax( double PixelWidth, int iSide );
long double getCColorLDBL( ColorLDBL c, Parameters P );
Rgb getBerstein128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_amp );
Rgb getBersteinSineFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase );
Rgb getBersteinSineDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase );
Rgb getBersteinSineLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase );
Rgb getBersteinSine128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase );
Rgb getColor128( __float128 colorPoly, int rgb, int n, int maxiter );
Rgb getColorDBL( double colorPoly, int rgb, int n, int maxiter );
Rgb getColorFLT( float colorPoly, int rgb, int n, int maxiter );
Rgb getColorLDBL( long double colorPoly, int rgb, int n, int maxiter );
Rgb getRgb( int count, int MaxCount );
Rgb getRgb2( int count, int MaxCount );
Rgb getRgb3( int count, int MaxCount );
Rgb getRgb4( int count, int MaxCount );
Rgb getRgb5( int count, int MaxCount );
Rgb getRgb6( int count, int MaxCount, complex Z );
Rgb getRgb7( int count, int MaxCount, complex Z );
Rgb getRgb8( int count, int MaxCount, complex Z );
Rgb getRgb9( int count, int MaxCount, double mu );
Rgb getRgb10( int count, int MaxCount, complex Z );
Rgb getRgb11( int count, int MaxCount, complex Z );
Rgb getRgbFromTable( int count, int MaxCount );
Rgb getRgbSmooth( int count, int MaxCount );
Rgb getRgbSmoothCP128( __float128 cp, int count, int MaxCount );
Rgb getRgbSmoothCPDBL( double cp, int count, int MaxCount );
Rgb getRgbSmoothCPFLT( float cp, int count, int MaxCount );
Rgb getRgbSmoothCPLDBL( long double cp, int count, int MaxCount );
Rgb GiveRainbowColor( double position );
void cpyRgb( Rgb source, Rgb *dest );
void setRgb( Rgb *a, Rgb *b, Parameters p );
void name2Rgb( char *name, Rgb *dest );
void raw2Rgb( char *name, Rgb *dest );

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#define M_2PI (6.28318530717958647692)
#endif

#endif // _COLORS_H