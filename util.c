//
// util.c
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

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

