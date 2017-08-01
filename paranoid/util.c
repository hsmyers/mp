/**
 **  @file util.c
 **  @author Hugh S. Myers
 **  @brief A collection of functions in aid of support for mp.
 **  @date Mon Jul 24 17:01:02 2017
 **
 **  General catch-all of routines needed but not complicated enough for their own file.
 **
 **  @bug No known bugs.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <quadmath.h>
#include <ctype.h>
#include "util.h"

/**
 * @brief Assemble the command-line as a string.
 * @details Reconstruct the command-line from argc and argv.
 *
 * @param argc Argument count.
 * @param argv Command-line substrings array.
 *
 * @return An image of the original command-line as a pointer to a static buffer.
 */
char *getCl( int argc, char *argv[] ) {
    static char buffer[256];

    strcpy( buffer, argv[0] );
    for ( int i = 1; i < argc; i++ ) {
        strcat( buffer, " " );
        strcat( buffer, argv[i] );
    }
    return buffer;
}

char *ReadFile( char *filename ) {
    char *buffer = NULL;
    long string_size;
    size_t read_size;
    FILE *fp = fopen( filename, "rb" );

    if ( fp ) {
        fseek( fp, 0, SEEK_END );
        string_size = ftell( fp );
        rewind( fp );
        buffer = ( char * ) malloc( sizeof( char ) * ( string_size + 1 ) );
        read_size = fread( buffer, sizeof( char ), string_size, fp );
        buffer[string_size] = '\0';
        if ( string_size != read_size ) {
            free( buffer );
            buffer = NULL;
        }
        fclose( fp );
    }
    return buffer;
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

void str2abbr( char *abbr, size_t size, const char *s ) {
    int n = 0;

    for (int i = 0; i < strlen( s ); ++i) {
        if ( isupper( s[i] ) && n < size ) {
            abbr[n++] = s[i];
            abbr[n] = 0;
        }
    }
}


__float128 fabsq( __float128 x ) {
    if ( x < 0 ) {
        x *= -1.0;
    }
    return x;
}

int countChar( const char *s, const char c ) {
    int count = 0;

    for (int i = 0; i < strlen( s ); ++i) {
        if ( s[ i ] == c ) {
            count++;
        }
    }
    return count;
}
