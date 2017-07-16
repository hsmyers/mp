//
// cspace.c
//
#include <math.h>
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
