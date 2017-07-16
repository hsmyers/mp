//
// colors.c
//
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "colors.h"
#include "cspace.h"

const double saturation = 0.90;
const double value = 0.75;
const double rotation = 172.0;

Rgb getColorFLT( float colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPFLT( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColorDBL( double colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPDBL( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColorLDBL( long double colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPLDBL( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColor128( __float128 colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCP128( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        default:
            return getRgb( n, maxiter );
    }
}

long double getCColorLDBL( long double complex Z, long double complex C,unsigned int n, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        Z = Z * Z + C;
        n++;
    }
    switch (P.rgb) {
        case 3:
            return n + 1 - ( log( 2 ) / cabs( Z ) / log( 2 ) );
        case 4:
            return n - ( log( log( cabs( Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + n - log( log( cabs( Z ) ) ) ) / log( ( long double )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( long double )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( long double )P.maxiter );
        case 8:
            return n + 1.5 - log2( log2( cabs( Z ) ) );
        default:
            return 0.0;
    }
}

float getCColorFLT( float complex Z, float complex C,unsigned int n, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        Z = Z * Z + C;
        n++;
    }
    switch (P.rgb) {
        case 3:
            return n + 1 - ( log( 2 ) / cabs( Z ) / log( 2 ) );
        case 4:
            return n - ( log( log( cabs( Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + n - log( log( cabs( Z ) ) ) ) / log( ( float )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( float )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( float )P.maxiter );
        case 8:
            return n + 1.5 - log2( log2( cabs( Z ) ) );
        default:
            return 0.0;
    }
}

double getCColorDBL( double complex Z, double complex C,unsigned int n, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        Z = Z * Z + C;
        n++;
    }
    switch (P.rgb) {
        case 3:
            return n + 1 - ( log( 2 ) / cabs( Z ) / log( 2 ) );
        case 4:
            return n - ( log( log( cabs( Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + n - log( log( cabs( Z ) ) ) ) / log( ( double )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( double )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( double )P.maxiter );
        case 8:
            return n + 1.5 - log2( log2( cabs( Z ) ) );
        default:
            return 0.0;
    }
}

__float128 getCColor128( __complex128 Z, __complex128 C,unsigned int n, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        Z = Z * Z + C;
        n++;
    }
    switch (P.rgb) {
        case 3:
            return n + 1 - ( log( 2 ) / cabs( Z ) / log( 2 ) );
        case 4:
            return n - ( log( log( cabs( Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + n - log( log( cabs( Z ) ) ) ) / log( ( __float128 )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( __float128 )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + n - log2( log2( cabs( Z ) ) ) ) / log2( ( __float128 )P.maxiter );
        case 8:
            return n + 1.5 - log2( log2( cabs( Z ) ) );
        default:
            return 0.0;
    }
}

Rgb getRgb3( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        (count * 6) % 256,
        1,
        1,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb2( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    double hue = fmod( count * 360.0 / MaxCount + rotation, 360.0 );
    HSV rainbow = {
        hue,
        saturation,
        value,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb( int count, int MaxCount ) {
    double hue, f, p, q, t;
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        hue = fmod( count * 360.0 / MaxCount + rotation, 360.0 );
        f = hue / 60 - ( int ) ( hue / 60 );
        p = ( int ) ( value * ( 1 - saturation ) * 255 );
        q = ( int ) ( value * ( 1 - f * saturation ) * 255 );
        t = ( int ) ( value * ( 1 - ( 1 - f ) * saturation ) * 255 );
        switch ( ( int ) ( hue / 60 ) % 6 ) {
        case 0:
            color.r = value;
            color.g = t;
            color.b = p;
            break;
        case 1:
            color.r = q;
            color.g = value;
            color.b = p;
            break;
        case 2:
            color.r = p;
            color.g = value;
            color.b = t;
            break;
        case 3:
            color.r = p;
            color.g = q;
            color.b = value;
            break;
        case 4:
            color.r = t;
            color.g = p;
            color.b = value;
            break;
        case 5:
            color.r = value;
            color.g = p;
            color.b = q;
            break;
        }
    }
    return color;
}

Rgb getRgbFromTable( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color = colors.array[count % colors.size];
    }
    return color;
}

Rgb getRgbSmooth( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        double t = ( double ) count / ( double ) MaxCount;

        color.r = ( unsigned char ) ( 9 * ( 1 - t ) * t * t * t * 255 );
        color.g =
            ( unsigned char ) ( 15 * ( 1 - t ) * ( 1 - t ) * t * t * 255 );
        color.b =
            ( unsigned char ) ( 8.5 * ( 1 - t ) * ( 1 - t ) * ( 1 - t ) *
                                t * 255 );
    }

    return color;
}

Rgb getRgbSmoothCPFLT( float colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r =
            ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g =
            ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b =
            ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCPDBL( double colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r =
            ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g =
            ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b =
            ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCPLDBL( long double colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r =
            ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g =
            ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b =
            ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCP128( __float128 colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r =
            ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g =
            ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b =
            ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}
