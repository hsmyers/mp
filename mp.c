//
// mp.c - An OpenMP Mandelbrot
//
// compile: gcc -Wall -o mp -std=c99 -O3 -msse2 -march=native -fopenmp cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
//          gcc -ggdb -Wall -o mp -std=c99 -msse2 -march=native -fopenmp cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd
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
#include <quadmath.h>
#include <limits.h>
#include <gd.h>
#include <float.h>
#include "palette.h"
#include "cJSON.h"
#include "elapsed.h"
#include "util.h"
#include "colors.h"

char *Version = "0.015";
char *Date = "Sat Jul 15 07:51:21 2017";

enum {
    FLT,
    DBL,
    LDBL,
    FLT128,
    FLTMPC,
    NOTYET
};

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

typedef struct {
    double H;
    double S;
    double V;

} HSV;

typedef struct timespec time_spec;

Array colors;
gdImagePtr im;

/* *INDENT-OFF* */

__float128 fabsq( __float128 x );
AxesDBL ct_gain_axesDBL( double real, double imag, double diameter, int height, int width );
AxesFLT ct_gain_axesFLT( float real, float imag, float diameter, int height, int width );
AxesFLT128 ct_gain_axesFLT128( __float128 real, __float128 imag, __float128 diameter, int height, int width );
AxesLDBL ct_gain_axesLDBL( long double real, long double imag, long double diameter, int height, int width );
char *guessStr( int g );
double scaleWidth( double d, int N, double E );
int bestGuess( double diameter, int W );
int rgb2int( Rgb color );
Parameters zeroP( void );
void msetDBL( Parameters g );
void msetFLT( Parameters g );
void msetFLT128( Parameters g );
void msetLDBL( Parameters g );

 /* *INDENT-ON* */

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
    Parameters g = zeroP();
    char buffer[100];

    if ( argc >= 3 && argc <= 7 ) {
        char *json = ReadFile( argv[1] );
        g.filename = argv[2];
        if ( json != NULL ) {
            cJSON *root = cJSON_Parse( json );
            cJSON *params = cJSON_GetObjectItemCaseSensitive( root, "params" );
            cJSON *centerX_item = cJSON_GetObjectItemCaseSensitive( params, "centerX" );
            if ( cJSON_IsString( centerX_item ) ) {
                strcpy( buffer, centerX_item->valuestring );
                g.centerX = strtold( buffer, NULL );
            } else if ( cJSON_IsNumber( centerX_item ) ) {
                g.centerX = centerX_item->valuedouble;
            }
            cJSON *centerY_item = cJSON_GetObjectItemCaseSensitive( params, "centerY" );
            if ( cJSON_IsString( centerY_item ) ) {
                strcpy( buffer, centerY_item->valuestring );
                g.centerY = strtold( buffer, NULL );
            } else if ( cJSON_IsNumber( centerY_item ) ) {
                g.centerY = centerY_item->valuedouble;
            }
            cJSON *magnify_item = cJSON_GetObjectItemCaseSensitive( params, "magnify" );
            if ( cJSON_IsString( magnify_item ) ) {
                strcpy( buffer, magnify_item->valuestring );
                g.diameter = strtold( buffer, NULL );
            } else if ( cJSON_IsNumber( magnify_item ) ) {
                g.diameter = magnify_item->valuedouble;
            }
            cJSON *maxIterations_item = cJSON_GetObjectItemCaseSensitive( params, "maxIterations" );
            if ( cJSON_IsNumber( maxIterations_item ) )
                g.maxiter = ( long ) maxIterations_item->valuedouble;
            cJSON *width_item = cJSON_GetObjectItemCaseSensitive( params, "width" );
            if ( cJSON_IsNumber( width_item ) )
                g.width = ( int ) width_item->valuedouble;
            cJSON *height_item = cJSON_GetObjectItemCaseSensitive( params, "height" );
            if ( cJSON_IsNumber( height_item ) )
                g.height = ( int ) height_item->valuedouble;
            cJSON_Delete( root );
            free( json );
            if ( argc >= 4 ) {
                g.color = atoi( argv[3] );
            }
            if ( argc >= 5 ) {
                g.tweak = atoi( argv[4] );
            }
            if ( argc >= 6 ) {
                g.aa = true;
                g.file2name = argv[5];
            }
        } else {
            printf( "error in JSON parameter file: %s\n", argv[1] );
            return 1;
        }
    } else if ( argc >= 8 ) {
        g.centerX  = strtold( argv[1], NULL );
        g.centerY  = strtold( argv[2], NULL );
        g.diameter = strtold( argv[3], NULL );
        g.maxiter  = atol( argv[4] );
        g.width    = atol( argv[5] );
        g.height   = atol( argv[6] );
        g.filename = argv[7];
        if ( argc >= 9 ) {
            g.color = atoi( argv[8] );
        }
        if ( argc >= 10 ) {
            g.tweak = atoi( argv[9] );
        }
        if ( argc >= 11 ) {
            g.aa = true;
            g.file2name = argv[10];
        }

    } else {
        printf( "Usage: either a JSON parameter filename and output file,\n" );
        printf( "    or the above with the name of an anti-aliased file,\n" );
        printf( "    or 7 parameters:\n" );
        printf( "\n" );
        printf( "    center X parameter\n" );
        printf( "    center Y parameter\n" );
        printf( "    diameter parameter\n" );
        printf( "    iteration parameter\n" );
        printf( "    width parameter\n" );
        printf( "    height parameter\n" );
        printf( "    output filename\n" );
        return 1;
    }
    struct timeval tvBegin, tvEnd, tvDiff;

    gettimeofday( &tvBegin, NULL );
    int guess = bestGuess( g.diameter, g.width );
    printf( "%s-diameter:%.17Lg, dims: %dx%d %s color=%d, tweak=%d aa=%d\n", guessStr( guess ),
            ( long double ) g.diameter, g.width, g.height, g.filename, g.color, g.tweak, g.aa );
    switch ( guess ) {
        case FLT:
            msetFLT( g );
            break;
        case DBL:
            msetDBL( g );
            break;
        case LDBL:
            msetLDBL( g );
            break;
        case FLT128:
            msetFLT128( g );
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
        printf( "Convolving image...\n" );
        gdImageConvolution( im, hpf_filter_3, 0.75, 0.5 );
        FILE *cfp = fopen( g.file2name, "wb" );
        gdImageJpeg( im, cfp, 95 );
        fclose( cfp );
    }
    gdImageDestroy( im );
    return 0;
}

double scaleWidth( double d, int N, double E ) {
    return ( double ) ( ( d * N ) / ( 2 * E ) );
}

int bestGuess( double diameter, int W ) {
    if ( diameter > scaleWidth( FLT_EPSILON, W, 0.01 ) ) {
        return FLT;
    } else if ( diameter > scaleWidth( DBL_EPSILON, W, 0.01 ) ) {
        return DBL;
    } else if ( diameter > scaleWidth( LDBL_EPSILON, W, 0.01 ) ) {
        return LDBL;
    } else if ( diameter > scaleWidth( FLT128_EPSILON, W, 0.01 ) ) {
        return FLT128;
    } else {
        return NOTYET;
    }
}

char *guessStr( int g ) {
    static char *s;

    switch ( g ) {
        case FLT:
            s = "FLT";
            break;
        case DBL:
            s = "DBL";
            break;
        case LDBL:
            s = "LDBL";
            break;
        case FLT128:
            s = "FLT128";
            break;
        case FLTMPC:
            s = "FLTMPC";
            break;
        case NOTYET:
            s = "NOTYET";
            break;
        default:
            s = "UNK";
            break;
    }
    return s;
}

void msetFLT( Parameters g ) {
    im = gdImageCreateTrueColor( g.width, g.height );
    AxesFLT ctaxes = ct_gain_axesFLT( g.centerX, g.centerY, g.diameter, g.height, g.width );
#pragma omp parallel shared(im)
    {
        int Y;
#pragma omp for schedule(dynamic)
        for ( Y = 0; Y < g.height; Y++ ) {
            double Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            int X;
            for ( X = 0; X < g.width; X++ ) {
                float Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                float Zx = 0.0;
                float Zy = 0.0;
                float Zx2;
                float Zy2;
                float colorPoly = 0;
                int Iteration;

                for ( Iteration = 0; Iteration < g.maxiter; Iteration++ ) {
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                    if ( ( Zx2 + Zy2 ) > 4.0 )
                        break;
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                }
                if ( g.color > 2 ) {
                    complex C = Cx + Cy * I;
                    complex Z = Zx + Zy * I;
                    colorPoly = getCColorFLT( Z, C, Iteration, g );
                }
                gdImageSetPixel( im, X, Y,
                                 rgb2int( getColorFLT( colorPoly, g.color, Iteration, g.maxiter ) ) );
            }
        }
    }
}

void msetDBL( Parameters g ) {
    im = gdImageCreateTrueColor( g.width, g.height );
    AxesDBL ctaxes = ct_gain_axesDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
#pragma omp parallel shared(im)
    {
        int Y;
#pragma omp for schedule(dynamic)
        for ( Y = 0; Y < g.height; Y++ ) {
            double Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            int X;
            for ( X = 0; X < g.width; X++ ) {
                double Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                double Zx = 0.0;
                double Zy = 0.0;
                double Zx2;
                double Zy2;
                double colorPoly = 0;
                int Iteration;

                for ( Iteration = 0; Iteration < g.maxiter; Iteration++ ) {
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                    if ( ( Zx2 + Zy2 ) > 4.0 )
                        break;
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                }
                if ( g.color > 2 ) {
                    double complex C = Cx + Cy * I;
                    double complex Z = Zx + Zy * I;
                    colorPoly = getCColorDBL( Z, C, Iteration, g );
                }
                gdImageSetPixel( im, X, Y,
                                 rgb2int( getColorDBL( colorPoly, g.color, Iteration, g.maxiter ) ) );
            }
        }
    }
}

void msetLDBL( Parameters g ) {
    im = gdImageCreateTrueColor( g.width, g.height );
    AxesLDBL ctaxes = ct_gain_axesLDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
#pragma omp parallel shared(im)
    {
        int Y;
#pragma omp for schedule(dynamic)
        for ( Y = 0; Y < g.height; Y++ ) {
            long double Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            int X;
            for ( X = 0; X < g.width; X++ ) {
                long double Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                long double Zx = 0.0;
                long double Zy = 0.0;
                long double Zx2;
                long double Zy2;
                long double colorPoly = 0;
                int Iteration;

                for ( Iteration = 0; Iteration < g.maxiter; Iteration++ ) {
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                    if ( ( Zx2 + Zy2 ) > 4.0 )
                        break;
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                }
                if ( g.color > 2 ) {
                    long double complex C = Cx + Cy * I;
                    long double complex Z = Zx + Zy * I;
                    colorPoly = getCColorLDBL( Z, C, Iteration, g );
                }
                gdImageSetPixel( im, X, Y,
                                 rgb2int( getColorLDBL( colorPoly, g.color, Iteration, g.maxiter ) ) );
            }
        }
    }
}

void msetFLT128( Parameters g ) {
    im = gdImageCreateTrueColor( g.width, g.height );
    AxesFLT128 ctaxes = ct_gain_axesFLT128( g.centerX, g.centerY, g.diameter, g.height, g.width );
#pragma omp parallel shared(im)
    {
        int Y;
#pragma omp for schedule(dynamic)
        for ( Y = 0; Y < g.height; Y++ ) {
            __float128 Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
            int X;
            for ( X = 0; X < g.width; X++ ) {
                __float128 Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
                __float128 Zx = 0.0;
                __float128 Zy = 0.0;
                __float128 Zx2;
                __float128 Zy2;
                __float128 colorPoly = 0;
                int Iteration;

                for ( Iteration = 0; Iteration < g.maxiter; Iteration++ ) {
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                    if ( ( Zx2 + Zy2 ) > 4.0 )
                        break;
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                }
                if ( g.color > 2 ) {
                    __complex128 C = Cx + Cy * I;
                    __complex128 Z = Zx + Zy * I;
                    colorPoly = getCColor128( Z, C, Iteration, g );
                }
                gdImageSetPixel( im, X, Y,
                                 rgb2int( getColor128( colorPoly, g.color, Iteration, g.maxiter ) ) );
            }
        }
    }
}

AxesFLT ct_gain_axesFLT( float real, float imag, float diameter, int height, int width ) {
    float radius = diameter / 2.0;
    AxesFLT ctaxes = {
        real - radius,
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
        real - radius,
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
        real - radius,
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
        real - radius,
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

int rgb2int( Rgb color ) {
    return ( color.r * 256 * 256 ) + ( color.g * 256 ) + color.b;
}

__float128 fabsq( __float128 x ) {
    if ( x < 0 ) {
        x *= -1.0;
    }
    return x;
}
