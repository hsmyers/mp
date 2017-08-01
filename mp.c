//
// mp.c - An OpenMP Mandelbrot
//
// compile: gcc -Wall -o mp -std=c99 -O3 -msse2 -march=native -fopenmp cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
//          gcc -ggdb -Wall -o mp -std=c99 -msse2 -march=native -fopenmp cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
// debug:   gdb -args …
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <gd.h>
#include "palette.h"
#include "elapsed.h"
#include "colors.h"
#include "getopt.h"
#include "util.h"

char *Version = "0.022";
char *Date = "Tue Aug 01 14:25:14 2017";

typedef struct timespec time_spec;

Array colors;
gdImagePtr im;

Parameters msetDBL( Parameters g );
Parameters msetFLT( Parameters g );
Parameters msetFLT128( Parameters g );
Parameters msetLDBL( Parameters g );

float gauss_kernel[3][3] = {
    {1.0, 2.0, 1.0},
    {2.0, 4.0, 2.0},
    {1.0, 2.0, 1.0}
};

float lpf_filter_6[3][3] = {
    {0.0, 1.0, 0.0},
    {1.0, 2.0, 1.0},
    {0.0, 1.0, 0.0}
};

float lpf_filter_9[3][3] = {
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0}
};

float lpf_filter_10[3][3] = {
    {1.0, 1.0, 1.0},
    {1.0, 2.0, 1.0},
    {1.0, 1.0, 1.0}
};

float lpf_filter_16[3][3] = {
    {1.0, 2.0, 1.0},
    {2.0, 4.0, 2.0},
    {1.0, 2.0, 1.0}
};

float lpf_filter_32[3][3] = {
    {1.0, 4.0, 1.0},
    {4.0, 12.0, 4.0},
    {1.0, 4.0, 1.0}
};

float hpf_filter_1[3][3] = {
    {0.0, -1.0, 0.0},
    {-1.0, 5.0, -1.0},
    {0.0, -1.0, 0.0}
};

float intensified_sharpen_kernel[3][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 8.0, -1.0},
    {-1.0, -1.0, -1.0}
};

float hpf_filter_2[3][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 9.0, -1.0},
    {-1.0, -1.0, -1.0}
};

float hpf_filter_3[3][3] = {
    {1.0, -2.0, 1.0},
    {-2.0, 5.0, -2.0},
    {1.0, -2.0, 1.0}
};

int main( int argc, char *argv[] ) {
    Parameters g = getParameters( argc, argv, Version, Date );
    struct timeval tvBegin, tvEnd, tvDiff;

    if ( g.palname ) {
        if ( strncmp( g.palname, "SET", 3 ) == 0 ) {
            colors = setColors( g );
        } else {
            colors = getColors( g.palname );
        }
    }
    gettimeofday( &tvBegin, NULL );
    int guess = bestGuess( g.diameter, g.width );
    printf( "%s vr%s\n", argv[0], Version );
    printf( "%s-diameter:%.17Lg, dims: %dx%d %s color=%d, tweak=%d aa=%s\n", guessStr( guess ),
            ( long double ) g.diameter, g.width, g.height, g.filename, g.color, g.tweak, g.aa );
    timeval_print( &tvBegin );
    switch ( guess ) {
        case FLT:
            g = msetFLT( g );
            break;
        case DBL:
            g = msetDBL( g );
            break;
        case LDBL:
            g = msetLDBL( g );
            break;
        case FLT128:
            g = msetFLT128( g );
            break;
        default:
            printf( "Need higher precision\n" );
            return 1;
            break;
    }
    gettimeofday( &tvEnd, NULL );
    timeval_subtract( &tvDiff, &tvEnd, &tvBegin );
    elapsed( tvDiff.tv_sec, tvDiff.tv_usec );
    timeval_print( &tvEnd );
    FILE *fp = fopen( g.filename, "wb" );
    gdImageJpeg( im, fp, 95 );
    fclose( fp );
    if ( g.aa ) {
        printf( "Convolving image to %s...\n", g.aa );
        gdImageConvolution( im, hpf_filter_1, 0.75, 0.5 );
        FILE *cfp = fopen( g.aa, "wb" );
        gdImageJpeg( im, cfp, 95 );
        fclose( cfp );
    }
    gdImageDestroy( im );
    if ( g.palname )
        freeArray( &colors );
    printf( "maxiter = '%d', nMax = '%d'\n", g.maxiter, g.nMax );
    printf( "——————————————————————————————\n" );
    return 0;
}

Parameters msetFLT( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorFLT cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
            float y = ( Y - g.height2 ) / ( g.height2 );
            for (int X = 0; X < g.width; X++ ) {
                float x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    cp.Z = cp.Z * cp.Z + cp.C;
                    cp.Exps = cabs( cp.Z );
                    if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                        break;
                }
                if ( cp.n < g.maxiter ) {
                    g.nMax = max( cp.n, g.nMax );
                }
                gdImageSetPixel( im, X, Y, getfColorFLT( g, cp ) );
            }
        }
    }
    return g;
}

Parameters msetDBL( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorDBL cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
            double y = ( Y - g.height2 ) / ( g.height2 );
            for (int X = 0; X < g.width; X++ ) {
                double x = ( X - g.width2 ) / ( g.height2 );
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;
                cp.colorPoly = 0;
                cp.Exps = 0;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    cp.Z = cp.Z * cp.Z + cp.C;
                    cp.Exps = cabs( cp.Z );
                    if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                        break;
                }
                if ( cp.n < g.maxiter ) {
                    g.nMax = max( cp.n, g.nMax );
                }
                gdImageSetPixel( im, X, Y, getfColorDBL( g, cp ) );
            }
        }
    }
    return g;
}

Parameters msetLDBL( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorLDBL cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
            long double y = ( Y - g.height2 ) / ( g.height2 );
            for (int X = 0; X < g.width; X++ ) {
                long double x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    cp.Z = cp.Z * cp.Z + cp.C;
                    cp.Exps = cabs( cp.Z );
                    if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                        break;
                }
                if ( cp.n < g.maxiter ) {
                    g.nMax = max( cp.n, g.nMax );
                }
                gdImageSetPixel( im, X, Y, getfColorLDBL( g, cp ) );
            }
        }
    }
    return g;
}

Parameters msetFLT128( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        Color128 cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
            __float128 y = ( Y - g.height2 ) / ( g.height2 );
            for (int X = 0; X < g.width; X++ ) {
                __float128 x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    cp.Z = cp.Z * cp.Z + cp.C;
                    cp.Exps = cabs( cp.Z );
                    if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                        break;
                }
                if ( cp.n < g.maxiter ) {
                    g.nMax = max( cp.n, g.nMax );
                }
                gdImageSetPixel( im, X, Y, getfColor128( g, cp ) );
            }
        }
    }
    return g;
}
