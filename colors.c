//
// colors.c
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <complex.h>
#include <math.h>
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
    switch (P.color) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
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
    switch (P.color) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
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
    switch (P.color) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
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
    switch (P.color) {
        case 3:
            return c.n + 1 - ( log( 2 ) / cabs( c.Z ) / log( 2 ) );
        case 4:
            return c.n - ( log( log( cabs( c.Z ) ) ) ) / log( 2.0 );
        case 5:
            return 256.0 * log( 1.75 + c.n - log( log( cabs( c.Z ) ) ) ) / log( ( float )P.maxiter );
        case 6:
            return 256.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
        case 7:
            return 512.0 * log2( 1.75 + c.n - log2( log2( cabs( c.Z ) ) ) ) / log2( ( float )P.maxiter );
        case 8:
            return c.n + 1.5 - log2( log2( cabs( c.Z ) ) );
        default:
            return 0.0;
    }
}

Rgb getRgb5( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        count % 256,
        fractionCount(count, MaxCount),
        count % 256,
    };
    if ( count < MaxCount ) {
        color = HSVToRGB( rainbow );
    }
    return color;
}

int fractionCount( int n, int max ) {
    int f = (int)(100 * (float)n / (float)max);

    if ( f <= 5) {
        return 0;
    } else if ( f < 20) {
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

Rgb getRgb4( int count, int MaxCount ) {
    Rgb color = { 0, 0, 0 };
    HSV rainbow = {
        (count * 6) % 256,
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

Rgb getBersteinSineFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r =
            abs(sin(rgb_freq.r * g.n + rgb_phase.r) * (255 - rgb_base.r) + rgb_base.r);
        color.g =
            abs(sin(rgb_freq.g * g.n + rgb_phase.g) * (255 - rgb_base.g) + rgb_base.g);
        color.b =
            abs(sin(rgb_freq.b * g.n + rgb_phase.b) * (255 - rgb_base.b) + rgb_base.b);
    }

    return color;
}

Rgb getBersteinSineDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r =
            abs(sin(rgb_freq.r * g.n + rgb_phase.r) * (255 - rgb_base.r) + rgb_base.r);
        color.g =
            abs(sin(rgb_freq.g * g.n + rgb_phase.g) * (255 - rgb_base.g) + rgb_base.g);
        color.b =
            abs(sin(rgb_freq.b * g.n + rgb_phase.b) * (255 - rgb_base.b) + rgb_base.b);
    }

    return color;
}

Rgb getBersteinSineLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r =
            abs(sin(rgb_freq.r * g.n + rgb_phase.r) * (255 - rgb_base.r) + rgb_base.r);
        color.g =
            abs(sin(rgb_freq.g * g.n + rgb_phase.g) * (255 - rgb_base.g) + rgb_base.g);
        color.b =
            abs(sin(rgb_freq.b * g.n + rgb_phase.b) * (255 - rgb_base.b) + rgb_base.b);
    }

    return color;
}

Rgb getBersteinSine128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_freq, Rgb rgb_phase ) {
    Rgb color = { 0, 0, 0 };

    if ( g.n < p.maxiter ) {
        color.r =
            abs(sin(rgb_freq.r * g.n + rgb_phase.r) * (255 - rgb_base.r) + rgb_base.r);
        color.g =
            abs(sin(rgb_freq.g * g.n + rgb_phase.g) * (255 - rgb_base.g) + rgb_base.g);
        color.b =
            abs(sin(rgb_freq.b * g.n + rgb_phase.b) * (255 - rgb_base.b) + rgb_base.b);
    }

    return color;
}

Rgb getBersteinFLT( Parameters p, ColorFLT g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs(rgb_amp.r * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.r );
        color.g =
            abs(rgb_amp.g * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.g) + rgb_base.g );
        color.b =
            abs(rgb_amp.b * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinDBL( Parameters p, ColorDBL g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs(rgb_amp.r * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.r );
        color.g =
            abs(rgb_amp.g * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.g) + rgb_base.g );
        color.b =
            abs(rgb_amp.b * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.b );
    }

    return color;
}

Rgb getBersteinLDBL( Parameters p, ColorLDBL g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs(rgb_amp.r * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.r );
        color.g =
            abs(rgb_amp.g * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.g) + rgb_base.g );
        color.b =
            abs(rgb_amp.b * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.b );
    }

    return color;
}

Rgb getBerstein128( Parameters p, Color128 g, Rgb rgb_base, Rgb rgb_amp ) {
    Rgb color = { 0, 0, 0 };
    float index_mapped = g.n / p.escape;

    if ( g.n < p.maxiter ) {
        color.r =
            abs(rgb_amp.r * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.r );
        color.g =
            abs(rgb_amp.g * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.g) + rgb_base.g );
        color.b =
            abs(rgb_amp.b * (1 - index_mapped) * pow(index_mapped, 3) * (255 - rgb_base.r) + rgb_base.b );
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

int getfColorFLT( Parameters g, ColorFLT c ) {
    Rgb rcolor = { 0, 0, 0 };
    Rgb r_amp = { 127, 127, 127 };
    Rgb r_base = { 0.01, 0.008, 0.005 };
    setRgb( &r_amp, &r_base, g );

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
            for ( int m = 0; m < g.tweak ; m++ ) {
                c.Z = c.Z * c.Z + c.C;
                c.Exps += cabs( c.Z );
            }
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
            rcolor = getBersteinFLT( g, c, r_base, r_amp );
            break;
        case 17:
            rcolor = getBersteinSineFLT( g, c, (Rgb){200,200,200}, (Rgb){0.016,0.013,0.01}, (Rgb){4,2,1} );
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
            for ( int m = 0; m < g.tweak ; m++ ) {
                c.Z = c.Z * c.Z + c.C;
                c.Exps += cabs( c.Z );
            }
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
            rcolor = getBersteinSineDBL( g, c, (Rgb){0.01,0.008,0.005}, (Rgb){0,0,0}, (Rgb){127,127,127} );
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
            for ( int m = 0; m < g.tweak ; m++ ) {
                c.Z = c.Z * c.Z + c.C;
                c.Exps += cabs( c.Z );
            }
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
            rcolor = getBersteinSineLDBL( g, c, (Rgb){0.01,0.008,0.005}, (Rgb){0,0,0}, (Rgb){127,127,127} );
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
            for ( int m = 0; m < g.tweak ; m++ ) {
                c.Z = c.Z * c.Z + c.C;
                c.Exps += cabs( c.Z );
            }
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
            rcolor = getBersteinSine128( g, c, (Rgb){0.01,0.008,0.005}, (Rgb){0,0,0}, (Rgb){127,127,127} );
            break;
        default:
            rcolor = getRgb( c.n, g.maxiter );
    }
    return rgb2int( rcolor );
}

int rgb2int( Rgb color ) {
    return ( color.r * 256 * 256 ) + ( color.g * 256 ) + color.b;
}

void setRgb( Rgb *a, Rgb *b, Parameters p ) {

    if ( p.nargc == 2 ) {
        if ( p.names[0][0] != '{' ) {
            name2Rgb( p.names[0], a );
        } else {
            raw2Rgb( p.names[0], a );
        }
        if ( p.names[0][0] != '{' ) {
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

void cpyRgb( Rgb source, Rgb *dest ) {
    dest->r = source.r;
    dest->g = source.g;
    dest->b = source.b;
}

void name2Rgb( char *name, Rgb *dest ) {
    Rgb r;

    str2Rgb( name, &r );
    cpyRgb( r, dest );
}

void raw2Rgb( char *name, Rgb *dest ) {
    Rgb color;

    sscanf( name, "{%hhu,%hhu,%hhu}", &color.r, &color.g, &color.b );
    cpyRgb( color, dest );
}