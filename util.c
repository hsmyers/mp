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
    int length;

    strcpy( buffer, argv[0] );
    for ( int i = 1; i < argc; i++ ) {
        strcat( buffer, " " );
        length = strcspn( argv[i], " " );
        if ( length < strlen( argv[i] ) ) {
            strcat( buffer, "\"" );
            strcat( buffer, argv[i] );
            strcat( buffer, "\"" );
        } else {
            strcat( buffer, argv[i] );
        }
    }
    return buffer;
}

char *strgets( char **ptr ) {
    static char buffer[512];
    int length = strcspn( *ptr, "\n" );

    if ( length ) {
        strncpy( buffer, *ptr, length );
        buffer[length] = '\0';
        *ptr += length + 1;
        return buffer;
    } else {
        return NULL;
    }

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

    for ( int i = 0; i < strlen( s ); ++i ) {
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

    for ( int i = 0; i < strlen( s ); ++i ) {
        if ( s[i] == c ) {
            count++;
        }
    }
    return count;
}

void signon( const char *prog, const char *Version ) {
    char Program[128];
    int n = strcspn( prog, "." );

    if ( n ) {
        strncpy( Program, prog, n );
        Program[n] = 0;
    } else {
        strcpy( Program, prog );
    }
    fprintf( stderr, "%s vr%s\n", Program, Version );
}

char **CommandLineToArgvA( char *lpCmdline, int *numargs ) {
    char **argv;
    char *cmdline;
    char *d;
    char *s;
    int argc;
    int bcount;
    int qcount;

    if ( !numargs || *lpCmdline == 0 ) {
        fprintf( stderr, "Invalid parameter\n" );
        exit( EXIT_FAILURE );
    }
    argc = 1;
    s = lpCmdline;
    if ( *s == '"' ) {
        s++;
        while ( *s ) {
            if ( *s++ == '"' ) {
                break;
            }
        }
    } else {
        while ( *s && *s != ' ' && *s != '\t' ) {
            s++;
        }
    }
    while ( *s == ' ' || *s == '\t' ) {
        s++;
    }
    if ( *s ) {
        argc++;
    }
    qcount = bcount = 0;
    while ( *s ) {
        if ( ( *s == ' ' || *s == '\t' ) && qcount == 0 ) {
            while ( *s == ' ' || *s == '\t' ) {
                s++;
            }
            if ( *s ) {
                argc++;
            }
            bcount = 0;
        } else if ( *s == '\\' ) {
            bcount++;
            s++;
        } else if ( *s == '"' ) {
            /* '"' */
            if ( ( bcount & 1 ) == 0 ) {
                qcount++;
            }
            s++;
            bcount = 0;
            while ( *s == '"' ) {
                qcount++;
                s++;
            }
            qcount = qcount % 3;
            if ( qcount == 2 ) {
                qcount = 0;
            }
        } else {
            bcount = 0;
            s++;
        }
    }
    argv =
        ( char ** ) malloc( ( argc + 1 ) * sizeof( char * ) + ( strlen( lpCmdline ) + 1 ) * sizeof( char ) );
    if ( !argv ) {
        return NULL;
    }
    cmdline = ( char * ) ( argv + argc + 1 );
    strcpy( cmdline, lpCmdline );
    argv[0] = d = cmdline;
    argc = 1;
    if ( *d == '"' ) {
        s = d + 1;
        while ( *s ) {
            if ( *s == '"' ) {
                s++;
                break;
            }
            *d++ = *s++;
        }
    } else {
        while ( *d && *d != ' ' && *d != '\t' ) {
            d++;
        }
        s = d;
        if ( *s ) {
            s++;
        }
    }
    *d++ = 0;
    while ( *s == ' ' || *s == '\t' ) {
        s++;
    }
    if ( !*s ) {
        argv[argc] = NULL;
        *numargs = argc;
        return argv;
    }
    argv[argc++] = d;
    qcount = bcount = 0;
    while ( *s ) {
        if ( ( *s == ' ' || *s == '\t' ) && qcount == 0 ) {
            *d++ = 0;
            bcount = 0;
            do {
                s++;
            } while ( *s == ' ' || *s == '\t' );
            if ( *s ) {
                argv[argc++] = d;
            }
        } else if ( *s == '\\' ) {
            *d++ = *s++;
            bcount++;
        } else if ( *s == '"' ) {
            if ( ( bcount & 1 ) == 0 ) {
                d -= bcount / 2;
                qcount++;
            } else {
                d = d - bcount / 2 - 1;
                *d++ = '"';
            }
            s++;
            bcount = 0;
            while ( *s == '"' ) {
                if ( ++qcount == 3 ) {
                    *d++ = '"';
                    qcount = 0;
                }
                s++;
            }
            if ( qcount == 2 ) {
                qcount = 0;
            }
        } else {
            *d++ = *s++;
            bcount = 0;
        }
    }
    *d = '\0';
    argv[argc] = NULL;
    *numargs = argc;
    return argv;
}

