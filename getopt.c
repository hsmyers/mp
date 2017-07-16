//
// getopt.c
//
// to compile:  gcc -Wall -DTEST getopt.c dictionary.c iniparser.c -o getopt
//
// dictionary.c
// iniparser.c
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include "iniparser.h"
#include "getopt.h"

#ifdef TEST
char *Version = "0.015";
char *Date = "Sun Jun 11 16:50:34 2017";

int main( int argc, char **argv ) {
    Parameters p = getParameters( argc, argv, Version, Date );

    showParameters( p );
    freeParameters( p );

    return 0;
}
#endif

Parameters getParameters( int argc, char *argv[], char *Version,
                          char *Date ) {
    Parameters p = parse_ini_file( "mandel.cfg" );
    char buffer[256];
    int c;

    while ( true ) {
        static struct option long_options[] = {
            {"config", required_argument, 0, 'c'},
            {"diameter", required_argument, 0, 'd'},
            {"file", required_argument, 0, 'f'},
            {"height", required_argument, 0, 'h'},
            {"help", no_argument, 0, 'l'},
            {"iteration", required_argument, 0, 'i'},
            {"magnify", required_argument, 0, 'm'},
            {"next", optional_argument, 0, 'n'},
            {"palette", required_argument, 0, 'p'},
            {"rgb", required_argument, 0, 'r'},
            {"tweak", required_argument, 0, 't'},
            {"version", no_argument, 0, 'v'},
            {"width", required_argument, 0, 'w'},
            {"x_center", required_argument, 0, 'x'},
            {"y_center", required_argument, 0, 'y'},
            {0, 0, 0, 0}
        };
        int option_index = 0;

        c = getopt_long( argc, argv, "d:t:r:c:x:y:m:i:w:h:d:f:p:n::vl",
                         long_options, &option_index );
        if ( c == -1 )
            break;

        switch ( c ) {
        case 0:
            break;
        case 'x':
            sscanf( optarg, "%Lf", &p.centerX );
            break;
        case 'y':
            sscanf( optarg, "%Lf", &p.centerY );
            break;
        case 'm':
            sscanf( optarg, "%Lf", &p.magnify );
            p.diameter = 1.0 / p.magnify;
            break;
        case 'd':
            sscanf( optarg, "%Lf", &p.diameter );
            break;
        case 'n':
            if ( optarg ) {
                p.next = atoi( ++optarg );
            } else {
                p.next = getNext( "ppm" );
            }
            sprintf( buffer, "ppm\\fractal.%03d.ppm", p.next++ );
            free( p.filename );
            p.filename = getstr( buffer );
            break;
        case 'c':
            free( p.config );
            p.config = getstr( optarg );
            break;
        case 'r':
            p.rgb = atoi( optarg );
            break;
        case 't':
            p.tweak = atoi( optarg );
            break;
        case 'i':
            p.maxiter = atoi( optarg );
            break;
        case 'w':
            p.width = atoi( optarg );
            break;
        case 'h':
            p.height = atoi( optarg );
            break;
        case 'f':
            free( p.filename );
            p.filename = getstr( optarg );
            break;
        case 'p':
            free( p.palname );
            p.palname = getstr( optarg );
            break;
        case '?':
            help( '?', argv[0], Version, Date );
            break;
        case 'v':
            help( 'v', argv[0], Version, Date );
            break;
        case 'l':
            help( 'l', argv[0], Version, Date );
            break;
        default:
            abort(  );
        }
    }
    return p;
}

void help( char c, char *Program, char *Version, char *Date ) {
    printf( "%s vr%s dated %s\n", Program, Version, Date );
    if ( c == 'l' || c == '?' ) {
        printf( "\n  Options:\n\n" );
        printf( "  --x_center    requires an argument -x\n" );
        printf( "  --y_center    requires an argument -y\n" );
        printf( "  --magnify     requires an argument -m\n" );
        printf( "  --diameter    requires an argument -d\n" );
        printf( "  --iteration   requires an argument -i\n" );
        printf( "  --width       requires an argument -w\n" );
        printf( "  --height      requires an argument -h\n" );
        printf( "  --file        requires an argument -f\n" );
        printf( "  --palette     requires an argument -p\n" );
        printf( "  --next        argument is optional -n\n" );
        printf( "  --config      requires an argument -c\n" );
        printf( "  --rgb         requires an argument -r\n" );
        printf( "  --tweak       requires an argument -t\n" );
        printf( "  --version     no argument          -v\n" );
        printf( "  --help        no argument          -l\n" );
        printf
            ( "\n  long options ('--' prefix) are incremental till unambiguous\n" );
        printf( "  short options ('-' prefix) are exact\n" );
        printf( "  Hideously enough, options with optional arguments,\n" );
        printf( "  take the form [-[-]]option=arg, no spaces." );
    }
    exit( 0 );
}

void freeParameters( Parameters p ) {
    free( p.filename );
    free( p.palname );
    free( p.config );
    return;
}

Parameters parse_ini_file( char *ini_name ) {
    Parameters p;
    dictionary *ini;

    ini = iniparser_load( ini_name );
    if ( ini == NULL ) {
        fprintf( stderr, "cannot parse file: %s\n", ini_name );
        return p;
    }

    p.centerX = iniparser_getlongdouble( ini, "image:centerx", 0.0 );
    p.centerY = iniparser_getlongdouble( ini, "image:centery", 0.0 );
    p.magnify = iniparser_getlongdouble( ini, "image:magnify", 1.0 );
    p.diameter = iniparser_getlongdouble( ini, "image:diameter", 3.0 );
    p.maxiter = iniparser_getint( ini, "image:maxiter", 1000 );
    p.width = iniparser_getint( ini, "image:width", 512 );
    p.height = iniparser_getint( ini, "image:height", 512 );

    p.cv = iniparser_getint( ini, "color:cv", 64 );
    p.palname =
        getstr( ( char * )
                iniparser_getstring( ini, "color:palname", "test.pal" ) );
    p.rgb = iniparser_getint( ini, "color:rgb", 0 );
    p.tweak = iniparser_getint( ini, "color:tweak", 3 );

    p.filename =
        getstr( ( char * )
                iniparser_getstring( ini, "files:filename",
                                     "ppm\\fractal.000.ppm" ) );
    p.config =
        getstr( ( char * )
                iniparser_getstring( ini, "files:config", "mandel.cfg" ) );
    p.next = iniparser_getint( ini, "files:next", 0 );

    iniparser_freedict( ini );
    return p;
}

int getNext( char *path ) {
    DIR *dp;
    struct dirent *ep;
    char *ptr;
    char buffer[256];
    int n;
    int max = 0;

    dp = opendir( path );
    if ( dp != NULL ) {
        while ( ( ep = readdir( dp ) ) ) {
            n = -1;
            strcpy( buffer, ep->d_name );
            ptr = strtok( buffer, "." );
            while ( ( ptr = strtok( NULL, "." ) ) ) {
                if ( isdigit( ptr[0] ) ) {
                    n = atoi( ptr );
                }
            }
            if ( max < n ) {
                max = n;
            }
        }
        ++max;
        closedir( dp );
    } else {
        perror( "Couldn't open the directory" );
    }
    return max;
}

char *getstr( char *arg ) {
    char *result = malloc( strlen( arg ) + 1 );
    strcpy( result, arg );
    return result;
}

void showParameters( Parameters p ) {
    printf( "  p.centerX  = '%.17Lg'\n", p.centerX );
    printf( "  p.centerY  = '%.17Lg'\n", p.centerY );
    printf( "  p.magnify  = '%.17Lg'\n", p.magnify );
    printf( "  p.diameter = '%.17Lg'\n", p.diameter );
    printf( "  p.maxiter  = '%d'\n", p.maxiter );
    printf( "  p.cv       = '%d'\n", p.cv );
    printf( "  p.width    = '%d'\n", p.width );
    printf( "  p.height   = '%d'\n", p.height );
    printf( "  p.filename = '%s'\n", p.filename );
    printf( "  p.palname  = '%s'\n", p.palname );
    printf( "  p.config   = '%s'\n", p.config );
    printf( "  p.next     = '%d'\n", p.next );
    printf( "  p.rgb      = '%d'\n", p.rgb );
    printf( "  p.tweak    = '%d'\n", p.tweak );
}
