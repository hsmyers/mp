//
// cspace.c
//
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex.h>
#include "cspace.h"

static double Min( double a, double b ) {
    return a <= b ? a : b;
}

static double Max( double a, double b ) {
    return a >= b ? a : b;
}

Rgb HSVToRGB( HSV hsv ) {
    double r = 0, g = 0, b = 0;

    if ( hsv.S == 0 ) {
        r = hsv.V;
        g = hsv.V;
        b = hsv.V;
    } else {
        int i;
        double f, p, q, t;

        if ( hsv.H == 360 )
            hsv.H = 0;
        else
            hsv.H = hsv.H / 60;

        i = ( int ) trunc( hsv.H );
        f = hsv.H - i;

        p = hsv.V * ( 1.0 - hsv.S );
        q = hsv.V * ( 1.0 - ( hsv.S * f ) );
        t = hsv.V * ( 1.0 - ( hsv.S * ( 1.0 - f ) ) );

        switch ( i ) {
            case 0:
                r = hsv.V;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = hsv.V;
                b = p;
                break;
            case 2:
                r = p;
                g = hsv.V;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = hsv.V;
                break;
            case 4:
                r = t;
                g = p;
                b = hsv.V;
                break;
            default:
                r = hsv.V;
                g = p;
                b = q;
                break;
        }
    }

    Rgb rgb;
    rgb.r = r * 255;
    rgb.g = g * 255;
    rgb.b = b * 255;

    return rgb;
}

HSV RGBToHSV( Rgb rgb ) {
    double delta, min;
    double h = 0, s, v;

    min = Min( Min( rgb.r, rgb.g ), rgb.b );
    v = Max( Max( rgb.r, rgb.g ), rgb.b );
    delta = v - min;

    if ( v == 0.0 )
        s = 0;
    else
        s = delta / v;

    if ( s == 0 )
        h = 0.0;
    else {
        if ( rgb.r == v )
            h = ( rgb.g - rgb.b ) / delta;
        else if ( rgb.g == v )
            h = 2 + ( rgb.b - rgb.r ) / delta;
        else if ( rgb.b == v )
            h = 4 + ( rgb.r - rgb.g ) / delta;

        h *= 60;

        if ( h < 0.0 )
            h = h + 360;
    }

    HSV hsv;
    hsv.H = h;
    hsv.S = s;
    hsv.V = v / 255;

    return hsv;
}

float calcDistance( float a, float b ) {
    complex c = a + b * I;
    complex z = 0;
    complex dz = 0;
    float m2;

    for ( int i = 0; i < 1024; i++ ) {
        dz = 2.0 * z * dz + 1.0;
        z = z * z + c;
        m2 = cabs( z );
        if ( m2 > 1e20 )
            break;
    }

    return sqrtf( m2 / cabs( dz ) ) * 0.5 * log( m2 );
}

HSV GiveHSV( double complex z ) {
    // The HSV, or HSB, model describes colors in terms of
    // hue, saturation, and value (brightness).
    // hue = f(argument(z))
    // hue values range from .. to ..
    HSV h;
    double a = carg( z );

    while ( a < 0 )
        a += 2 * M_PI;
    a /= 2 * M_PI;
    // radius of z
    double m = cabs( z );
    double ranges = 0;
    double rangee = 1;
    while ( m > rangee ) {
        ranges = rangee;
        rangee *= M_E;
    }
    double k = ( m - ranges ) / ( rangee - ranges );
    // saturation = g(abs(z))
    double sat = k < 0.5 ? k * 2 : 1 - ( k - 0.5 ) * 2;
    sat = 1 - pow( ( 1 - sat ), 3 );
    sat = 0.4 + sat * 0.6;
    // value = h(abs(z))
    double val = k < 0.5 ? k * 2 : 1 - ( k - 0.5 ) * 2;
    val = 1 - val;
    val = 1 - pow( ( 1 - val ), 3 );
    val = 0.6 + val * 0.4;

    h.H = a;
    h.S = sat;
    h.V = val;

    return h;
}
