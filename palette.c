/**
 **  @file palette.c
 **  @author Hugh S. Myers
 **  @brief A collection of functions in aid of the care and feeding of palettes.
 **  @date Fri Aug 11 07:38:08 2017
 **
 **  @section DESCRIPTION
 **
 **  mp uses two methods to color a given fractal image. The first is a simple color table look-up,
 **  from an array of Rgb values. This structure is referred to as a palette, as in palette of
 **  colors like that used by artists. The functions here allow the creation, destruction, and
 **  manipulation of palettes.
 **
 **  @bug No known bugs.
 **
 **  @todo Refactor code to eliminate duplication and near-duplication.
 **/
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "palette.h"
#include "colors.h"
#include "cspace.h"

/**
 * @brief Initialize Dynamic Array
 * @details This begins a chain of memory allocations for a given typedef/struct. In this instance, the type is Rgb.
 *
 * @param A pointer to an array.
 * @param initialSize How many instances of item for initial allocation
 */
void initArray( Array * a, size_t initialSize ) {
    a->array = ( Rgb * ) malloc( initialSize * sizeof( Rgb ) );
    a->used = 0;
    a->size = initialSize;
}

/**
 * @brief Add item to dynamic array.
 * @details Either insert item into already allocated space or fetch more space and then insert.
 *
 * @param A pointer to an array.
 * @param element Item to be inserted.
 */
void insertArray( Array * a, Rgb element ) {
    if ( a->used == a->size ) {
        a->size *= 2;
        a->array = ( Rgb * ) realloc( a->array, a->size * sizeof( Rgb ) );
    }
    a->array[a->used++] = element;
}

/**
 * @brief Deallocate array.
 * @details Free memory allocated for dynamic array.
 *
 * @param a A pointer to an array.
 */
void freeArray( Array * a ) {
    free( a->array );
    a->array = NULL;
    a->used = a->size = 0;
}

/**
 * @brief Initialize palette from a palette file.
 * @details Given the name of a palette file of Rgb triples read, create, and load a palette.
 *
 * @param palname Name of palette file.
 * @return Returns an instance of dynamic array. Palette in this case.
 */
Array getColors( char *palname ) {
    FILE *fp;
    Rgb scan;
    Array colors;

    if ( ( fp = fopen( palname, "r+" ) ) == NULL ) {
        printf( "No such file\n" );
        exit( 1 );
    }

    initArray( &colors, 16 );
    while ( true ) {
        int ret = fscanf( fp, "%hhi %hhi %hhi", &scan.r, &scan.g, &scan.b );
        if ( ret == 3 ) {
            insertArray( &colors, scan );
        } else if ( ret == EOF ) {
            break;
        } else {
            printf( "Problem! ret=%d\n", ret );
            exit( 1 );
        }
    }
    fclose( fp );
    return colors;
}

/**
 * @brief Initialize palette from command line information.
 * @details Given start and finish colors, construct a palette accordingly.
 *
 * @param p Pointer to command line information typedef/struct
 * @return Returns an instance of dynamic array. Palette in this case.
 */
Array setColors( Parameters p ) {
    Rgb start;
    Rgb finish;
    int N = atoi( p.palname + strcspn( p.palname, "1234567890" ) );

    if ( N == 0 ) {
        N = 512;
    }
    setRgb( &start, &finish, p );

    return fromStart2Finish( start, finish, N );
}

/**
 * @brief Given a start Rgb value and a finish Rgb value, create a palette of N steps.
 * @details Convert the given bracketing colors to HSV space and linearly interpolate between them.
 *
 * @param start First or starting Rgb color.
 * @param finish Second or finishing Rgb color.
 * @param N Number of color values between start and finish ( inclusive ).
 * @return Returns an array of Rgb values, i.e. a palette.
 */
Array fromStart2Finish( Rgb start, Rgb finish, int N ) {
    Array colors;

    HSV s = RGBToHSV( start );
    HSV f = RGBToHSV( finish );
    HSV inter;

    double cR = s.H;
    double cG = s.S;
    double cB = s.V;
    double dR = f.H - cR;
    double dG = f.S - cG;
    double dB = f.V - cB;

    initArray( &colors, 16 );
    for ( int i = 0; i < N; ++i ) {
        inter.H = cR + i * dR / N;
        inter.S = cG + i * dG / N;
        inter.V = cB + i * dB / N;
        insertArray( &colors, HSVToRGB( inter ) );
    }

    return colors;
}

/**
 * @brief Write out an image of the palette.
 * @details Given a filename create a .ppm image file, displaying the chosen palette.
 *
 * @param colors Palate to use.
 * @param filename Name of file to create and write to,
 */
void writeColors( Array colors, char *filename ) {
    int width = colors.used;
    int height = 100;
    FILE *fp;

    fp = fopen( filename, "wb" );
    if ( fp == NULL ) {
        printf( "fopen failed for file: %s, errno: %d\n", filename, errno );
        exit( EXIT_FAILURE );
    }
    fprintf( fp, "P6\n# Palette Display Image\n %d\n %d\n %d\n", width, height, 255 );

    for ( int y = 0; y < height; y++ ) {
        for ( int x = 0; x < width; x++ ) {
            fwrite( &colors.array[x], 1, sizeof( Rgb ), fp );
        }
    }

    fclose( fp );
}

/**
 * @brief Read a palette file.
 * @details Read a palette file and create a palette, using the first line.
 *
 * PPM File Format
 *
 *  1. A "magic number" for identifying the file type. A ppm image's magic number is the two characters "P6".
 *  2. Whitespace (blanks, TABs, CRs, LFs).
 *  3. A width, formatted as ASCII characters in decimal.
 *  4. Whitespace.
 *  5. A height, again in ASCII decimal.
 *  6. Whitespace.
 *  7. The maximum color value (Maxval), again in ASCII decimal. Must be less than 65536 and more than zero.
 *  8. A single whitespace character (usually a newline).
 *  9. A raster of Height rows, in order from top to bottom. Each row consists of Width pixels,
 *     in order from left to right. Each pixel is a triplet of red, green, and blue samples, in that order.
 *     Each sample is represented in pure binary by either 1 or 2 bytes. If the Maxval is less than 256,
 *     it is 1 byte. Otherwise, it is 2 bytes. The most significant byte is first.
 *
 * @param filename Name of file to read.
 * @return Returns a dynamic palette array.
 */
Array readColors( char *filename ) {
    char buffer[PPMREADBUFLEN];
    char *t;
    int r;
    FILE *fp;
    size_t rd;
    Array colors;
    Rgb color;
    int argc = 0;
    int argv[10] = { 0 };
    int max = 3;

    fp = fopen( filename, "rb" );
    if ( fp == NULL ) {
        printf( "fopen failed for file: %s, errno: %d\n", filename, errno );
        exit( EXIT_FAILURE );
    }
    t = fgets( buffer, PPMREADBUFLEN, fp );

    if ( ( t == NULL ) || ( strncmp( buffer, "P6\n", 3 ) != 0 ) ) {
        printf( "fgets failure[1], %s is not a PPM file\n", filename );
        exit( EXIT_FAILURE );
    }
    while ( 1 ) {
        t = fgets( buffer, PPMREADBUFLEN, fp );
        if ( t == NULL ) {
            printf( "fgets failure[2], %s is not a PPM file\n", filename );
            exit( EXIT_FAILURE );
        }
        if ( buffer[0] == '#' ) {
            continue;
        }
        r = sscanf( buffer, "%d %d %d", &argv[argc], &argv[argc + 1], &argv[argc + 2] );
        if ( max > 0 ) {
            if ( r == max ) {
                break;
            } else if ( r == max - 1 ) {
                argc += max - 1;
                max -= 2;
            } else if ( r == max - 2 ) {
                argc += max - 2;
                max -= 1;
            }
        } else {
            break;
        }
    }

    initArray( &colors, 16 );
    for ( int n = 0; n < argv[0]; n++ ) {
        rd = fread( &color, sizeof( Rgb ), 1, fp );
        if ( rd < 1 ) {
            printf( "fread failure[5], file: %s\n", filename );
            exit( EXIT_FAILURE );
        }
        insertArray( &colors, color );
    }
    return colors;
}

/**
 * @brief Build a palette from list of Rgb information.
 * @details Handle multiple -k entries and construct a palette by parsing the entries. The palette
 *          consists of colors laid end to end with each color specified acting as the head and tail
 *          of a color segment. Start with first, interpolate for listed (or default) number
 *          of values. Next segment starts with previous closing color and proceeds in the same
 *          fashion to the next color.
 *
 * @param p Parameters file which contains stack of entries from the -k options
 * @return Returns a dynamic palette array.
 */
Array buildColors( Parameters p ) {
    Array colors;
    Rgb gray = { 32, 32, 32 };
    Rgb list[NAMES_SIZE];
    int runLength[NAMES_SIZE] = { 0 };

    for ( int n = 0; n < p.nargc; n++ ) {
        list[n] = parseRGB( p.names[n], &runLength[n] );
    }
    initArray( &colors, 16 );
    insertArray( &colors, list[0] );
    if ( p.nargc > 1 ) {
        for ( int n = 0; n < p.nargc - 1; n++ ) {
            appendColors( list[n], list[n + 1], runLength[n], &colors );
        }
    } else {
        appendColors( list[0], gray, runLength[0], &colors );
    }

    return colors;
}

/**
 * @brief Mini parser for -k option format.
 * @details -k or --kolor allows Rgb references in tow forms with an optional step indicator
 *          allowed in either case. If the reference begins with a '{' it is assumed to be
 *          an actual Rgb triplet and the the 3 values are scanned and parsed accordingly.
 *          If not a curly brace, then the assumption becomes that the entry is a named
 *          reference and a color name lookup is performed. Then the parser determines if
 *          a colon is present and if so, the numeric value is parsed and returned by
 *          setting the int pointer 'n' to the retrieved value. It defaults to 128. Finally
 *          the routine returns a palette.
 *
 * @param s -k value.
 * @param n pointer to an integer which receives the interval or step value.
 *
 * @return Returns an Rgb triplet and sets the pointer to the interval.
 */
Rgb parseRGB( char *s, int *n ) {
    Rgb color;
    char *ptr;

    *n = 128;
    if ( s[0] == '{' ) {
        raw2Rgb( s, &color );
    } else {
        name2Rgb( s, &color );
    }
    ptr = strpbrk( s, ":" );
    if ( ptr ) {
        *n = atoi( ptr + 1 );
    }
    return color;
}

/**
 * @brief Append a range of colors to a palette.
 * @details This function creates a range of colors between a pair of values, by stepping
 *          through HSV space and then converting each result to Rgb. The colors are created
 *          with a simple linear interpolation for each value.
 *
 * @note The apparent off-by-one error where the index of values starts at 1 rather than
 *       at zero is intentional. It prevents doubling the end/start value that would otherwise
 *       occur.
 *
 * @param start First color in the sequence of Rgb values.
 * @param finish Last color in the sequence of Rgb values.
 * @param N number of steps in the interval between start and finish.
 * @param colors existing dynamic array of colors to extend.
 */
void appendColors( Rgb start, Rgb finish, int N, Array * colors ) {
    HSV s = RGBToHSV( start );
    HSV f = RGBToHSV( finish );
    HSV inter;

    if (N == 0) {
        N = 128;
    }
    double cR = s.H;
    double cG = s.S;
    double cB = s.V;
    double dR = f.H - cR;
    double dG = f.S - cG;
    double dB = f.V - cB;

    for ( int i = 1; i < N; ++i ) {
        inter.H = cR + i * dR / N;
        inter.S = cG + i * dG / N;
        inter.V = cB + i * dB / N;
        insertArray( colors, HSVToRGB( inter ) );
    }
}
