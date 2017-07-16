/**
 **  palette.c
 **/
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "palette.h"

void initArray( Array *a, size_t initialSize ) {
    a->array = ( Rgb * )malloc( initialSize * sizeof( Rgb ) );
    a->used  = 0;
    a->size  = initialSize;
}

void insertArray( Array *a, Rgb element ) {
    if( a->used == a->size ) {
        a->size *= 2;
        a->array = ( Rgb * )realloc( a->array, a->size * sizeof( Rgb ) );
    }
    a->array[a->used++] = element;
}

void freeArray( Array *a ) {
    free( a->array );
    a->array = NULL;
    a->used  = a->size = 0;
}

Array getColors( char *palname ) {
    FILE *fp;
    Rgb scan;
    Array colors;

    if( ( fp = fopen( palname, "r+" ) ) == NULL ) {
        printf( "No such file\n" );
        exit( 1 );
    }

    initArray( &colors, 16 );
    while( true ) {
        int ret = fscanf( fp, "%hhi %hhi %hhi", &scan.r, &scan.g, &scan.b );
        if( ret == 3 ) {
            insertArray( &colors, scan );
        } else if( ret == EOF ) {
            break;
        } else {
            printf( "Problem! ret=%d\n", ret );
            exit( 1 );
        }
    }
    fclose( fp );
    return colors;
}
