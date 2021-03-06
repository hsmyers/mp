//
// mp.c - An OpenMP Mandelbrot
//
// compile: gcc -Wall -o mp -std=c99 -O3 -msse2 -march=native -fopenmp palette.c dictionary.c iniparser.c getopt.c cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
//          gcc -ggdb -Wall -o mp -std=c99 -msse2 -march=native -fopenmp palette.c dictionary.c iniparser.c getopt.c cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
// debug:   gdb -args …
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include "palette.h"
#include "colors.h"
#include "getopt.h"
#include "util.h"
#include "mp.h"
#include "elapsed.h"

char *Version = "0.025";
char *Date = "Sat Jul 29 10:20:53 2017";

typedef struct {
    __float128 xmin;
    __float128 xmax;
    __float128 ymin;
    __float128 ymax;
    __float128 ctxfactor;
    __float128 ctyfactor;
} AxesFLT128;

typedef struct {
    long double xmin;
    long double xmax;
    long double ymin;
    long double ymax;
    long double ctxfactor;
    long double ctyfactor;
} AxesLDBL;

typedef struct {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double ctxfactor;
    double ctyfactor;
} AxesDBL;

typedef struct {
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    float ctxfactor;
    float ctyfactor;
} AxesFLT;

AxesFLT ct_gain_axesFLT( float real, float imag, float diameter, int height, int width );
AxesDBL ct_gain_axesDBL( double real, double imag, double diameter, int height, int width );
AxesLDBL ct_gain_axesLDBL( long double real, long double imag, long double diameter, int height, int width );
AxesFLT128 ct_gain_axesFLT128( __float128 real, __float128 imag, __float128 diameter, int height, int width );

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
    AxesFLT ctaxes = ct_gain_axesFLT( g.centerX, g.centerY, g.diameter, g.height, g.width );
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorFLT cp;
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            for ( int X = 0; X < g.width; X++ ) {
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                cp.Zx = 0.0;
                cp.Zy = 0.0;
                cp.colorPoly = 0;
                cp.Exps = 0;
                float Zx2;
                float Zy2;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    Zx2 = cp.Zx * cp.Zx;
                    Zy2 = cp.Zy * cp.Zy;
                    if ( ( Zx2 + Zy2 ) > g.escape )
                        break;
                    cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                    cp.Zx = Zx2 - Zy2 + cp.Cx;
                    cp.Exps += exp( Zx2 + Zy2 );
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
    AxesDBL ctaxes = ct_gain_axesDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorDBL cp;
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            for ( int X = 0; X < g.width; X++ ) {
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                cp.Zx = 0.0;
                cp.Zy = 0.0;
                cp.colorPoly = 0;
                cp.Exps = 0;
                double Zx2;
                double Zy2;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    Zx2 = cp.Zx * cp.Zx;
                    Zy2 = cp.Zy * cp.Zy;
                    if ( ( Zx2 + Zy2 ) > g.escape )
                        break;
                    cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                    cp.Zx = Zx2 - Zy2 + cp.Cx;
                    cp.Exps += exp( Zx2 + Zy2 );
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
    AxesLDBL ctaxes = ct_gain_axesLDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorLDBL cp;
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            for ( int X = 0; X < g.width; X++ ) {
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                cp.Zx = 0.0;
                cp.Zy = 0.0;
                cp.colorPoly = 0;
                cp.Exps = 0;
                long double Zx2;
                long double Zy2;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    Zx2 = cp.Zx * cp.Zx;
                    Zy2 = cp.Zy * cp.Zy;
                    if ( ( Zx2 + Zy2 ) > g.escape )
                        break;
                    cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                    cp.Zx = Zx2 - Zy2 + cp.Cx;
                    cp.Exps += exp( Zx2 + Zy2 );
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
    AxesFLT128 ctaxes = ct_gain_axesFLT128( g.centerX, g.centerY, g.diameter, g.height, g.width );
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        Color128 cp;
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            for ( int X = 0; X < g.width; X++ ) {
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                cp.Zx = 0.0;
                cp.Zy = 0.0;
                cp.colorPoly = 0;
                cp.Exps = 0;
                __float128 Zx2;
                __float128 Zy2;

                for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                    Zx2 = cp.Zx * cp.Zx;
                    Zy2 = cp.Zy * cp.Zy;
                    if ( ( Zx2 + Zy2 ) > g.escape )
                        break;
                    cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                    cp.Zx = Zx2 - Zy2 + cp.Cx;
                    cp.Exps += exp( Zx2 + Zy2 );
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
AxesFLT ct_gain_axesFLT( float real, float imag, float diameter, int height, int width ) {
    float radius = diameter / 2.0;
    AxesFLT ctaxes = {
        real - diameter,
        real + radius,
        imag - radius,
        imag + radius,
        0.0,
        0.0,
    };
    float ctwidth = ctaxes.xmax - ctaxes.xmin;
    float ctheight = ctaxes.ymax - ctaxes.ymin;
    float ctdaspect = fabsf( ( float ) height / ( float ) width );
    float ctwaspect = fabsf( ctheight / ctwidth );

    if ( ctdaspect > ctwaspect ) {
        float excess = ctheight * ( ctdaspect / ctwaspect - 1 );
        ctaxes.ymax += excess / 2;
        ctaxes.ymin -= excess / 2;
    } else if ( ctdaspect < ctwaspect ) {
        float excess = ctwidth * ( ctwaspect / ctdaspect - 1 );
        ctaxes.xmax += excess / 2;
        ctaxes.xmin -= excess / 2;
    }

    ctwidth = ctaxes.xmax - ctaxes.xmin;
    ctheight = ctaxes.ymax - ctaxes.ymin;
    ctaxes.ctxfactor = ctwidth / ( ( width > 1 ) ? ( width - 1 ) : width );
    ctaxes.ctyfactor = ctheight / ( ( height > 1 ) ? ( height - 1 ) : height );

    return ctaxes;
}

AxesDBL ct_gain_axesDBL( double real, double imag, double diameter, int height, int width ) {
    double radius = diameter / 2.0;
    AxesDBL ctaxes = {
        real - diameter,
        real + radius,
        imag - radius,
        imag + radius,
        0.0,
        0.0,
    };
    double ctwidth = ctaxes.xmax - ctaxes.xmin;
    double ctheight = ctaxes.ymax - ctaxes.ymin;
    double ctdaspect = fabs( ( double ) height / ( double ) width );
    double ctwaspect = fabs( ctheight / ctwidth );

    if ( ctdaspect > ctwaspect ) {
        double excess = ctheight * ( ctdaspect / ctwaspect - 1 );
        ctaxes.ymax += excess / 2;
        ctaxes.ymin -= excess / 2;
    } else if ( ctdaspect < ctwaspect ) {
        double excess = ctwidth * ( ctwaspect / ctdaspect - 1 );
        ctaxes.xmax += excess / 2;
        ctaxes.xmin -= excess / 2;
    }

    ctwidth = ctaxes.xmax - ctaxes.xmin;
    ctheight = ctaxes.ymax - ctaxes.ymin;
    ctaxes.ctxfactor = ctwidth / ( ( width > 1 ) ? ( width - 1 ) : width );
    ctaxes.ctyfactor = ctheight / ( ( height > 1 ) ? ( height - 1 ) : height );

    return ctaxes;
}

AxesLDBL ct_gain_axesLDBL( long double real, long double imag, long double diameter, int height, int width ) {
    long double radius = diameter / 2.0;
    AxesLDBL ctaxes = {
        real - diameter,
        real + radius,
        imag - radius,
        imag + radius,
        0.0,
        0.0,
    };
    long double ctwidth = ctaxes.xmax - ctaxes.xmin;
    long double ctheight = ctaxes.ymax - ctaxes.ymin;
    long double ctdaspect = fabsl( ( long double ) height / ( long double ) width );
    long double ctwaspect = fabsl( ctheight / ctwidth );

    if ( ctdaspect > ctwaspect ) {
        long double excess = ctheight * ( ctdaspect / ctwaspect - 1 );
        ctaxes.ymax += excess / 2;
        ctaxes.ymin -= excess / 2;
    } else if ( ctdaspect < ctwaspect ) {
        long double excess = ctwidth * ( ctwaspect / ctdaspect - 1 );
        ctaxes.xmax += excess / 2;
        ctaxes.xmin -= excess / 2;
    }

    ctwidth = ctaxes.xmax - ctaxes.xmin;
    ctheight = ctaxes.ymax - ctaxes.ymin;
    ctaxes.ctxfactor = ctwidth / ( ( width > 1 ) ? ( width - 1 ) : width );
    ctaxes.ctyfactor = ctheight / ( ( height > 1 ) ? ( height - 1 ) : height );

    return ctaxes;
}

AxesFLT128 ct_gain_axesFLT128( __float128 real, __float128 imag, __float128 diameter, int height, int width ) {
    __float128 radius = diameter / 2.0;
    AxesFLT128 ctaxes = {
        real - diameter,
        real + radius,
        imag - radius,
        imag + radius,
        0.0,
        0.0,
    };
    __float128 ctwidth = ctaxes.xmax - ctaxes.xmin;
    __float128 ctheight = ctaxes.ymax - ctaxes.ymin;
    __float128 ctdaspect = fabsq( ( __float128 ) height / ( __float128 ) width );
    __float128 ctwaspect = fabsq( ctheight / ctwidth );

    if ( ctdaspect > ctwaspect ) {
        __float128 excess = ctheight * ( ctdaspect / ctwaspect - 1 );
        ctaxes.ymax += excess / 2;
        ctaxes.ymin -= excess / 2;
    } else if ( ctdaspect < ctwaspect ) {
        __float128 excess = ctwidth * ( ctwaspect / ctdaspect - 1 );
        ctaxes.xmax += excess / 2;
        ctaxes.xmin -= excess / 2;
    }

    ctwidth = ctaxes.xmax - ctaxes.xmin;
    ctheight = ctaxes.ymax - ctaxes.ymin;
    ctaxes.ctxfactor = ctwidth / ( ( width > 1 ) ? ( width - 1 ) : width );
    ctaxes.ctyfactor = ctheight / ( ( height > 1 ) ? ( height - 1 ) : height );

    return ctaxes;
}
