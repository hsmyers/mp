/**
 **  @file mp.c
 **  @author Hugh S. Myers
 **  @brief This is the primary source file for mp.exe
 **  @date Mon Aug 14 10:25:06 2017
 **
 **  @section DESCRIPTION
 **
 **  This is both the location of main() as well as the central file for the executable. Mp.exe is an
 **  OpenMP Mandelbrot image generator. It is designed to be open ended as well as an on-going test bed.
 **  As such not everything may work. You've been warned. Best indicator of something wrong is an image
 **  that is all black. I suppose in keeping with the windows platform, the image should be all blue, but
 **  it is what it is.
 **
 **  @note
 **  compile: gcc -Wall -o mp -std=c99 -O3 -msse2 -march=native -fopenmp cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd<br>
 **           gcc -ggdb -Wall -o mp -std=c99 -msse2 -march=native -fopenmp cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd<br>
 **  debug:   gdb -args …<br>
 **
 **  @bug No known bugs.
 **/
#include "mp.h"

char *Version = "0.029";
char *Date = "Sun Aug 13 20:42:04 2017";

/**
 * @brief main() for mp.exe
 * @details Primary routine for the executable. Acts as information collection point and function dispatcher.
 *
 * @param argc Command line argument count.
 * @param argv Command line argument list.
 *
 * @return Returns EXIT_SUCCESS or EXIT_FAILURE depending.
 */
int main( int argc, char *argv[] ) {
    Parameters g = getParameters( argc, argv, Version, Date );
    struct timeval tvBegin, tvEnd, tvDiff;

    if ( g.nargc ) {
        colors = buildColors( g );
        writeColors( colors, "colors.ppm" );
    } else if ( g.palname ) {
        if ( strncmp( g.palname, "SET", 3 ) == 0 ) {
            colors = setColors( g );
        } else {
            colors = getColors( g.palname );
        }
    }
    gettimeofday( &tvBegin, NULL );
    int guess = bestGuess( g.diameter, g.width );
    signon( argv[0], Version );
    printf( "%s  diameter: %.17Lg, dims: %dx%d %s color=%d, tweak=%d aa=%s\n", guessStr( guess ),
            ( long double ) g.diameter, g.width, g.height, g.filename, g.color, g.tweak, g.aa );
    if ( g.color == 13 ) {
        if ( g.old == DEMM ) {
            printf( "color mode 13 and old mode DEMM not implemented\n" );
            exit( EXIT_FAILURE );
        }
        else {
            if ( g.old == MSETCPM ) {
                printf( "color mode 13 and old mode MSETCPM not implemented\n" );
                exit( EXIT_FAILURE );
            }
        }
    }
    printf
        ( "————————————————————————————————\n" );
    timeval_print( &tvBegin );
    switch ( guess ) {
        case FLT:
            g = MSetFLT( g );
            break;
        case DBL:
            g = MSetDBL( g );
            break;
        case LDBL:
            g = MSetLDBL( g );
            break;
        case FLT128:
            g = MSetFLT128( g );
            break;
        default:
            printf( "Need higher precision\n" );
            exit( EXIT_FAILURE );
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
    if ( colors.size )
        freeArray( &colors );
    printf( "maxiter = '%d', nMax = '%d'\n", g.maxiter, g.nMax );
    printf
        ( "————————————————————————————————\n" );
    return EXIT_SUCCESS;
}

/**
 * @brief Mandelbrot Set using float
 * @details Function to compute the Mandelbrot Set using float variables. This derives an
 *          image g.width × g.height, centered at g.center from g.centerX and g.centerY. The
 *          complex width is g.diameter. The inner loop is available in 4 methods; ZX, meaning
 *          calculate without complex variables, COMPLEX, meaning calculate with complex variables,
 *          DEMM, meaning use the Distance Estimator Method for Mandelbrot set and MSETCPM, meaning
 *          use the Continuous Potential Method.
 *
 *
 * @param P Parameters structure, a collection of configuration information.
 * @return A Parameters structure g, as modified by the function.
 */
Parameters MSetFLT( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorFLT cp;
        cp.DistanceMax = GiveDistanceMax( g.diameter / g.width, g.width );
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            float y = ( Y - g.height2 ) / ( g.height2 );
            for ( int X = 0; X < g.width; X++ ) {
                float x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;
                float zOld;

                if ( g.old == ZX ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp.Zx = 0.0;
                    cp.Zy = 0.0;
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        cp.Zx2 = cp.Zx * cp.Zx;
                        cp.Zy2 = cp.Zy * cp.Zy;
                        if ( ( cp.Zx2 + cp.Zy2 ) > g.escape )
                            break;
                        cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                        cp.Zx = cp.Zx2 - cp.Zy2 + cp.Cx;
                        cp.Exps += exp( cp.Zx2 + cp.Zy2 );
                    }
                    cp.Z = cp.Zx + cp.Zy * I;
                    cp.C = cp.Cx + cp.Cy * I;
                } else if ( g.old == COMPLEX ) {
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        zOld = cp.Z;
                        cp.Z = cp.Z * cp.Z + cp.C;
                        cp.Exps += exp( -cabs( cp.Z ) - 0.5 / ( cabs( zOld - cp.Z ) ) );
                        if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                            break;
                    }
                } else if ( g.old == DEMM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = GiveDistanceFLT( cp, g.maxiter );
                } else if ( g.old == MSETCPM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = MSetCPMFLT( cp, g.maxiter );
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

/**
 * @brief Mandelbrot Set using double
 * @details Function to compute the Mandelbrot Set using double variables. This derives an
 *          image g.width × g.height, centered at g.center from g.centerX and g.centerY. The
 *          complex width is g.diameter. The inner loop is available in 4 methods; ZX, meaning
 *          calculate without complex variables, COMPLEX, meaning calculate with complex variables,
 *          DEMM, meaning use the Distance Estimator Method for Mandelbrot set and MSETCPM, meaning
 *          use the Continuous Potential Method.
 *
 *
 * @param P Parameters structure, a collection of configuration information.
 * @return A Parameters structure g, as modified by the function.
 */
Parameters MSetDBL( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorDBL cp;
        cp.DistanceMax = GiveDistanceMax( g.diameter / g.width, g.width );
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            double y = ( Y - g.height2 ) / ( g.height2 );
            for ( int X = 0; X < g.width; X++ ) {
                double x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;
                double zOld;

                if ( g.old == ZX ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp.Zx = 0.0;
                    cp.Zy = 0.0;
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        cp.Zx2 = cp.Zx * cp.Zx;
                        cp.Zy2 = cp.Zy * cp.Zy;
                        if ( ( cp.Zx2 + cp.Zy2 ) > g.escape )
                            break;
                        cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                        cp.Zx = cp.Zx2 - cp.Zy2 + cp.Cx;
                        cp.Exps += exp( cp.Zx2 + cp.Zy2 );
                    }
                    cp.Z = cp.Zx + cp.Zy * I;
                    cp.C = cp.Cx + cp.Cy * I;
                } else if ( g.old == COMPLEX ) {
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        zOld = cp.Z;
                        cp.Z = cp.Z * cp.Z + cp.C;
                        cp.Exps += exp( -cabs( cp.Z ) - 0.5 / ( cabs( zOld - cp.Z ) ) );
                        if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                            break;
                    }
                } else if ( g.old == DEMM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = GiveDistanceDBL( cp, g.maxiter );
                } else if ( g.old == MSETCPM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = MSetCPMDBL( cp, g.maxiter );
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

/**
 * @brief Mandelbrot Set using long double
 * @details Function to compute the Mandelbrot Set using long double variables. This derives an
 *          image g.width × g.height, centered at g.center from g.centerX and g.centerY. The
 *          complex width is g.diameter. The inner loop is available in 4 methods; ZX, meaning
 *          calculate without complex variables, COMPLEX, meaning calculate with complex variables,
 *          DEMM, meaning use the Distance Estimator Method for Mandelbrot set and MSETCPM, meaning
 *          use the Continuous Potential Method.
 *
 *
 * @param P Parameters structure, a collection of configuration information.
 * @return A Parameters structure g, as modified by the function.
 */
Parameters MSetLDBL( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        ColorLDBL cp;
        cp.DistanceMax = GiveDistanceMax( g.diameter / g.width, g.width );
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            long double y = ( Y - g.height2 ) / ( g.height2 );
            for ( int X = 0; X < g.width; X++ ) {
                long double x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;
                long double zOld;

                if ( g.old == ZX ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp.Zx = 0.0;
                    cp.Zy = 0.0;
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        cp.Zx2 = cp.Zx * cp.Zx;
                        cp.Zy2 = cp.Zy * cp.Zy;
                        if ( ( cp.Zx2 + cp.Zy2 ) > g.escape )
                            break;
                        cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                        cp.Zx = cp.Zx2 - cp.Zy2 + cp.Cx;
                        cp.Exps += exp( cp.Zx2 + cp.Zy2 );
                    }
                    cp.Z = cp.Zx + cp.Zy * I;
                    cp.C = cp.Cx + cp.Cy * I;
                } else if ( g.old == COMPLEX ) {
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        zOld = cp.Z;
                        cp.Z = cp.Z * cp.Z + cp.C;
                        cp.Exps += exp( -cabs( cp.Z ) - 0.5 / ( cabs( zOld - cp.Z ) ) );
                        if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                            break;
                    }
                } else if ( g.old == DEMM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = GiveDistanceLDBL( cp, g.maxiter );
                } else if ( g.old == MSETCPM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = MSetCPMLDBL( cp, g.maxiter );
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

/**
 * @brief Mandelbrot Set using __float128
 * @details Function to compute the Mandelbrot Set using __float128 variables. This derives an
 *          image g.width × g.height, centered at g.center from g.centerX and g.centerY. The
 *          complex width is g.diameter. The inner loop is available in 4 methods; ZX, meaning
 *          calculate without complex variables, COMPLEX, meaning calculate with complex variables,
 *          DEMM, meaning use the Distance Estimator Method for Mandelbrot set and MSETCPM, meaning
 *          use the Continuous Potential Method.
 *
 *
 * @param P Parameters structure, a collection of configuration information.
 * @return A Parameters structure g, as modified by the function.
 */
Parameters MSetFLT128( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#pragma omp parallel shared(im)
    {
        Color128 cp;
        cp.DistanceMax = GiveDistanceMax( g.diameter / g.width, g.width );
#pragma omp for schedule(dynamic)
        for ( int Y = 0; Y < g.height; Y++ ) {
            __float128 y = ( Y - g.height2 ) / ( g.height2 );
            for ( int X = 0; X < g.width; X++ ) {
                __float128 x = ( X - g.width2 ) / ( g.height2 );
                cp.colorPoly = 0;
                cp.Exps = 0;
                cp.C = g.center + g.radius * ( x - I * y );
                cp.Z = 0;
                __float128 zOld;

                if ( g.old == ZX ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp.Zx = 0.0;
                    cp.Zy = 0.0;
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        cp.Zx2 = cp.Zx * cp.Zx;
                        cp.Zy2 = cp.Zy * cp.Zy;
                        if ( ( cp.Zx2 + cp.Zy2 ) > g.escape )
                            break;
                        cp.Zy = 2 * cp.Zx * cp.Zy + cp.Cy;
                        cp.Zx = cp.Zx2 - cp.Zy2 + cp.Cx;
                        cp.Exps += exp( cp.Zx2 + cp.Zy2 );
                    }
                    cp.Z = cp.Zx + cp.Zy * I;
                    cp.C = cp.Cx + cp.Cy * I;
                } else if ( g.old == COMPLEX ) {
                    for ( cp.n = 0; cp.n < g.maxiter; cp.n++ ) {
                        zOld = cp.Z;
                        cp.Z = cp.Z * cp.Z + cp.C;
                        cp.Exps += exp( -cabs( cp.Z ) - 0.5 / ( cabs( zOld - cp.Z ) ) );
                        if ( creal( cp.Z ) + cimag( cp.Z ) > 4 )
                            break;
                    }
                } else if ( g.old == DEMM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = GiveDistanceFLT128( cp, g.maxiter );
                } else if ( g.old == MSETCPM ) {
                    cp.Cx = creal( cp.C );
                    cp.Cy = cimag( cp.C );
                    cp = MSetCPMFLT128( cp, g.maxiter );
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

/**
 * @brief Float implementation of DEMM
 * @details This is the Distance Estimator Method for the Mandelbrot set. It is
 *          coded using all float variables.
 *
 * @param cp An instance of the ColorFLT structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorFLT the function was called with.
 */
ColorFLT GiveDistanceFLT( ColorFLT cp, int iMax ) {
    float Zx = 0.0;
    float Zy = 0.0;
    float Zx2;
    float Zy2;
    float temp;
    float absZ2;
    float dZx = 0.0;
    float dZy = 0.0;
    float absdZ2;
    float ER2 = 1089.0;
    float g = 100.0;
    float zOld;

    Zx2 = Zx * Zx;
    Zy2 = Zy * Zy;
    absZ2 = Zx * Zx + Zy * Zy;
    absdZ2 = dZx * dZx + dZy * dZy;

    for ( cp.n = 0; cp.n < iMax; cp.n++ ) {
        zOld = absZ2;
        if ( absZ2 > ER2 ) {
            break;
        }
        temp = 2 * ( Zx * dZx - Zy * dZy ) + 1.0;
        dZy = 2 * ( Zx * dZy + Zy * dZx );
        dZx = temp;

        Zy = 2 * Zx * Zy + cp.Cy;
        Zx = Zx2 - Zy2 + cp.Cx;

        Zx2 = Zx * Zx;
        Zy2 = Zy * Zy;
        absZ2 = Zx2 + Zy2;
        absdZ2 = dZx * dZx + dZy * dZy;
        cp.Exps += exp( -sqrt( absZ2 ) - 0.5 / ( sqrt( zOld - absZ2 ) ) );
    }
    cp.Z = Zx + Zy * I;

    if ( cp.n < iMax ) {
        cp.colorPoly = sqrt( absZ2 / absdZ2 ) * log( absZ2 );
        cp.colorPoly = pow( g * cp.colorPoly, 0.25 );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief Double implementation of DEMM
 * @details This is the Distance Estimator Method for the Mandelbrot set. It is
 *          coded using all double variables.
 *
 * @param cp An instance of the ColorDBL structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorDBL the function was called with.
 */
ColorDBL GiveDistanceDBL( ColorDBL cp, int iMax ) {
    double Zx = 0.0;
    double Zy = 0.0;
    double Zx2;
    double Zy2;
    double temp;
    double absZ2;
    double dZx = 0.0;
    double dZy = 0.0;
    double absdZ2;
    double ER2 = 1089.0;
    double g = 100.0;
    double zOld;

    Zx2 = Zx * Zx;
    Zy2 = Zy * Zy;
    absZ2 = Zx * Zx + Zy * Zy;
    absdZ2 = dZx * dZx + dZy * dZy;

    for ( cp.n = 0; cp.n < iMax; cp.n++ ) {
        zOld = absZ2;
        if ( absZ2 > ER2 ) {
            break;
        }
        temp = 2 * ( Zx * dZx - Zy * dZy ) + 1.0;
        dZy = 2 * ( Zx * dZy + Zy * dZx );
        dZx = temp;

        Zy = 2 * Zx * Zy + cp.Cy;
        Zx = Zx2 - Zy2 + cp.Cx;

        Zx2 = Zx * Zx;
        Zy2 = Zy * Zy;
        absZ2 = Zx2 + Zy2;
        cp.Exps += exp( absZ2 );
        absdZ2 = dZx * dZx + dZy * dZy;
        cp.Exps += exp( -sqrt( absZ2 ) - 0.5 / ( sqrt( zOld - absZ2 ) ) );
    }

    if ( cp.n < iMax ) {
        cp.colorPoly = sqrt( absZ2 / absdZ2 ) * log( absZ2 );
        cp.colorPoly = pow( g * cp.colorPoly, 0.25 );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief Long double implementation of DEMM
 * @details This is the Distance Estimator Method for the Mandelbrot set. It is
 *          coded using all long double variables.
 *
 * @param cp An instance of the ColorLDBL structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorLDBL the function was called with.
 */
ColorLDBL GiveDistanceLDBL( ColorLDBL cp, int iMax ) {
    long double Zx = 0.0;
    long double Zy = 0.0;
    long double Zx2;
    long double Zy2;
    long double temp;
    long double absZ2;
    long double dZx = 0.0;
    long double dZy = 0.0;
    long double absdZ2;
    long double ER2 = 1089.0;
    long double g = 100.0;
    long double zOld;

    Zx2 = Zx * Zx;
    Zy2 = Zy * Zy;
    absZ2 = Zx * Zx + Zy * Zy;
    absdZ2 = dZx * dZx + dZy * dZy;

    for ( cp.n = 0; cp.n < iMax; cp.n++ ) {
        zOld = absZ2;
        if ( absZ2 > ER2 ) {
            break;
        }
        temp = 2 * ( Zx * dZx - Zy * dZy ) + 1.0;
        dZy = 2 * ( Zx * dZy + Zy * dZx );
        dZx = temp;

        Zy = 2 * Zx * Zy + cp.Cy;
        Zx = Zx2 - Zy2 + cp.Cx;

        Zx2 = Zx * Zx;
        Zy2 = Zy * Zy;
        absZ2 = Zx2 + Zy2;
        absdZ2 = dZx * dZx + dZy * dZy;
        cp.Exps += exp( -sqrt( absZ2 ) - 0.5 / ( sqrt( zOld - absZ2 ) ) );
    }

    if ( cp.n < iMax ) {
        cp.colorPoly = sqrt( absZ2 / absdZ2 ) * log( absZ2 );
        cp.colorPoly = pow( g * cp.colorPoly, 0.25 );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief __float128 implementation of DEMM
 * @details This is the Distance Estimator Method for the Mandelbrot set. It is
 *          coded using all __float128 variables.
 *
 * @param cp An instance of the Color128 structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of Color128 the function was called with.
 */
Color128 GiveDistanceFLT128( Color128 cp, int iMax ) {
    __float128 Zx = 0.0;
    __float128 Zy = 0.0;
    __float128 Zx2, Zy2;
    __float128 temp;
    __float128 absZ2;
    __float128 dZx = 0.0;
    __float128 dZy = 0.0;
    __float128 absdZ2;
    __float128 ER2 = 1089.0;
    __float128 g = 100.0;
    __float128 zOld;

    Zx2 = Zx * Zx;
    Zy2 = Zy * Zy;
    absZ2 = Zx * Zx + Zy * Zy;
    absdZ2 = dZx * dZx + dZy * dZy;

    for ( cp.n = 0; cp.n < iMax; cp.n++ ) {
        zOld = absZ2;
        if ( absZ2 > ER2 ) {
            break;
        }
        temp = 2 * ( Zx * dZx - Zy * dZy ) + 1.0;
        dZy = 2 * ( Zx * dZy + Zy * dZx );
        dZx = temp;

        Zy = 2 * Zx * Zy + cp.Cy;
        Zx = Zx2 - Zy2 + cp.Cx;

        Zx2 = Zx * Zx;
        Zy2 = Zy * Zy;
        absZ2 = Zx2 + Zy2;
        absdZ2 = dZx * dZx + dZy * dZy;
        cp.Exps += exp( -sqrt( absZ2 ) - 0.5 / ( sqrt( zOld - absZ2 ) ) );
    }

    if ( cp.n < iMax ) {
        cp.colorPoly = sqrt( absZ2 / absdZ2 ) * log( absZ2 );
        cp.colorPoly = pow( g * cp.colorPoly, 0.25 );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief Float implementation of MSETCPM
 * @details This is the Continuous Potential Method. It is coded using all float variables.
 *
 * @param cp An instance of the ColorFLT structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorFLT the function was called with.
 */
ColorFLT MSetCPMFLT( ColorFLT cp, int maxiter ) {
    float x = cp.Cx;
    float x2 = x * x;
    float y = cp.Cy;
    float y2 = y * y;
    float temp;
    float zOld;

    for ( cp.n = 0; cp.n < maxiter && ( x2 + y2 < 10000.0 ); cp.n++ ) {
        zOld = x2 + y2;
        temp = x2 - y2 + cp.Cx;
        y = 2 * x * y + cp.Cy;
        x = temp;
        x2 = x * x;
        y2 = y * y;
        cp.Exps += exp( -sqrt( x2 + y2 ) - 0.5 / ( sqrt( zOld - ( x2 + y2 ) ) ) );
    }
    if ( cp.n < maxiter ) {
        cp.colorPoly = 0.5 * log( x2 + y2 ) / pow( 2.0, cp.n );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief Double implementation of MSETCPM
 * @details This is the Continuous Potential Method. It is coded using all double variables.
 *
 * @param cp An instance of the ColorDBL structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorDBL the function was called with.
 */
ColorDBL MSetCPMDBL( ColorDBL cp, int maxiter ) {
    double x = cp.Cx;
    double x2 = x * x;
    double y = cp.Cy;
    double y2 = y * y;
    double temp;

    for ( cp.n = 0; cp.n < maxiter && ( x2 + y2 < 10000.0 ); cp.n++ ) {
        temp = x2 - y2 + cp.Cx;
        y = 2 * x * y + cp.Cy;
        x = temp;
        x2 = x * x;
        y2 = y * y;
    }
    if ( cp.n < maxiter ) {
        cp.colorPoly = 0.5 * log( x2 + y2 ) / pow( 2.0, cp.n );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief Long double implementation of MSETCPM
 * @details This is the Continuous Potential Method. It is coded using all long double variables.
 *
 * @param cp An instance of the ColorLDBL structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of ColorLDBL the function was called with.
 */
ColorLDBL MSetCPMLDBL( ColorLDBL cp, int maxiter ) {
    long double x = cp.Cx;
    long double x2 = x * x;
    long double y = cp.Cy;
    long double y2 = y * y;
    long double temp;

    for ( cp.n = 0; cp.n < maxiter && ( x2 + y2 < 10000.0 ); cp.n++ ) {
        temp = x2 - y2 + cp.Cx;
        y = 2 * x * y + cp.Cy;
        x = temp;
        x2 = x * x;
        y2 = y * y;
    }
    if ( cp.n < maxiter ) {
        cp.colorPoly = 0.5 * log( x2 + y2 ) / pow( 2.0, cp.n );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}

/**
 * @brief __float128 implementation of MSETCPM
 * @details This is the Continuous Potential Method. It is coded using all __float128 variables.
 *
 * @param cp An instance of the Color128 structure holding needed information.
 * @param iMax The maximum iteration count.
 *
 * @return The same instance of Color128 the function was called with.
 */
Color128 MSetCPMFLT128( Color128 cp, int maxiter ) {
    __float128 x = cp.Cx;
    __float128 x2 = x * x;
    __float128 y = cp.Cy;
    __float128 y2 = y * y;
    __float128 temp;

    for ( cp.n = 0; cp.n < maxiter && ( x2 + y2 < 10000.0 ); cp.n++ ) {
        temp = x2 - y2 + cp.Cx;
        y = 2 * x * y + cp.Cy;
        x = temp;
        x2 = x * x;
        y2 = y * y;
    }
    if ( cp.n < maxiter ) {
        cp.colorPoly = 0.5 * log( x2 + y2 ) / pow( 2.0, cp.n );
    } else {
        cp.colorPoly = 0.0;
    }

    return cp;
}
