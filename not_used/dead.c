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
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPFLT( colorPoly, n, maxiter );
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
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPDBL( colorPoly, n, maxiter );
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
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPLDBL( colorPoly, n, maxiter );
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
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCP128( colorPoly, n, maxiter );
        default:
            return getRgb( n, maxiter );
    }
}


Parameters msetDBL( Parameters P ) {
    Parameters g = P;
    im = gdImageCreateTrueColor( g.width, g.height );
#ifdef AXIS
    AxesDBL ctaxes = ct_gain_axesDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
#endif
#pragma omp parallel shared(im)
    {
        ColorDBL cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
#ifdef AXIS
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
#else
            double y = ( Y - g.height2 ) / ( g.height2 );
#endif
            for (int X = 0; X < g.width; X++ ) {
#ifdef AXIS
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
#else
                double x = ( X - g.width2 ) / ( g.height2 );
                complex double c = g.center + g.radius * ( x - I * y );
                cp.Cx = creal( c );
                cp.Cy = cimag( c );
#endif
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
    im = gdImageCreateTrueColor( g.width, g.height );
#ifdef AXIS
    AxesLDBL ctaxes = ct_gain_axesLDBL( g.centerX, g.centerY, g.diameter, g.height, g.width );
#endif
#pragma omp parallel shared(im)
    {
        ColorLDBL cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
#ifdef AXIS
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
#else
            long double y = ( Y - g.height2 ) / ( g.height2 );
#endif
            for (int X = 0; X < g.width; X++ ) {
#ifdef AXIS
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
#else
                long double x = ( X - g.width2 ) / ( g.height2 );
                complex long double c = g.center + g.radius * ( x - I * y );
                cp.Cx = creal( c );
                cp.Cy = cimag( c );
#endif
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
    im = gdImageCreateTrueColor( g.width, g.height );
#ifdef AXIS
    AxesFLT128 ctaxes = ct_gain_axesFLT128( g.centerX, g.centerY, g.diameter, g.height, g.width );
#endif
#pragma omp parallel shared(im)
    {
        Color128 cp;
#pragma omp for schedule(dynamic)
        for (int Y = 0; Y < g.height; Y++ ) {
#ifdef AXIS
            cp.Cy = ctaxes.ymax - Y * ctaxes.ctyfactor;
#else
            __float128 y = ( Y - g.height2 ) / ( g.height2 );
#endif
            for (int X = 0; X < g.width; X++ ) {
#ifdef AXIS
                cp.Cx = ctaxes.xmin + X * ctaxes.ctxfactor;
#else
                __float128 x = ( X - g.width2 ) / ( g.height2 );
                __complex128 c = g.center + g.radius * ( x - I * y );
                cp.Cx = creal( c );
                cp.Cy = cimag( c );
#endif
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

#ifdef AXIS
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
#endif
#ifdef AXIS
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
#endif

#ifdef AXIS
AxesDBL ct_gain_axesDBL( double real, double imag, double diameter, int height, int width );
AxesFLT ct_gain_axesFLT( float real, float imag, float diameter, int height, int width );
AxesFLT128 ct_gain_axesFLT128( __float128 real, __float128 imag, __float128 diameter, int height, int width );
AxesLDBL ct_gain_axesLDBL( long double real, long double imag, long double diameter, int height, int width );
#endif
#ifdef COORD
void coordinateLDBL( long double *Cx, long double *Cy, int i, int j, Parameters g ) {
    long double x = ( i - g.width / 2.0 ) / ( g.height / 2.0 );
    long double y = ( j - g.height / 2.0 ) / ( g.height / 2.0 );
    complex long double c = g.center + g.radius * ( x - I * y );
    *Cx = creal( c );
    *Cy = cimag( c );
}

void coordinateDBL( double *Cx, double *Cy, int i, int j, Parameters g ) {
    double x = ( i - g.width / 2.0 ) / ( g.height / 2.0 );
    double y = ( j - g.height / 2.0 ) / ( g.height / 2.0 );
    complex double c = g.center + g.radius * ( x - I * y );
    *Cx = creal( c );
    *Cy = cimag( c );
}

void coordinateFLT( float *Cx, float *Cy, int i, int j, Parameters g ) {
    float x = ( i - g.width / 2.0 ) / ( g.height / 2.0 );
    float y = ( j - g.height / 2.0 ) / ( g.height / 2.0 );
    complex c = g.center + g.radius * ( x - I * y );
    *Cx = creal( c );
    *Cy = cimag( c );
}

void coordinateFLT128( __float128 *Cx, __float128 *Cy, int i, int j, Parameters g ) {
    __float128 x = ( i - g.width / 2.0 ) / ( g.height / 2.0 );
    __float128 y = ( j - g.height / 2.0 ) / ( g.height / 2.0 );
    __complex128 c = g.center + g.radius * ( x - I * y );
    *Cx = creal( c );
    *Cy = cimag( c );
}
#endif

