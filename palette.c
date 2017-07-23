/**
 **  palette.c
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
 * @param initialSize How many instances of item for inital allocation
 */
void initArray( Array *a, size_t initialSize ) {
    a->array = ( Rgb * )malloc( initialSize * sizeof( Rgb ) );
    a->used  = 0;
    a->size  = initialSize;
}

/**
 * @brief Add item to dynamic array.
 * @details Either insert item into already allocated space or fetch more space and then insert.
 *
 * @param A pointer to an array.
 * @param element Item to be inserted.
 */
void insertArray( Array *a, Rgb element ) {
    if ( a->used == a->size ) {
        a->size *= 2;
        a->array = ( Rgb * )realloc( a->array, a->size * sizeof( Rgb ) );
    }
    a->array[a->used++] = element;
}

/**
 * @brief Deallocate array.
 * @details Free memory allocated for dynamic array.
 *
 * @param a A pointer to an array.
 */
void freeArray( Array *a ) {
    free( a->array );
    a->array = NULL;
    a->used  = a->size = 0;
}

/**
 * @brief Initialize palette from a palette file.
 * @details Give the name of a palette file of Rgb triples read and load a palette.
 *
 * @param palname Name of palette file.
 * @return Returns an instance of array. Palette in this case.
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
 * @return Returns an instance of array. Palette in this case.
 */
Array setColors( Parameters p ) {
    Array colors;
    Rgb start;
    Rgb finish;
    int N = atoi( p.palname + strcspn( p.palname, "1234567890" ) );

    if ( N == 0 ) {
        N = 512;
    }
    setRgb( &start, &finish, p );

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
    for (int i = 0; i < N; ++i) {
        inter.H = cR + i * dR / N;
        inter.S = cG + i * dG / N;
        inter.V = cB + i * dB / N;
        insertArray( &colors, HSVToRGB( inter ) );
    }

    return colors;
}
