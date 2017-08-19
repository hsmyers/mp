//
// colors.c
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <assert.h>
#include "colors.h"
#include "cspace.h"
#include "cnames.h"

const double saturation = 0.90;
const double value = 0.75;
const double rotation = 172.0;

float getCColorFLT( ColorFLT c, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        c.Z = c.Z * c.Z + c.C;
        c.n++;
    }
    switch ( P.color ) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float ) P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 8:
            return c.n + 1.5 - log2( log2( cabs( c.Z ) ) );
        default:
            return 0.0;
    }
}

double getCColorDBL( ColorDBL c, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        c.Z = c.Z * c.Z + c.C;
        c.n++;
    }
    switch ( P.color ) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float ) P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 8:
            return c.n + 1.5 - log2( log2( cabs( c.Z ) ) );
        default:
            return 0.0;
    }
}

long double getCColorLDBL( ColorLDBL c, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        c.Z = c.Z * c.Z + c.C;
        c.n++;
    }
    switch ( P.color ) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float ) P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 8:
            return c.n + 1.5 - log2( log2( cabs( c.Z ) ) );
        default:
            return 0.0;
    }
}

__float128 getCColor128( Color128 c, Parameters P ) {
    for ( int m = 0; m < P.tweak; m++ ) {
        c.Z = c.Z * c.Z + c.C;
        c.n++;
    }
    switch ( P.color ) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float ) P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float ) P.maxiter );
        case 8:
            return c.n + 1.5 - log2( log2( cabs( c.Z ) ) );
        default:
            return 0.0;
    }
}

int fractionCount( int n, int max ) {
    int f = ( int ) ( 100 * ( float ) n / ( float ) max );

    if ( f <= 5 ) {
        return 0;
    } else if ( f < 20 ) {
        return 51;
    } else if ( f <= 40 ) {
        return 102;
    } else if ( f <= 60 ) {
        return 153;
    } else if ( f <= 80 ) {
        return 206;
    } else {
        return 255;
    }
}

Rgb getRgb11( int count, int MaxCount, complex Z ) {
    Rgb color = { 0, 0, 0 };
    double zn = cabs( Z );
    double data = M_2PI * ( count / 360.0 );
    double hue = data + 1.0 - log( log( abs( zn ) ) ) / log( 2.0 );

    hue = 0.95 + 20.0 * hue;
    hue = fmod( hue, 360.0 );

    HSV rainbow = {
        hue,
        0.8,
        1,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb10( int count, int MaxCount, complex Z ) {
    Rgb color = { 0, 0, 0 };
    double di = count;
    double zn = cabs( Z );
    double hue = di + 1.0 - log( log( abs( zn ) ) ) / log( 2.0 );

    hue = 0.95 + 20.0 * hue;
    hue = fmod( hue, 360.0 );

    HSV rainbow = {
        hue,
        0.8,
        1,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb9( int count, int MaxCount, double mu ) {
    Rgb color = { 0, 0, 0 };

    HSV rainbow = {
        mu,
        1,
        count % 256,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb8( int count, int MaxCount, complex Z ) {
    Rgb color = { 0, 0, 0 };
    double mu = 5 + count - log( log( cabs( Z ) ) ) / log( 2 );

    HSV rainbow = {
        mu,
        1,
        1,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb7( int count, int MaxCount, complex Z ) {
    Rgb color = { 0, 0, 0 };
    double nu = count - log( log( cabs( Z ) / log( 2 ) ) ) / log( 2 );

    HSV rainbow = {
        nu,
        1,
        1,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb6( int count, int MaxCount, complex Z ) {
    Rgb color = { 0, 0, 0 };
    double continuous_index = count + 1 - ( log( 2 ) / cabs( Z ) ) / log( 2 );

    if ( count < MaxCount ) {
        color.r = ( unsigned char ) ( sin( 0.016 * continuous_index + 4 ) * 230 + 25 );
        color.g = ( unsigned char ) ( sin( 0.013 * continuous_index + 2 ) * 230 + 25 );
        color.b = ( unsigned char ) ( sin( 0.01 * continuous_index + 1 ) * 230 + 25 );
    }
    return color;
}

Rgb getRgb5( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        count % 256,
        fractionCount( count, MaxCount ),
        count % 256,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb4( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        ( count * 6 ) % 256,
        0,
        count % 256,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

Rgb getRgb3( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        ( count * 6 ) % 256,
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
        color.g = ( unsigned char ) ( 15 * ( 1 - t ) * ( 1 - t ) * t * t * 255 );
        color.b = ( unsigned char ) ( 8.5 * ( 1 - t ) * ( 1 - t ) * ( 1 - t ) * t * 255 );
    }

    return color;
}

Rgb getBersteinSineFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r = abs( sin( rgb_freq.r * g.n + rgb_phase.r ) * ( 255 - rgb_base.r ) + rgb_base.r );
        color.g = abs( sin( rgb_freq.g * g.n + rgb_phase.g ) * ( 255 - rgb_base.g ) + rgb_base.g );
        color.b = abs( sin( rgb_freq.b * g.n + rgb_phase.b ) * ( 255 - rgb_base.b ) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinSineDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r = abs( sin( rgb_freq.r * g.n + rgb_phase.r ) * ( 255 - rgb_base.r ) + rgb_base.r );
        color.g = abs( sin( rgb_freq.g * g.n + rgb_phase.g ) * ( 255 - rgb_base.g ) + rgb_base.g );
        color.b = abs( sin( rgb_freq.b * g.n + rgb_phase.b ) * ( 255 - rgb_base.b ) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinSineLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r = abs( sin( rgb_freq.r * g.n + rgb_phase.r ) * ( 255 - rgb_base.r ) + rgb_base.r );
        color.g = abs( sin( rgb_freq.g * g.n + rgb_phase.g ) * ( 255 - rgb_base.g ) + rgb_base.g );
        color.b = abs( sin( rgb_freq.b * g.n + rgb_phase.b ) * ( 255 - rgb_base.b ) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinSine128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r = abs( sin( rgb_freq.r * g.n + rgb_phase.r ) * ( 255 - rgb_base.r ) + rgb_base.r );
        color.g = abs( sin( rgb_freq.g * g.n + rgb_phase.g ) * ( 255 - rgb_base.g ) + rgb_base.g );
        color.b = abs( sin( rgb_freq.b * g.n + rgb_phase.b ) * ( 255 - rgb_base.b ) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs( rgb_amp.r * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.r );
        color.g =
            abs( rgb_amp.g * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.g ) +
                 rgb_base.g );
        color.b =
            abs( rgb_amp.b * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.b );
    }

    return color;
}

Rgb getBersteinDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs( rgb_amp.r * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.r );
        color.g =
            abs( rgb_amp.g * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.g ) +
                 rgb_base.g );
        color.b =
            abs( rgb_amp.b * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.b );
    }

    return color;
}

Rgb getBersteinLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs( rgb_amp.r * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.r );
        color.g =
            abs( rgb_amp.g * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.g ) +
                 rgb_base.g );
        color.b =
            abs( rgb_amp.b * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.b );
    }

    return color;
}

Rgb getBerstein128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs( rgb_amp.r * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.r );
        color.g =
            abs( rgb_amp.g * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.g ) +
                 rgb_base.g );
        color.b =
            abs( rgb_amp.b * ( 1 - index_mapped ) * pow( index_mapped, 3 ) * ( 255 - rgb_base.r ) +
                 rgb_base.b );
    }

    return color;
}

Rgb getRgbSmoothCPFLT( float colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r = ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g = ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b = ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCPDBL( double colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r = ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g = ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b = ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCPLDBL( long double colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r = ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g = ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b = ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

Rgb getRgbSmoothCP128( __float128 colorPoly, int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };

    if ( count < MaxCount ) {
        color.r = ( unsigned char ) ( sin( 0.016 * colorPoly + 4 ) * 230 + 25 );
        color.g = ( unsigned char ) ( sin( 0.013 * colorPoly + 2 ) * 230 + 25 );
        color.b = ( unsigned char ) ( sin( 0.01 * colorPoly + 1 ) * 230 + 25 );
    }

    return color;
}

int getfColorFLT( Parameters g, ColorFLT c ) {
    Rgb rcolor = { 0, 0, 0 };
    Rgb r_amp = { 127, 127, 127 };
    Rgb r_base = { 0.01, 0.008, 0.005 };
    Rgb r_ampA = { 9, 15, 8.5 };
    Rgb r_baseA = { 0.0, 0.0, 0.0 };
    setRgb( &r_amp, &r_base, g );
    float zOld;

    for ( int m = 0; m < g.tweak; m++ ) {
        zOld = c.Z;
        c.Z = c.Z * c.Z + c.C;
        c.Exps += exp( -cabs( c.Z ) - 0.5 / ( cabs( zOld - c.Z ) ) );
    }
    switch ( g.color ) {
        case 1:
            rcolor = getRgbFromTable( c.n, g.maxiter );
            break;
        case 2:
            rcolor = getRgbSmooth( c.n, g.maxiter );
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            rcolor = getRgbSmoothCPFLT( getCColorFLT( c, g ), c.n, g.maxiter );
            break;
        case 9:
            rcolor = getRgb2( c.n, g.maxiter );
            break;
        case 10:
            rcolor = getRgb3( c.n, g.maxiter );
            break;
        case 11:
            rcolor = getRgb4( c.n, g.maxiter );
            break;
        case 12:
            rcolor = getRgb5( c.n, g.maxiter );
            break;
        case 13:
            rcolor = getRgbSmoothCPFLT( c.Exps, c.n, g.maxiter );
            break;
        case 14:
            if ( c.n < g.maxiter ) {
                rcolor = HSVToRGB( GiveHSV( c.Z ) );
            }
            break;
        case 15:
            rcolor = HSVToRGB( GiveHSV( c.Z ) );
            break;
        case 16:
            rcolor = getBersteinFLT( g, c, r_baseA, r_ampA );
            break;
        case 17:
            rcolor = getBersteinSineFLT( g, c, ( Rgb ) {
                                         200, 200, 200}
                                         , ( Rgb ) {
                                         0.016, 0.013, 0.01}
                                         , ( Rgb ) {
                                         4, 2, 1}
             );
            break;
        case 18:
            if ( c.n < g.maxiter ) {
                if ( c.colorPoly < c.DistanceMax ) {
                    rcolor.r = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.g = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.b = 255 - ( int ) ( 255.0 * c.colorPoly );
                } else {
                    rcolor = GiveRainbowColor( ( double ) c.colorPoly );
                }
            }
            break;
        case 19:
            rcolor = getRgb6( c.n, g.maxiter, c.Z );
            break;
        case 20:
            rcolor = getRgb7( c.n, g.maxiter, c.Z );
            break;
        case 21:
            rcolor = getRgb8( c.n, g.maxiter, c.Z );
            break;
        case 22:
            rcolor = getRgb9( c.n, g.maxiter, c.Exps );
            break;
        case 23:
            rcolor = getRgb10( c.n, g.maxiter, c.Z );
            break;
        case 24:
            rcolor = getRgb11( c.n, g.maxiter, c.Z );
            break;
        case 25:
            if ( c.n < g.maxiter ) {
                if ( c.Exps < c.DistanceMax ) {
                    rcolor.r = 255 - ( int ) ( 255.0 * c.Exps );
                    rcolor.g = 255 - ( int ) ( 255.0 * c.Exps );
                    rcolor.b = 255 - ( int ) ( 255.0 * c.Exps );
                } else {
                    rcolor = GiveRainbowColor( ( double ) c.Exps );
                }
            }
            break;
        default:
            rcolor = getRgb( c.n, g.maxiter );
    }
    return rgb2int( rcolor );
}

int getfColorDBL( Parameters g, ColorDBL c ) {
    Rgb rcolor = { 0, 0, 0 };
    Rgb r_amp = { 230, 32, 32 };
    Rgb r_base = { 0, 28, 61 };
    setRgb( &r_amp, &r_base, g );
    double zOld;

    for ( int m = 0; m < g.tweak; m++ ) {
        zOld = c.Z;
        c.Z = c.Z * c.Z + c.C;
        c.Exps += exp( -cabs( c.Z ) - 0.5 / ( cabs( zOld - c.Z ) ) );
        c.n++;
    }
    switch ( g.color ) {
        case 1:
            rcolor = getRgbFromTable( c.n, g.maxiter );
            break;
        case 2:
            rcolor = getRgbSmooth( c.n, g.maxiter );
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            rcolor = getRgbSmoothCPDBL( getCColorDBL( c, g ), c.n, g.maxiter );
            break;
        case 9:
            rcolor = getRgb2( c.n, g.maxiter );
            break;
        case 10:
            rcolor = getRgb3( c.n, g.maxiter );
            break;
        case 11:
            rcolor = getRgb4( c.n, g.maxiter );
            break;
        case 12:
            rcolor = getRgb5( c.n, g.maxiter );
            break;
        case 13:
            rcolor = getRgbSmoothCPFLT( c.Exps, c.n, g.maxiter );
            break;
        case 14:
            if ( c.n < g.maxiter ) {
                rcolor = HSVToRGB( GiveHSV( c.Z ) );
            }
            break;
        case 15:
            rcolor = HSVToRGB( GiveHSV( c.Z ) );
            break;
        case 16:
            rcolor = getBersteinDBL( g, c, r_base, r_amp );
            break;
        case 17:
            rcolor = getBersteinSineDBL( g, c, ( Rgb ) {
                                         0.01, 0.008, 0.005}
                                         , ( Rgb ) {
                                         0, 0, 0}
                                         , ( Rgb ) {
                                         127, 127, 127}
             );
            break;
        case 18:
            if ( c.n < g.maxiter ) {
                if ( c.colorPoly < c.DistanceMax ) {
                    rcolor.r = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.g = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.b = 255 - ( int ) ( 255.0 * c.colorPoly );
                } else {
                    rcolor = GiveRainbowColor( ( double ) c.colorPoly );
                }
            }
            break;
        case 19:
            rcolor = getRgb6( c.n, g.maxiter, c.Z );
            break;
        case 20:
            rcolor = getRgb7( c.n, g.maxiter, c.Z );
            break;
        case 21:
            rcolor = getRgb8( c.n, g.maxiter, c.Z );
            break;
        case 22:
            rcolor = getRgb9( c.n, g.maxiter, c.Exps );
            break;
        case 23:
            rcolor = getRgb10( c.n, g.maxiter, c.Z );
            break;
        default:
            rcolor = getRgb( c.n, g.maxiter );
    }
    return rgb2int( rcolor );
}

int getfColorLDBL( Parameters g, ColorLDBL c ) {
    Rgb rcolor = { 0, 0, 0 };
    Rgb r_amp = { 0, 153, 153 };
    Rgb r_base = { 204, 0, 204 };
    setRgb( &r_amp, &r_base, g );
    long double zOld;

    for ( int m = 0; m < g.tweak; m++ ) {
        zOld = c.Z;
        c.Z = c.Z * c.Z + c.C;
        c.Exps += exp( -cabs( c.Z ) - 0.5 / ( cabs( zOld - c.Z ) ) );
        c.n++;
    }
    switch ( g.color ) {
        case 1:
            rcolor = getRgbFromTable( c.n, g.maxiter );
            break;
        case 2:
            rcolor = getRgbSmooth( c.n, g.maxiter );
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            rcolor = getRgbSmoothCPLDBL( getCColorLDBL( c, g ), c.n, g.maxiter );
            break;
        case 9:
            rcolor = getRgb2( c.n, g.maxiter );
            break;
        case 10:
            rcolor = getRgb3( c.n, g.maxiter );
            break;
        case 11:
            rcolor = getRgb4( c.n, g.maxiter );
            break;
        case 12:
            rcolor = getRgb5( c.n, g.maxiter );
            break;
        case 13:
            rcolor = getRgbSmoothCPFLT( c.Exps, c.n, g.maxiter );
            break;
        case 14:
            if ( c.n < g.maxiter ) {
                rcolor = HSVToRGB( GiveHSV( c.Z ) );
            }
            break;
        case 15:
            rcolor = HSVToRGB( GiveHSV( c.Z ) );
            break;
        case 16:
            rcolor = getBersteinLDBL( g, c, r_base, r_amp );
            break;
        case 17:
            rcolor = getBersteinSineLDBL( g, c, ( Rgb ) {
                                          0.01, 0.008, 0.005}
                                          , ( Rgb ) {
                                          0, 0, 0}
                                          , ( Rgb ) {
                                          127, 127, 127}
             );
            break;
        case 18:
            if ( c.n < g.maxiter ) {
                if ( c.colorPoly < c.DistanceMax ) {
                    rcolor.r = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.g = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.b = 255 - ( int ) ( 255.0 * c.colorPoly );
                } else {
                    rcolor = GiveRainbowColor( ( double ) c.colorPoly );
                }
            }
            break;
        case 19:
            rcolor = getRgb6( c.n, g.maxiter, c.Z );
            break;
        case 20:
            rcolor = getRgb7( c.n, g.maxiter, c.Z );
            break;
        case 21:
            rcolor = getRgb8( c.n, g.maxiter, c.Z );
            break;
        case 22:
            rcolor = getRgb9( c.n, g.maxiter, c.Exps );
            break;
        case 23:
            rcolor = getRgb10( c.n, g.maxiter, c.Z );
            break;
        default:
            rcolor = getRgb( c.n, g.maxiter );
    }
    return rgb2int( rcolor );
}

int getfColor128( Parameters g, Color128 c ) {
    Rgb rcolor = { 0, 0, 0 };
    Rgb r_amp = { 0, 153, 153 };
    Rgb r_base = { 204, 0, 204 };
    setRgb( &r_amp, &r_base, g );
    __float128 zOld;

    for ( int m = 0; m < g.tweak; m++ ) {
        zOld = c.Z;
        c.Z = c.Z * c.Z + c.C;
        c.Exps += exp( -cabs( c.Z ) - 0.5 / ( cabs( zOld - c.Z ) ) );
        c.n++;
    }
    switch ( g.color ) {
        case 1:
            rcolor = getRgbFromTable( c.n, g.maxiter );
            break;
        case 2:
            rcolor = getRgbSmooth( c.n, g.maxiter );
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            rcolor = getRgbSmoothCP128( getCColor128( c, g ), c.n, g.maxiter );
            break;
        case 9:
            rcolor = getRgb2( c.n, g.maxiter );
            break;
        case 10:
            rcolor = getRgb3( c.n, g.maxiter );
            break;
        case 11:
            rcolor = getRgb4( c.n, g.maxiter );
            break;
        case 12:
            rcolor = getRgb5( c.n, g.maxiter );
            break;
        case 13:
            rcolor = getRgbSmoothCPFLT( c.Exps, c.n, g.maxiter );
            break;
        case 14:
            if ( c.n < g.maxiter ) {
                rcolor = HSVToRGB( GiveHSV( c.Z ) );
            }
            break;
        case 15:
            rcolor = HSVToRGB( GiveHSV( c.Z ) );
            break;
        case 16:
            rcolor = getBerstein128( g, c, r_base, r_amp );
            break;
        case 17:
            rcolor = getBersteinSine128( g, c, ( Rgb ) {
                                         0.01, 0.008, 0.005}
                                         , ( Rgb ) {
                                         0, 0, 0}
                                         , ( Rgb ) {
                                         127, 127, 127}
             );
            break;
        case 18:
            if ( c.n < g.maxiter ) {
                if ( c.colorPoly < c.DistanceMax ) {
                    rcolor.r = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.g = 255 - ( int ) ( 255.0 * c.colorPoly );
                    rcolor.b = 255 - ( int ) ( 255.0 * c.colorPoly );
                } else {
                    rcolor = GiveRainbowColor( ( double ) c.colorPoly );
                }
            }
            break;
        case 19:
            rcolor = getRgb6( c.n, g.maxiter, c.Z );
            break;
        case 20:
            rcolor = getRgb7( c.n, g.maxiter, c.Z );
            break;
        case 21:
            rcolor = getRgb8( c.n, g.maxiter, c.Z );
            break;
        case 22:
            rcolor = getRgb9( c.n, g.maxiter, c.Exps );
            break;
        case 23:
            rcolor = getRgb10( c.n, g.maxiter, c.Z );
            break;
        default:
            rcolor = getRgb( c.n, g.maxiter );
    }
    return rgb2int( rcolor );
}

int rgb2int( Rgb color ) {
    return ( color.r * 256 * 256 ) + ( color.g * 256 ) + color.b;
}

void setRgb( Rgb * a, Rgb * b, Parameters p ) {

    if ( p.nargc == 2 ) {
        if ( p.names[0][0] != '{' ) {
            name2Rgb( p.names[0], a );
        } else {
            raw2Rgb( p.names[0], a );
        }
        if ( p.names[1][0] != '{' ) {
            name2Rgb( p.names[1], b );
        } else {
            raw2Rgb( p.names[1], b );
        }
    } else if ( p.nargc == 1 ) {
        if ( p.names[0][0] != '{' ) {
            name2Rgb( p.names[0], a );
        } else {
            raw2Rgb( p.names[0], a );
        }
    }
}

void cpyRgb( Rgb source, Rgb * dest ) {
    dest->r = source.r;
    dest->g = source.g;
    dest->b = source.b;
}

void name2Rgb( char *name, Rgb * dest ) {
    Rgb r;

    str2Rgb( name, &r );
    cpyRgb( r, dest );
}

void raw2Rgb( char *name, Rgb * dest ) {
    Rgb color;

    sscanf( name, "{%hhu,%hhu,%hhu}", &color.r, &color.g, &color.b );
    cpyRgb( color, dest );
}

// _______________________________________________________________________________
// added: Tue Aug 01 22:46:36 2017
// from: http://paulbourke.net/miscellaneous/interpolation/

/*
  Linear interpolation is the simplest method of getting values at positions in
  between the data points. The points are simply joined by straight line segments.
  Each segment (bounded by two data points) can be interpolated independently. The
  parameter mu defines where to estimate the value on the interpolated line, it is 0
  at the first point and 1 and the second point. For interpolated values between the
  two points mu ranges between 0 and 1. Values of mu outside this range result in
  extrapolation. This convention is followed for all the subsequent methods below.
  As with subsequent more interesting methods, a snippet of plain C code will server
  to describe the mathematics.
*/
double LinearInterpolate( double y1, double y2, double mu ) {
    return ( y1 * ( 1 - mu ) + y2 * mu );
}

/*
  Linear interpolation results in discontinuities at each point. Often a
  smoother interpolating function is desirable, perhaps the simplest is cosine
  interpolation. A suitable orientated piece of a cosine function serves to
  provide a smooth transition between adjacent segments.
*/
double CosineInterpolate( double y1, double y2, double mu ) {
    double mu2;

    mu2 = ( 1 - cos( mu * M_PI ) ) / 2;
    return ( y1 * ( 1 - mu2 ) + y2 * mu2 );
}

/*
  Cubic interpolation is the simplest method that offers true continuity between
  the segments. As such it requires more than just the two endpoints of the segment
  but also the two points on either side of them. So the function requires 4 points
  in all labelled y0, y1, y2, and y3, in the code below. mu still behaves the same
  way for interpolating between the segment y1 to y2. This does raise issues for how
  to interpolate between the first and last segments. In the examples here I just
  haven't bothered. A common solution is the dream up two extra points at the start
  and end of the sequence, the new points are created so that they have a slope equal
  to the slope of the start or end segment.
*/
double CubicInterpolate( double y0, double y1, double y2, double y3, double mu ) {
    double a0, a1, a2, a3, mu2;

    mu2 = mu * mu;
    a0 = y3 - y2 - y0 + y1;
    a1 = y0 - y1 - a0;
    a2 = y2 - y0;
    a3 = y1;

    return ( a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3 );
}

/*
  Hermite interpolation like cubic requires 4 points so that it can achieve a higher degree
  of continuity. In addition it has nice tension and biasing controls. Tension can be used
  to tighten up the curvature at the known points. The bias is used to twist the curve about
  the known points. The examples shown here have the default tension and bias values of 0, it
  will be left as an exercise for the reader to explore different tension and bias values.

   Tension: 1 is high, 0 normal, -1 is low
   Bias: 0 is even,
         positive is towards first segment,
         negative towards the other
*/
double HermiteInterpolate( double y0, double y1, double y2, double y3, double mu, double tension,
                           double bias ) {
    double m0, m1, mu2, mu3;
    double a0, a1, a2, a3;

    mu2 = mu * mu;
    mu3 = mu2 * mu;
    m0 = ( y1 - y0 ) * ( 1 + bias ) * ( 1 - tension ) / 2;
    m0 += ( y2 - y1 ) * ( 1 - bias ) * ( 1 - tension ) / 2;
    m1 = ( y2 - y1 ) * ( 1 + bias ) * ( 1 - tension ) / 2;
    m1 += ( y3 - y2 ) * ( 1 - bias ) * ( 1 - tension ) / 2;
    a0 = 2 * mu3 - 3 * mu2 + 1;
    a1 = mu3 - 2 * mu2 + mu;
    a2 = mu3 - mu2;
    a3 = -2 * mu3 + 3 * mu2;

    return ( a0 * y1 + a1 * m0 + a2 * m1 + a3 * y2 );
}

Rgb GiveRainbowColor( double position ) {
    if ( position > 1.0 ) {
        if ( position - ( int ) position == 0.0 )
            position = 1.0;
        else
            position = position - ( int ) position;
    }
    double n;
    double f = modf( 6.0 * position, &n );
    unsigned char t = ( int ) ( f * 255 );
    Rgb Color;

    switch ( ( int ) n ) {
        case 0:{
                Color.r = 255;
                Color.g = t;
                Color.b = 0;
                break;
            };
        case 1:{
                Color.r = 255 - t;
                Color.g = 255;
                Color.b = 0;
                break;
            };
        case 2:{
                Color.r = 0;
                Color.g = 255;
                Color.b = t;
                break;
            };
        case 3:{
                Color.r = 0;
                Color.g = 255 - t;
                Color.b = 255;
                break;
            };
        case 4:{
                Color.r = t;
                Color.g = 0;
                Color.b = 255;
                break;
            };
        case 5:{
                Color.r = 255;
                Color.g = 0;
                Color.b = 255 - t;
                break;
            };
        default:{
                Color.r = 255;
                Color.g = 0;
                Color.b = 0;
                break;
            };
    };
    return Color;
}

double GiveDistanceMax( double PixelWidth, int iSide ) {
    return PixelWidth * iSide * 0.0333;
}
